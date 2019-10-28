const fs = require('fs'),
    path = require('path'),
    child_process = require('child_process');

if (process.argv.length < 5) {
    console.error("Not enough arguments!");
    console.info('Usage: node build_v8.js <version> <config> <output_dir>');
    process.exit(-1);
}

const depotToolsRepoURL = "https://chromium.googlesource.com/chromium/tools/depot_tools.git";
const depotToolsBundleURL = "https://storage.googleapis.com/chrome-infra/depot_tools.zip";

const vs2019TagPath = "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Auxiliary\\Build\\vcvarsall.bat";
const vs2017TagPath = "C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Auxiliary\\Build\\vcvarsall.bat";

const buildVersion = process.argv[2].trim();
const buildConfig = process.argv[3].trim();
const outputDirPath = path.resolve(process.argv[4]);
const libExtension = isWindows() ? "dll" : "a";
const v8VersionCode = "v8_" + buildVersion + "_" + buildConfig;
const v8LibFileName = v8VersionCode + "." + libExtension;
const outputLibDirPath = path.join(outputDirPath, 'lib');
const outputLibFilePath = path.join(outputLibDirPath, v8LibFileName);
const outputPdbFilePath = path.join(outputLibDirPath, v8VersionCode + ".pdb");
const outputHeadersDirPath = path.join(outputDirPath, 'include');

const depotToolsPath = path.resolve('depot_tools');
const v8Path = path.resolve('tmp', 'v8');
const v8RealPath = path.join(v8Path, 'v8');
const v8HeadersPath = path.join(v8RealPath, 'include');
const v8OutPath = path.join(v8RealPath, 'out.gn', buildConfig);
const v8OutObjPath = path.join(v8OutPath, 'obj');
const v8TagFilePath = path.join(v8RealPath, '.v8_dl');
const depotToolsBundleFilePath = path.join(depotToolsPath, 'depot_tools.zip');
const depotToolsTagFilePath = path.join(depotToolsPath, '.depot_tools_dl');
const v8BuildConfigDirPath = path.resolve('v8_build_config');
const v8BuildConfigPath = path.join(v8BuildConfigDirPath, buildConfig + ".gn");

let vsVersion = '';

function downloadFileSync(url, destination) {
    child_process
        .execFileSync('curl', ['-L', url, '-o', destination], {
            encoding: 'utf8',
            maxBuffer: Infinity,
            shell: true
        });
}

/*
 * Unzip specified file (Windows only!)
 */
function unzipFile(file, destinationDir) {
    child_process
        .execFileSync('powershell', ['-Command', 'Expand-Archive', file, destinationDir], {
            encoding: 'utf8',
            maxBuffer: Infinity,
            shell: true
        });
}

function mkdir(dirPath) {
    if (!fs.existsSync(dirPath))
        fs.mkdirSync(depotToolsPath, {recursive: true});
}

function copyDirContents(sourceDir, destinationDir) {
    if (!path.isAbsolute(sourceDir)) {
        sourceDir = path.resolve(sourceDir);
    }
    if (!path.isAbsolute(destinationDir)) {
        destinationDir = path.resolve(destinationDir);
    }

    mkdir(destinationDir);
    let contents = fs.readdirSync(sourceDir);
    for (let i = 0; i < contents.length; ++i) {
        let node = contents[i];
        let nodePath = path.join(sourceDir, node);
        let nodeDestinationPath = path.join(destinationDir, nodePath);
        let nodeStats = fs.statSync(nodePath);
        if (nodeStats.isFile()) {
            fs.copyFileSync(nodePath, nodeDestinationPath);
        } else if (nodeStats.isDirectory()) {
            copyDirContents(nodePath, nodeDestinationPath);
        }
    }
}

function rmDir(dirPath) {
    if (!path.isAbsolute(dirPath)) {
        dirPath = path.resolve(dirPath);
    }

    let contents = fs.readdirSync(dirPath);
    for (let i = 0; i < contents.length; ++i) {
        let node = contents[i];
        let nodePath = path.join(dirPath, node);
        let nodeStats = fs.statSync(nodePath);
        if (nodeStats.isFile()) {
            fs.unlinkSync(nodePath);
        } else if (nodeStats.isDirectory()) {
            rmDir(nodePath);
            fs.rmdirSync(nodePath);
        }
    }
}

function checkV8LibPresence() {
    return fs.existsSync(v8LibFileName);
}

/*
 * Check if we've fully downloaded depot_tools before
 */
function checkDepotToolsPresence() {
    return fs.existsSync(depotToolsTagFilePath);
}

/*
 * Check if we've fully fetched V8 before
 */
function checkV8Presence() {
    return fs.existsSync(v8TagFilePath);
}

function fetchDepotTools() {
    if (isWindows()) {
        console.info('Downloading depot_tools...');
        downloadFileSync(depotToolsBundleURL, depotToolsBundleFilePath);
        console.info('Unpacking depot_tools...');
        unzipFile(depotToolsBundleFilePath, depotToolsPath);
        fs.unlinkSync(depotToolsBundleFilePath);
    } else {
        console.info('Cloning depot_tools...');
        child_process
            .execFileSync('git', ['clone', depotToolsRepoURL, depotToolsPath], {
                encoding: 'utf8',
                maxBuffer: Infinity,
                shell: true,
                cwd: depotToolsPath
            });
    }
    fs.appendFileSync(depotToolsTagFilePath, '');
}

function fetchV8() {
    console.info('Fetching V8...');
    child_process
        .execFileSync('fetch', ['v8'], {
            encoding: 'utf8',
            maxBuffer: Infinity,
            shell: true,
            cwd: v8Path,
            env: getEnv(),
            stdio: "pipe"
        });
    fs.appendFileSync(v8TagFilePath, '');
}

function buildV8() {
    if (fs.existsSync(v8OutPath)) {
        rmDir(v8OutPath);
    }

    console.info("Generating build config...");
    child_process
        .execFileSync('python', ['tools/dev/v8gen.py', buildConfig], {
            encoding: 'utf8',
            maxBuffer: Infinity,
            shell: true,
            cwd: v8RealPath,
            env: getEnv()
        });

    if (!fs.existsSync(v8OutPath)) {
        console.error("Error! Looks like v8gen.py doesn't know about '" + buildConfig + "' build config.");
        process.exit(-1);
    }

    fs.copyFileSync(v8BuildConfigPath, path.join(v8OutPath, 'args.gn'));

    child_process
        .execFileSync('gn', ['gen', 'out.gn/' + buildConfig], {
            encoding: 'utf8',
            maxBuffer: Infinity,
            shell: true,
            cwd: v8RealPath,
            env: getEnv(),
            stdio: "pipe"
        });

    console.info("=== STARTING BUILDING V8 ===");

    child_process
        .execFileSync('ninja', ['-C', 'out.gn/' + buildConfig, 'v8_monolith'], {
            encoding: 'utf8',
            maxBuffer: Infinity,
            shell: true,
            cwd: v8RealPath,
            env: getEnv(),
            stdio: "pipe"
        });

    console.info("=== FINISHED BUILDING V8 ===");
}

function isWindows() {
    return process.platform === "win32";
}

function isMacOS() {
    return process.platform === "darwin";
}

function isLinux() {
    return process.platform === "linux";
}

function getVSVersion() {
    if (vsVersion !== '')
        return vsVersion;

    if (!isWindows()) {
        vsVersion = '-';
        return vsVersion;
    }

    if (fs.existsSync(vs2019TagPath)) {
        vsVersion = '2019';
    } else if (fs.existsSync(vs2017TagPath)) {
        vsVersion = '2017';
    } else {
        vsVersion = 'unknown';
    }
    return vsVersion;
}

function getEnv() {
    if (isWindows()) {
        return {
            DEPOT_TOOLS_WIN_TOOLCHAIN: 0,
            GYP_MSVS_VERSION: getVSVersion(),
            Path: depotToolsPath + path.delimiter + process.env.Path
        };
    } else {
        return {
            Path: depotToolsPath + path.delimiter + process.env.Path
        };
    }
}

function copyArtifacts() {
    let builtLibPath = path.join(v8OutObjPath, 'v8_monolith.' + libExtension);
    let builtPdbPath = path.join(v8OutObjPath, 'v8_monolith.pdb');

    if (!fs.existsSync(builtLibPath)) {
        console.error("Error! Can't find any built library files (v8_monolith." + libExtension + ")");
        process.exit(-1);
    }

    fs.copyFileSync(builtLibPath, outputLibFilePath);
    console.info("Copied lib file: " + outputLibFilePath);
    if (fs.existsSync(builtPdbPath)) {
        fs.copyFileSync(builtLibPath, outputPdbFilePath);
        console.info("Copied PDB file: " + outputPdbFilePath);
    }
}

function copyHeaders() {
    console.info("Copying V8 headers...");
    copyDirContents(v8HeadersPath, outputHeadersDirPath);
    console.info("Copied V8 headers to: " + outputHeadersDirPath);
}


/* MAIN CODE */

if (!fs.existsSync(v8BuildConfigPath)) {
    console.error("Error! Build config '" + +"' doesn't exists. Check tools/v8_build_config for available build config files.");
    process.exit(-1);
}

if (!isWindows() && !isMacOS() && !isLinux()) {
    console.error("Error! Unknown platform: " + process.platform + ".");
    console.error("Are you trying to build V8 on you smart microwave oven?");
    process.exit(-1);
}

if (checkV8LibPresence()) {
    console.info("Found prebuilt V8 v" + buildVersion + " [" + buildConfig + "]");
    process.exit(0);
}

console.info('Current platform for building V8: ' + (isWindows() ? 'Windows' : isMacOS() ? 'MacOS' : isLinux() ? 'Linux' : 'UNKNOWN'));

if (isWindows() && getVSVersion() === 'unknown') {
    console.error("Can't find neither VS 2019 nor VS 2017.");
    console.error("Please, install some of them (VS 2019 is preferred) as long as the 'Desktop development with C++' component and the 'MFC/ATL support' sub-components.");
    process.exit(-1);
} else {
    console.info("VS version: " + getVSVersion());
}

if (checkDepotToolsPresence()) {
    console.info("Found previously downloaded depot_tools, running gclient to update it...");

    child_process
        .execFileSync('gclient', null, {
            encoding: 'utf8',
            maxBuffer: Infinity,
            shell: true,
            cwd: depotToolsPath,
            env: getEnv(),
            stdio: "pipe"
        });
} else {
    if (fs.existsSync(depotToolsPath))
        rmDir(depotToolsPath);

    mkdir(depotToolsPath);
    fetchDepotTools();
}

console.info("Running gclient...");
console.info("It may take some time to install necessary dependencies if needed.");
child_process
    .execFileSync('gclient', null, {
        encoding: 'utf8',
        maxBuffer: Infinity,
        shell: true,
        cwd: depotToolsPath,
        env: getEnv()
    });

if (checkV8Presence()) {
    console.log("Found previously fetched V8, updating it...");

    child_process
        .execFileSync('git', ['fetch'], {
            encoding: 'utf8',
            maxBuffer: Infinity,
            shell: true,
            cwd: v8RealPath,
            env: getEnv()
        });

    child_process
        .execFileSync('gclient', ['sync'], {
            encoding: 'utf8',
            maxBuffer: Infinity,
            shell: true,
            cwd: v8RealPath,
            env: getEnv()
        });
} else {
    if (fs.existsSync(v8Path))
        rmDir(v8Path);

    mkdir(v8Path);
    fetchV8();
}

console.info('Checking out version ' + buildVersion);

child_process
    .execFileSync('git', ['checkout', buildVersion], {
        encoding: 'utf8',
        maxBuffer: Infinity,
        shell: true,
        cwd: v8RealPath,
        env: getEnv()
    });

console.info('Pulling...');

child_process
    .execFileSync('git', ['pull'], {
        encoding: 'utf8',
        maxBuffer: Infinity,
        shell: true,
        cwd: v8RealPath,
        env: getEnv()
    });

buildV8();
copyArtifacts();
copyHeaders();

console.info('Finished!');
console.info('Static library file location: ');
console.info('Header files location: ');
console.info('V8 v' + buildVersion + ' [' + buildConfig + '] is ready to go!');