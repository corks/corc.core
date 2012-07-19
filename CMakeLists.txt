cmake_minimum_required(VERSION 2.8.7)
project(corc.core C)

set(BUILD_SHARED_LIBS ON)

set(CMAKE_BUILD_TYPE Debug)

if(CMAKE_C_COMPILER MATCHES "gcc" OR "clang"
        OR "$gcc.*" OR "$clang.*")
    set(CMAKE_C_FLAGS_DEBUG "-O0 -g -Wall -Wextra")
    set(CMAKE_C_FLAGS_RELEASE "-O2")
    set(CMAKE_C_FLAGS_OPTDEBUG "-O2 -Wall -Wextra")
elseif(CMAKE_C_COMPILER MATCHES "icc")
    set(CMAKE_C_FLAGS_DEBUG 
        "-g -O0 -w2 -Wall -diag-enable thread,port-win,warn,error,remark,vec,par")
    set(CMAKE_C_FLAGS_RELEASE "-O2") 
    set(CMAKE_C_FLAGS_OPTDEBUG "-O2 -w2 -Wall -diag-enable
    thread,port-win,warn,error,remark,vec,par -opt-report -opt-report-level
    max -vec-report3 -fno-inline")
elseif(CMAKE_C_COMPILER MATCHES "pathcc" OR "opencc"
        OR "$pathcc-.*" OR "$opencc-.*")
    set(CMAKE_C_FLAGS_DEBUG "-g3 -O0 -W -Wall")
    set(CMAKE_C_FLAGS_RELEASE "-O2 -ipa -inline")
    set(CMAKE_C_FLAGS_OPTDEBUG "-g3 -noinline -W -Wall")
endif()

add_subdirectory(src)
