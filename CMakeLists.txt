cmake_minimum_required(VERSION 3.21.0)
project(cmdline-tools LANGUAGES C CXX)

include_directories(lib)

add_library(cmdtool_common SHARED lib/common.c)

if(${CMAKE_HOST_SYSTEM_NAME} MATCHES "Windows")
    install(TARGETS cmdtool_common DESTINATION D:/Path)
elseif(${CMAKE_HOST_SYSTEM_NAME} MATCHES "Linux")
    install(TARGETS cmdtool_common DESTINATION ~/path)
else()
    message(FATAL_ERROR "unknow platform")
endif()

function(add_tool name src)
    add_executable(${name} ${src})
    target_link_libraries(${name} cmdtool_common)
endfunction()

file(GLOB tools
    RELATIVE ${PROJECT_SOURCE_DIR}
    *.c
    *.cpp
)

message("Host System is: " ${CMAKE_HOST_SYSTEM_NAME})

foreach(tool ${tools})
    string(REPLACE "." ";" fn ${tool})
    list(GET fn 0 fn)
    add_tool(${fn} ${tool})
    if(${CMAKE_HOST_SYSTEM_NAME} MATCHES "Windows")
        install(TARGETS ${fn} DESTINATION D:/Path)
    elseif(${CMAKE_HOST_SYSTEM_NAME} MATCHES "Linux")
        install(TARGETS ${fn} DESTINATION ~/path)
    else()
        message(FATAL_ERROR "unknow platform")
    endif()
endforeach()
