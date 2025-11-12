/////////////////////////////////////////////////////////////////////////////
// Name:        jbtypes.h
// Purpose:     Type and enum definitions for wxTranslator
// Author:      Jan Buchholz
// Created:     2025-11-12
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include <map>
#include <string>
#include <vector>
#include <wx/defs.h>

enum displayMode {wxNONE, wxNEW, wxOPEN };
enum messageType {information, warning, error, question};
enum translationStatus { untranslated, translated, newtext };
enum { ID_MOVE_UP = wxID_HIGHEST + 1, ID_MOVE_DOWN, ID_SET_TRANSLATED, ID_MAKE_MO_FILE };

typedef struct {
    int pos_x;
    int pos_y;
    int size_w;
    int size_h;
    bool maximized;
    int sash1pos;
} window_coordinates;

typedef std::map<std::string, bool> extensions_t;

typedef struct {
    window_coordinates coordinates;
    extensions_t extensions;
    std::string msgfmt_path;
    std::string exclude_folders;
} app_settings;

typedef struct {
    std::string file_name;
    std::string project_folder;
    std::string exclude_folders;
} file_settings;

typedef struct {
    std::string source_file;
    std::string original;
    std::string translation;
    translationStatus status;
} single_translation;

typedef struct {
    messageType mtype;
    std::string message;
} message;

typedef struct {
    file_settings m_settings;
    std::vector<single_translation> m_translations;
    message m_message;
    bool m_dirty;
} translationFileData;
