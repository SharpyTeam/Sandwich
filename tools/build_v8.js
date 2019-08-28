const fs = require('fs'),
    http = require('http2'),
    path = require('path');

const tmpDir = path.resolve('tmp');
const depotToolsDir = path.resolve('tmp', 'depot_tools');
const depotToolsFlag = path.resolve('tmp', 'depot_tools', '_sandwich_dl');
const v8Flag = path.resolve('tmp', 'v8', '_sandwich_dl');

const depotToolsRepo = 'https://chromium.googlesource.com/chromium/tools/depot_tools.git';
const depotToolsBundle = 'https://storage.googleapis.com/chrome-infra/depot_tools.zip';

if (process.argv.length < 5) {
    if (process.argv.length > 2)
        console.error("Not enough arguments!");

    console.info('Usage: node build_v8.js <build_config> <v8_branch>');
    process.exit(-1);
}

const buildConfig = path.resolve(process.argv[2]);
const branch = path.resolve(process.argv[3]);
const isWindows = process.platform === "win32";

if (!fs.existsSync(tmpDir)) {
    fs.mkdirSync(tmpDir);
}

if (!fs.existsSync(depotToolsDir)) {
    fs.mkdirSync(depotToolsDir);
}

if (!fs.existsSync(depotToolsDir)) {

}


