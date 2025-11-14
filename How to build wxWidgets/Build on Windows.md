### Building wxWidgets with MSYS2

First, install MSYS2 from [https://www.msys2.org/](https://www.msys2.org/).

Then proceed as follows:

- Launch either the **UCRT64** (Windows x64) or **CLANGARM64** (Windows arm64) console
- Update the toolchain using pacman:  
  `pacman -Syu`
- Copy the appropriate included shell script to your home directory and execute it (This will install all necessary packages required to build the wxWidgets framework)
- Create a `git` folder in your home directory:  
  `mkdir git`
- Change into that directory:  
  `cd git`
- Clone wxWidgets from GitHub:  
  `git clone --recursive https://github.com/wxWidgets/wxWidgets`
- Create a build directory:  
  `mkdir build-wxWidgets`
- Enter the build directory:  
  `cd build-wxWidgets`
- Run CMake to configure the build:  
  `cmake -G "MSYS Makefiles" ../wxWidgets -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=c:/wxWidgets`
- If you want to install wxWidgets to a different location, adjust the `CMAKE_INSTALL_PREFIX` parameter accordingly
- Build and install wxWidgets:  
  `cmake --build . --target install`
- Add `c:/wxWidgets/bin` to your system `PATH` so that applications can find the wxWidgets .DLL libraries
- Copy `c:/wxWidgets/lib/wx/config/msw-unicode-3.3` to `c:/wxWidgets/bin` and rename it to `wx-config` 

