cmake_minimum_required(VERSION 3.13...3.27)

include(vendor/pico_sdk_import.cmake)
add_subdirectory(vendor/pico-vfs)

project(sqlite C CXX ASM)
set(FAMILY rp2040)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(sqlite
  src/shell.c
  src/sqlite3.c
)
target_include_directories(sqlite PRIVATE src)
target_link_libraries(sqlite PRIVATE pico_stdlib)
target_link_options(sqlite PRIVATE -Wl,--print-memory-usage)
target_compile_options(sqlite PRIVATE -DENABLE_TRACE)

pico_enable_stdio_usb(sqlite 1)
pico_enable_filesystem(sqlite AUTO_INIT TRUE)
pico_add_extra_outputs(sqlite)


find_program(OPENOCD openocd)
if(OPENOCD)
  add_custom_target(flash
    COMMAND ${OPENOCD} -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c "adapter speed 5000" -c "program ${CMAKE_PROJECT_NAME}.elf verify reset exit"
    DEPENDS ${CMAKE_PROJECT_NAME}
  )
endif()

