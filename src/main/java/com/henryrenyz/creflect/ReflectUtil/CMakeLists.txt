cmake_minimum_required(VERSION 3.17)
project(ReflectLibImpl C)

set(CMAKE_C_STANDARD 11)

include_directories($ENV{JAVA_HOME}/include)
include_directories($ENV{JAVA_HOME}/include/win32)

add_library(ReflectUtil SHARED
        com_henryrenyz_creflect_ReflectLibImpl.h
            ReflectUtil.c util.c util.h)
