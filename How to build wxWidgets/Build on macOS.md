### Building wxWidgets on macOS

If you haven't already, install Xcode.

Then proceed as follows:

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
  `cmake -G "Ninja" ../wxWidgets -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/Users/Shared/wxWidgets`
- If you want to install wxWidgets to a different location, adjust the `CMAKE_INSTALL_PREFIX` parameter accordingly.
- Build and install wxWidgets:  
  `cmake --build . --target install`
- Add `/Users/Shared/wxWidgets/bin` to your system `PATH` so that applications can locate the wxWidgets framework.


