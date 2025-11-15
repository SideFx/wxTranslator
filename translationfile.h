/////////////////////////////////////////////////////////////////////////////
// Name:        translationfile.h
// Purpose:     Header file for translationfile.cpp
// Author:      Jan Buchholz
// Created:     2025-11-12
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include "jbtypes.h"
#include "json.hpp"
using json = nlohmann::json;

class TranslationFile {

public:
    static void init();
    static bool load(const std::string& fileName);
    static bool save(const std::string& fileName);
    static void setSettings(mo_file_settings settings);
    static mo_file_settings getSettings();
    static void setDirty(bool dirty = true);
    static bool getDirty();
    static void setTranslations(std::vector<mo_single_translation> translations);
    static std::vector<mo_single_translation> getTranslations();
    static mo_message getMessage();
    static void setMessage(mo_message m);
    static bool createMoFile();
};

static mo_file_settings m_settings;
static std::vector<mo_single_translation> m_translations;
static mo_message m_message;
static bool m_dirty;
