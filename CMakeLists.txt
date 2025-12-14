cmake_minimum_required(VERSION 3.25)
project(wxTranslator)
set(CMAKE_CXX_STANDARD 20)
set(MO_FILE wxTranslate_DE.mo)
if(WIN32)
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
        mobuilder.cpp
        mobuilder.h
        logo.hpp
)
add_custom_command(TARGET wxTranslator POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:wxTranslator>/de"
)
if(EXISTS "${CMAKE_SOURCE_DIR}/${MO_FILE}")
    add_custom_command(TARGET wxTranslator POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/${MO_FILE}"
                "$<TARGET_FILE_DIR:wxTranslator>/de"
    )
endif()    
endif()

if(APPLE)
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
        mobuilder.cpp
        mobuilder.h
        logo.hpp
        app.icns
)
endif()
find_package(wxWidgets REQUIRED COMPONENTS core base CONFIG)
target_link_libraries(wxTranslator PRIVATE ${wxWidgets_LIBRARIES})

if(APPLE)
    set(MACOSX_BUNDLE_ICON_FILE app.icns)
    set_source_files_properties(app.icns PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    set_target_properties(wxTranslator PROPERTIES
        MACOSX_BUNDLE TRUE
        RESOURCE app.icns
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/Info.plist
    )
    add_custom_command(TARGET wxTranslator POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:wxTranslator>/../Frameworks"
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:wxTranslator>/../Resources/de.lproj"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  "${wxWidgets_ROOT_DIR}/lib/libwx_baseu-3.3*.dylib"
          "$<TARGET_FILE_DIR:wxTranslator>/../Frameworks"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  "${wxWidgets_ROOT_DIR}/lib/libwx_osx_cocoau_core-3.3*.dylib"
          "$<TARGET_FILE_DIR:wxTranslator>/../Frameworks" 
        COMMAND install_name_tool -add_rpath "@executable_path/../Frameworks"
            "$<TARGET_FILE:wxTranslator>" COMMENT "Adjusting install names for wxWidgets libs"   
    )
    if(EXISTS "${CMAKE_SOURCE_DIR}/${MO_FILE}")
    add_custom_command(TARGET wxTranslator POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/${MO_FILE}"
                "$<TARGET_FILE_DIR:wxTranslator>/../Resources/de.lproj"
    )
    endif()    
endif()
