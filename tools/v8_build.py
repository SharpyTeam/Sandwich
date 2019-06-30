import urllib.request
import zipfile
import sys
import os
import subprocess
import shutil


def progress(count, total, status=''):
    bar_len = 60
    filled_len = int(round(bar_len * count / float(total)))
    percents = round(100.0 * count / float(total), 1)
    bar = '=' * filled_len + '-' * (bar_len - filled_len)
    sys.stdout.write('[%s] %s%s %s\r' % (bar, percents, '%', status))
    sys.stdout.flush()


def run_command(command, env=None, cwd=None):
    if sys.platform.startswith('win32'):
        subprocess.run(['cmd', '/C'] + command, cwd=cwd, env=env)
    else:
        subprocess.run(command, cwd=cwd, env=env)


def clean_tmp():
    if os.path.exists('tmp'):
        shutil.rmtree('tmp')


def main():
    build_config = 'release'
    if len(sys.argv) > 1 and sys.argv[1] == 'debug':
        build_config = 'debug'

    clean_tmp()
    if not os.path.exists('tmp'):
        os.makedirs('tmp')

    print('Downloading depot_tools...')
    filename, _ = urllib.request.urlretrieve('https://storage.googleapis.com/chrome-infra/depot_tools.zip',
                                             'tmp/depot_tools.zip',
                                             lambda blocks, block_size, total_size:
                                             progress(blocks * block_size, total_size))
    print()
    print('Extracting depot_tools...')
    zip_ref = zipfile.ZipFile(filename, 'r')
    zip_ref.extractall('tmp/depot_tools')
    zip_ref.close()

    depot_tools_path = os.path.abspath('tmp/depot_tools')

    env = os.environ.copy()

    if sys.platform.startswith('win32'):
        vs_version = '2017'

        if os.path.exists('C:\\Program Files (x86)\\Microsoft Visual Studio\\2019'
                          '\\Community\\VC\\Auxiliary\\Build\\vcvarsall.bat'):
            vs_version = '2019'

        env['DEPOT_TOOLS_WIN_TOOLCHAIN'] = '0'
        env['GYP_MSVS_VERSION'] = vs_version

    env['PATH'] = depot_tools_path + (';' if sys.platform.startswith('win32') else ':') + env['PATH']

    run_command(['gclient'], env)

    if not os.path.exists(os.path.join(depot_tools_path, 'v8')):
        os.makedirs(os.path.join(depot_tools_path, 'v8'))

    run_command(['fetch', 'v8'], env, os.path.join(depot_tools_path, 'v8'))

    v8_path = os.path.join(depot_tools_path, 'v8', 'v8')

    run_command(['python', 'tools/dev/v8gen.py', 'x64.release.sample'], env, v8_path)
    os.unlink(os.path.join(v8_path, 'out.gn', 'x64.release.sample', 'args.gn'))
    shutil.copyfile('v8_build_config/x64_' + build_config + '.gn',
                    os.path.join(v8_path, 'out.gn', 'x64.release.sample', 'args.gn'))
    run_command(['gn', 'gen', 'out.gn/x64.release.sample'], env, v8_path)
    run_command(['ninja', '-C', 'out.gn/x64.release.sample', 'v8_monolith'], env, v8_path)
    lib_extension = '.lib' if sys.platform.startswith('win32') else '.a'

    if not os.path.exists('../lib'):
        os.makedirs('../lib')

    shutil.copyfile(
        os.path.join(v8_path, 'out.gn', 'x64.release.sample', 'obj', 'v8_monolith' + lib_extension),
        '../lib/v8_monolith_' + build_config + lib_extension)
    if os.path.exists(os.path.join(v8_path, 'out.gn', 'x64.release.sample', 'obj', 'v8_monolith.pdb')):
        shutil.copyfile(os.path.join(v8_path, 'out.gn', 'x64.release.sample', 'obj', 'v8_monolith.pdb'),
                        '../lib/v8_monolith_' + build_config + '.pdb')


if __name__ == '__main__':
    main()
