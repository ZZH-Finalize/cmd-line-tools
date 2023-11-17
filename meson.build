project('cli-tools', ['c', 'cpp'],
    version: '0.1',
    license: 'GPL-2.0',
    license_files: 'LICENSE',
    default_options: ['warning_level=3'],
)

message(host_machine.system())

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

c_srcs = c_find_res.stdout().strip().splitlines()
cpp_srcs = cpp_find_res.stdout().strip().splitlines()

lib_srcs = [
    'lib/common.c'
]

incs = ['lib']

all_srcs = c_srcs + cpp_srcs
foreach src : all_srcs

    exe_name = fs.stem(src)

    message('src: ', src, ', exe_name: ', exe_name)

    exe = executable(exe_name, src,
        include_directories: incs,
        c_args: c_args,
        cpp_args: cpp_args,
        link_args: ld_args,
        # native: true,
        install: true
    )

endforeach

