cmake_minimum_required(VERSION 3.21.0)
project(cmdline-tools LANGUAGES C CXX)

include_directories(lib)

add_library(cmdtool_common SHARED lib/common.c)
install(TARGETS cmdtool_common DESTINATION D:/Path)

function(add_tool name src)
    add_executable(${name} ${src})
    target_link_libraries(${name} cmdtool_common)
endfunction()

file(GLOB tools
    RELATIVE ${PROJECT_SOURCE_DIR}
    *.c
    *.cpp
)

foreach(tool ${tools})
    string(REPLACE "." ";" fn ${tool})
    list(GET fn 0 fn)
    add_tool(${fn} ${tool})
    install(TARGETS ${fn} DESTINATION D:/Path)
endforeach()
