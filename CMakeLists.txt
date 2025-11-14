cmake_minimum_required(VERSION 3.25)
project(wxTranslator)
set(CMAKE_CXX_STANDARD 20)
if(WIN32)
set(CMAKE_PREFIX_PATH C:/wxWidgets)
set(wxWidgets_ROOT_DIR C:/wxWidgets)
add_executable(wxTranslator WIN32
        main.cpp
        mainwindow.cpp
        mainwindow.h
        iconpool.h
        resource.rc app.ico
        definitions.h
        scanner.h
        scanner.cpp
        json.hpp
        preferencesdialog.cpp
        preferencesdialog.h
        appsettings.cpp
        appsettings.h
        jbtypes.h
        translationdialog.cpp
        translationdialog.h
        translationfile.cpp
        translationfile.h
        aboutdialog.cpp
        aboutdialog.h
        jbconversion.hpp
        logo.hpp
)
endif()
if(APPLE)
set(CMAKE_PREFIX_PATH /Users/Shared/wxWidgets)
set(wxWidgets_ROOT_DIR /Users/Shared/wxWidgets)
add_executable(wxTranslator
        main.cpp
        mainwindow.cpp
        mainwindow.h
        iconpool.h
        definitions.h
        scanner.h
        scanner.cpp
        json.hpp
        preferencesdialog.cpp
        preferencesdialog.h
        appsettings.cpp
        appsettings.h
        jbtypes.h
        translationdialog.cpp
        translationdialog.h
        translationfile.cpp
        translationfile.h
        aboutdialog.cpp
        aboutdialog.h
        jbconversion.hpp
        logo.hpp
        app.icns
)
endif()
find_package(wxWidgets REQUIRED COMPONENTS core base CONFIG)
target_link_libraries(wxTranslator PRIVATE ${wxWidgets_LIBRARIES})
set(TRANSLATION_DIR "${PROJECT_BINARY_DIR}/locale/de")

if(WIN32)
    if(NOT EXISTS ${TRANSLATION_DIR})
        file(MAKE_DIRECTORY ${TRANSLATION_DIR})
    endif()

    if(EXISTS "${CMAKE_SOURCE_DIR}/wxTranslate_DE.mo")
        add_custom_command(TARGET wxTranslator POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
                "${CMAKE_SOURCE_DIR}/wxTranslate_DE.mo"
                "${TRANSLATION_DIR}/wxTranslate_DE.mo"
        )
    endif()
endif()

if(APPLE)
    set(MACOSX_BUNDLE_ICON_FILE app.icns)
    set_source_files_properties(app.icns PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    set_target_properties(wxTranslator PROPERTIES
        MACOSX_BUNDLE TRUE
        RESOURCE app.icns
    )
endif()
