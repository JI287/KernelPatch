cmake_minimum_required(VERSION 3.18)
project(kpms LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

find_package(KMOD REQUIRED)

add_library(kpms MODULE
    main.c
    hook.c
)

target_compile_options(kpms PRIVATE
    -Wall
    -Wextra
    -ffreestanding
    -nostdinc
)

set_target_properties(kpms PROPERTIES
    PREFIX ""
    SUFFIX ".ko"
)
