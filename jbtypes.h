/////////////////////////////////////////////////////////////////////////////
// Name:        jbtypes.h
// Purpose:     Type and enum definitions for wxTranslator
// Author:      Jan Buchholz
// Created:     2025-11-12
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include <map>
#include <string>
#include <cstdint>
#include <vector>
#include <wx/defs.h>

enum displayMode {wxNONE, wxNEW, wxOPEN };
enum messageType {information, warning, error, question};
enum translationStatus { untranslated, translated, newtext };
enum { ID_MOVE_UP = wxID_HIGHEST + 1, ID_MOVE_DOWN, ID_SET_TRANSLATED, ID_MAKE_MO_FILE };

struct mo_window_coordinates{
    int pos_x;
    int pos_y;
    int size_w;
    int size_h;
    bool maximized;
    int sashpos;
};

using mt_extensions = std::map<std::string, bool>;

struct mo_app_settings {
    mo_window_coordinates coordinates;
    mt_extensions extensions;
    std::string exclude_folders;
};

struct mo_file_settings {
    std::string file_name;
    std::string project_folder;
    std::string exclude_folders;
};

struct mo_single_translation{
    std::string source_file;
    std::string original;
    std::string translation;
    translationStatus status;
};

struct mo_message{
    messageType mtype;
    std::string message;
};

struct mo_translationFileData{
    mo_file_settings m_settings;
    std::vector<mo_single_translation> m_translations;
    mo_message m_message;
    bool m_dirty;
};

struct mo_header {
    uint32_t magic;                 // 0x950412de (Little Endian) or 0xde120495 (Big Endian)
    uint32_t revision;              // set to 0
    uint32_t num_strings;           // number of der msgid/msgstr pairs
    uint32_t orig_tab_offset;       // offset originals strings table
    uint32_t trans_tab_offset;      // offset translations strings table
    uint32_t hash_tab_offset;       // optional, set to 0
    uint32_t hash_tab_size;         // optional, set to 0
};

struct mo_entry {
    uint32_t length;  // string size in bytes (without Null terminator)
    uint32_t offset;  // offset in file, where string begins
};

using mt_moentries = std::vector<mo_entry>;
using mt_translations = std::vector<mo_single_translation>;

