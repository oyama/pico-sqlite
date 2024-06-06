# SQLite for Raspberry Pi Pico

This project enables [SQLite3](https://www.sqlite.org/) operation on the Raspberry Pi Pico, primarily utilizing the onboard flash memory's [littlefs](https://github.com/littlefs-project/littlefs), while also supporting various storage media and filesystems such as SD card's FAT. This ensures data persistence and flexible operation across a broad range of environments. The project provides an interactive shell accessible via UART or USB CDC, and a C/C++ client library. For details on the supported storage media and filesystems, please refer to the [pico-vfs](https://github.com/oyama/pico-vfs) documentation.

Fixes to the pico-sdk port can be found by diffing from the [git history](https://github.com/oyama/pico-sqlite/compare/8d49726..9ae8520). There are a few fallback and omitted functions. The rest is due to miscellaneous comment-outs.

## Build and Install

To compile and install this project, a setup with the [pico-sdk](https://github.com/raspberrypi/pico-sdk) is necessary. Please refer to [Getting Started with Raspberry Pi Pico](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf) to prepare your toolchain. This project incorporates [pico-vfs](https://github.com/oyama/pico-vfs) and [littlefs](https://github.com/littlefs-project/littlefs) as _git submodule_, which requires an update post-checkout.

```bash
git clone https://github.com/oyama/pico-sqlite.git
cd pico-sqlite
git submodule update --init --recursive

mkdir build; cd build;
PICO_SDK_PATH=/path/to/pico-sdk cmake ..
make sqlite3
```
After successful compilation, the `sqlite3.uf2` binary will be produced. Simply drag and drop this file onto your Raspberry Pi Pico while in BOOTSEL mode to install.
The firmware `sqlite3.uf2` runs as a serial device connected via USB. You can connect to the SQLite3 shell with a serial terminal such as `minicom`, `screen` or `PuTTY`.

## Use as a library

Add pico-sqlite to your project directory, with CMakeLists.txt as follows:
```CMakeLists.txt
cmake_minimum_required(VERSION 3.13...3.27)

include(pico-sqlite/vendor/pico_sdk_import.cmake)
add_subdirectory(pico-sqlite)

set(FAMILY rp2040)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
project(hello_sqlite C CXX ASM)
pico_sdk_init()


add_executable(main main.c)
target_compile_options(main PRIVATE)
target_link_libraries(main PRIVATE
  pico_stdlib
  libsqlite3
)
pico_enable_stdio_usb(main 1)
pico_add_extra_outputs(main)
pico_enable_filesystem(main AUTO_INIT TRUE)
```

`add_subdirectory(pico-sqlite)` and `libsqlite3` to `target_link_libraries` and `pico_enable_filesystem` For more information on `pico_enable_filesystem` See the [pico-vfs](https://github.com/oyama/pico-vfs) project.

## Limitations

While operational, this SQLite implementation on the Pico has limitations due to the constrained environment, including:

- Lots of limitations
- SQLite3 is significantly larger compared to the Pico. The binary size is about 610KB when built with the compiler option `-Os`, and 1MB when built without any specification.

## Licence

All code and documentation in this pico-sqlite repository are dedicated to the public domain by the authors.
