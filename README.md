# Chaser Drone IMU

## Introduction

This repository is a drone attitude measurement solution with 9-axis.

The sensors are used as follow:

- MS5611
- HMC5983
- ICM20608/ICM20602

## Develop Environment

The environment of this project is based on Makefile and VSCode.

### On Windows

- Install [gcc-arm-none-eabi](https://armkeil.blob.core.windows.net/developer/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-win32.exe)
- Install [Jlink flasher](https://www.segger.com/downloads/flasher/Flasher_Windows_V760e_x86_64.exe)
- Type the follow commands in the workspace folder:

```bash
mingw32-make
.\firmware_download.bat
```

