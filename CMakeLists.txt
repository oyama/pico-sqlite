cmake_minimum_required(VERSION 3.13...3.27)

include(vendor/pico_sdk_import.cmake)
add_subdirectory(vendor/pico-vfs)

project(sqlite3 C CXX ASM)
set(FAMILY rp2040)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(sqlite3
  src/shell.c
  src/sqlite3.c
  src/fallback.c
)
target_include_directories(sqlite3 PRIVATE src)
target_compile_options(sqlite3 PRIVATE
  -Os
  -Wno-unused-parameter -Wno-implicit-fallthrough -Wno-char-subscripts
  -Wno-unused-but-set-variable -Wno-missing-field-initializers
  -Wno-unused-variable -Wno-unused-value
  -DPICO_SDK=1
  -DHAVE_NANOSLEEP=0
  -DSQLITE_DEFAULT_MMAP_SIZE=0
  -DSQLITE_DEFAULT_WORKER_THREADS=0
  -DSQLITE_DISABLE_DIRSYNC=1
  -DSQLITE_ENABLE_LOCKING_STYLE=0
  -DSQLITE_MAX_MMAP_SIZE=0
  -DSQLITE_MAX_WORKER_THREADS=0
  -DSQLITE_OMIT_AUTHORIZATION
  -DSQLITE_OMIT_LOAD_EXTENSION
  -DSQLITE_OMIT_LOCALTIME
  -DSQLITE_OMIT_POPEN
  -DSQLITE_OMIT_RANDOMNESS
  -DSQLITE_OMIT_WAL
  -DSQLITE_THREADSAFE=0
)
target_link_libraries(sqlite3 PRIVATE pico_stdlib)
target_link_options(sqlite3 PRIVATE -Wl,--print-memory-usage)

pico_enable_stdio_usb(sqlite3 1)
pico_enable_filesystem(sqlite3 SIZE 1048576 AUTO_INIT TRUE)
pico_add_extra_outputs(sqlite3)


find_program(OPENOCD openocd)
if(OPENOCD)
  add_custom_target(flash
    COMMAND ${OPENOCD} -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c "adapter speed 5000" -c "program ${CMAKE_PROJECT_NAME}.elf verify reset exit"
    DEPENDS ${CMAKE_PROJECT_NAME}
  )
endif()
