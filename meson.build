project('cli-tools', ['c', 'cpp'],
    version: '0.1',
    license: 'GPL-2.0',
    license_files: 'LICENSE',
    default_options: ['warning_level=3'],
)

install_dirs = {
    'linux': '~/path',
    'windows': 'D:/Path',
    'cygwin': '/cygdrive/d/Path'
}

install_path = install_dirs[target_machine.system()]

message('install path: ', install_path)

c_args = []
cpp_args = []
ld_args = []

fs = import('fs')

c_find_res = run_command('find', './', '-maxdepth', '1', '-name', '*.c',
    capture: true,
    check: false
)

cpp_find_res = run_command('find', './', '-maxdepth', '1', '-name', '*.cpp',
    capture: true,
    check: false
)

c_srcs = c_find_res.stdout().splitlines()
cpp_srcs = cpp_find_res.stdout().splitlines()

lib_srcs = [
    'lib/common.c'
]

incs = ['lib']

lib = shared_library('common', lib_srcs,
    install: true,
    install_dir: install_dirs[target_machine.system()]
)

all_srcs = c_srcs + cpp_srcs
foreach src : all_srcs

    exe_name = fs.stem(src)

    exe = executable(exe_name, src,
        include_directories: incs,
        c_args: c_args,
        cpp_args: cpp_args,
        link_args: ld_args,
        link_with: lib,
        install: true,
        install_dir: install_path
    )

endforeach

