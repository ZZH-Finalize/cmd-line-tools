set_project('cli-tools')
set_version('0.1')
set_license('GPL-2.0')
add_rules('mode.debug', 'mode.release')
set_defaultmode('release')
set_languages('gnu23')
set_warnings('everything')
set_toolchains('gcc')

add_rules('plugin.compile_commands.autoupdate', {outputdir = '$(builddir)'})

-- 公共动态库
target('cmdtool_common')
    set_kind('shared')
    add_files('lib/common.c')
    add_includedirs('lib', {public = true})

for _, src in ipairs(os.files(path.join(os.scriptdir(), '*.c')) or {}) do
    local name = path.basename(src)

    target(name)
        set_kind('binary')
        add_files(src)
        add_deps('cmdtool_common')
        add_includedirs('lib')
end
