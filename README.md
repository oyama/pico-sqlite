# SQLite for Raspberry Pi Pico

This project enables the operation of [SQLite3](https://www.sqlite.org/) on a Raspberry Pi Pico. The database utilizes the onboard flash memory, interfaced through the [littlefs](https://github.com/littlefs-project/littlefs) file system, enabling data persistence and manipulation via a straightforward SQLite3 interface. Interaction with the database can be done interactively via UART or USB CDC.

This project ports SQLite3 and an interactive shell to the pico-sdk environment. Fixes to the pico-sdk port can be found by diffing from the [git history](https://github.com/oyama/pico-sqlite/compare/8d49726..9ae8520). There are a few fallback and omitted functions. The rest is due to miscellaneous comment-outs.

## Build and Install

To compile and install this project, a setup with the [pico-sdk](https://github.com/raspberrypi/pico-sdk) is necessary. Please refer to [Getting Started with Raspberry Pi Pico](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf) to prepare your toolchain. This project incorporates [pico-vfs](https://github.com/oyama/pico-vfs) and [littlefs](https://github.com/littlefs-project/littlefs) as _git submodule_, which requires an update post-checkout.

```bash
git clone https://github.com/oyama/pico-sqlite.git
cd pico-sqlite
git submodule update --init --recursive

mkdir build; cd build;
PICO_SDK_PATH=/path/to/pico-sdk cmake ..
make
```
After successful compilation, the `sqlite3.uf2` binary will be produced. Simply drag and drop this file onto your Raspberry Pi Pico while in BOOTSEL mode to install.

## Limitations

While operational, this SQLite implementation on the Pico has limitations due to the constrained environment, including:

- Lots of limitations
- SQLite3 is significantly larger compared to the Pico. The binary size is about 630KB when built with the compiler option `-Os`, and 1MB when built without any specification.

## Licence

All code and documentation in this pico-sqlite repository are dedicated to the public domain by the authors.
