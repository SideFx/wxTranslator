/////////////////////////////////////////////////////////////////////////////
// Name:        definitions.h
// Purpose:     Text snippets and constants for wxTranslator
// Author:      Jan Buchholz
// Created:     2025-11-12
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/string.h>

#define SPACE std::string(" ")

#define APP_NAME "wxTranslator"
#define APP_VERSION "v1.0"
#define APP_VENDOR "org.janbuchholz"
#define APP_AUTHOR_STRING "(w) 2025 Jan Buchholz\n"

#define MENU_FILE _("File")
#define MENU_EDIT _("Edit")
#define MENU_HELP _("Help")

#define MENU_FILE_NEW _("&New\tCtrl-N")
#define MENU_FILE_OPEN _("&Open\tCtrl-O")
#define MENU_FILE_SAVE _("&Save\tCtrl-S")
#define MENU_FILE_EXIT _("&Quit\tCtrl-Q")

#define MENU_EDIT_PREFERENCES _("&Preferences")
#define MENU_EDIT_MAKE_MO_FILE _("Create .mo file")

#define MENU_HELP_ABOUT _("&About")

#define TIP_FILE_OPEN _("Open translation file")
#define TIP_FILE_SAVE _("Save translation file")
#define TIP_FILE_EXIT _("Quit wxTranslator")
#define TIP_EDIT_PREFERENCES _("Application preferences")
#define TIP_EDIT_MAKE_MO_FILE _("Create machine object (.mo) file")
#define TIP_PREVIOUS_TEXT _("Move to previous text")
#define TIP_NEXT_TEXT _("Move to next text")
#define TIP_SET_TRANSLATED _("Mark text as translated")

#define TEXT_EXCLUDE_FOLDERS _("Exclude files/folders from\nscanning, such as build\ndirectories or third-party\nlibraries:")

#define TITLE_PREFERENCES (APP_NAME + SPACE + _("Preferences"))
#define TITLE_TRANSLATION_SETTINGS _("Translation project settings")

#define CONFIG_WINDOW "window"
#define CONFIG_WINDOW_SPLITTER1 "window/splitter1/sash"
#define CONFIG_COMMON "common"
#define CONFIG_COMMON_EXTENSION "extension"
#define CONFIG_COMMON_EXCLUSION "exclusion"
#define CONFIG_COMMON_PROJECTFOLDER "projectfolder"
#define CONFIG_COMMON_FILENAME "filename"
#define CONFIG_TRANSLATION "translation"
#define CONFIG_TRANSLATIONS_ARRAY "translationarray"
#define CONFIG_TRANSLATION_SOURCEFILE "sourcefile"
#define CONFIG_TRANSLATION_ORIGINALTEXT "originaltext"
#define CONFIG_TRANSLATION_TRANSLATEDTEXT "translatedtext"
#define CONFIG_TRANSLATION_STATUS "status"

#define FILE_EXT_JSON ".json"
#define FILE_EXT_WXTRANS ".wxtrans"
#define FILE_EXT_MO ".mo"

#define TRANSLATION_FILE_FILTER _("wxTranslator files (*.wxtrans)|*.wxtrans")

#define TEXT_UNSAVED_CHANGES _("There are unsaved changes. Do you want to save them before exiting?")

#define STATUS_NEW _("New text")
#define STATUS_UNTRANSLATED _("Untranslated")
#define STATUS_TRANSLATED _("Translated")
#define STATUS_UNKNOWN _("Unknown")

#define CAP_OK _("OK")
#define CAP_CANCEL _("Cancel") 
#define CAP_CLOSE _("Close")

#define UNI_CREATE_TRANSLATION_FILE _("Create a new translation file")
#define UNI_HELP_ABOUT _("About") + SPACE + APP_NAME

#define DIALOG_ABOUT _("wxTranslator is a tool to help developers to create\nand manage translation files for wxWidgets applications.")
// https://json.nlohmann.me/
// https://wxwidgets.org/
#define DIALOG_CREDITS _("Credits go to Niels Lohmann for 'json.hpp'\nhttps://json.nlohmann.me/\nand to the wxWidgets community\nhttps://wxwidgets.org/")
