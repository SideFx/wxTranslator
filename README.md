**wxTranslator (w) 2025 by Jan Buchholz**

wxTranslator is a utility that helps developers create and manage machine object `(.MO)` files for wxWidgets applications by extracting source text from wxWidgets translation macros - without requiring any external tools.

### Application Start
![Screenshot](images/img01.png)

### Application Preferences
![Screenshot](images/img02.png)
- Select C++ file extensions to scan
- Choose files/folders to exclude from scanning

### Create a New Translation File
![Screenshot](images/img03.png)
- Select the project folder
- Choose files/folders to exclude from scanning for the current project
- Provide the name and location of the translation file

### Open an Existing Translation File
![Screenshot](images/img04.png)
- Adjust settings if necessary

### Translation File Loaded
![Screenshot](images/img05.png)
- Select the source file using the list view on the left
- Select the text to be translated using the list view on the right
- Enter the translated text and commit changes
- Tool buttons (from left to right):
  - Move to previous text
  - Move to next text
  - Commit changes & automagically move to the next text

Don't forget to save the translation file when you're done.  
Click the highlighted toolbar icon to generate the final `.MO` file:  
![Screenshot](images/img07.png)

This will generate the final machine object `.MO` file.

wxTranslator was used to generate its German translation:  
![Screenshot](images/img06.png)

### Credits
- Niels Lohmann for [json.hpp](https://json.nlohmann.me/)
- The people who created and maintain [wxWidgets](https://wxwidgets.org/)
- Microsoft Copilot, which was an indispensable help during my very first delve into wxWidgets

### Updates
2025-11-13:
Added presets for Windows arm64 and msys2 clangarm64 toolchain to CMakePresets.json. Obviously there's no reliable method to detect the processor architecture in CMake at the moment. Tried a quirky workaround using PROCESSOR_IDENTIFIER, which works at least on my machines.

2025-11-14:
Added presets for macOS to CMakePresets.json. Made adaptions to CMakeLists.txt accordingly. Stored sash position in app preferences. Added default xy-offset and window size for Mainwindow at first startup. New shell script for MSYS2 setup on Windows arm64. Created macOS app.icns.

2025-11-15: Added logic to internally generate the machine object `.MO` file without requiring external utilities like `MSGFMT`. Updated the macOS app.icns. Numerous UI changes to improve macOS compatibility. Discovered that the build process on macOS produces flawed info.plist files [MacOS Tahoe 26.1: FilePicker and DirPicker not working #25973](https://github.com/wxWidgets/wxWidgets/issues/25973#issuecomment-3533524803), so removed the `MACOSX_BUNDLE` option from CMakeLists.txt as a workaround. 

2025-11-16: Fixed wxListCtrl column width on macOS. Pre-sorted filenames. Created release v1.0, including executables for Windows x64, Windows arm64 and macOS.

2025-11-17: Added a recommendation on how to build wxWidgets on macOS. See folder: `How to build wxWidgets`.