# Polling Rate Viewer

A program to view your mouse's polling rate.

## Usage

- Download the latest release from [GitHub Releases](https://github.com/Aetopia/Polling.Rate.Viewer/releases).

- Run the program & rapidly start to move your mouse.

- The program will display the detected polling rate on a 1 second interval.

## Building
1. Install [MSYS2](https://www.msys2.org/) & [UPX](https://upx.github.io/) for optional compression.
2. Update the MSYS2 Environment until there are no pending updates using:

    ```bash
    pacman -Syu --noconfirm
    ```

3. Install GCC & [MinHook](https://github.com/TsudaKageyu/minhook) using:

    ```bash
    pacman -S mingw-w64-ucrt-x86_64-gcc --noconfirm
    ```

3. Make sure `<MSYS2 Installation Directory>\ucrt64\bin` is added to the Windows `PATH` environment variable.
4. Run [`Build.cmd`](src/Build.cmd).
