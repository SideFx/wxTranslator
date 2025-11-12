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
    static void setSettings(file_settings settings);
    static file_settings getSettings();
    static void setDirty(bool dirty = true);
    static bool getDirty();
    static void setTranslations(std::vector<single_translation> translations);
    static std::vector<single_translation> getTranslations();
    static message getMessage();
    static void setMessage(message m);
    static bool createPoFile();
    static bool createMoFile();
};

static file_settings m_settings;
static std::vector<single_translation> m_translations;
static message m_message;
static bool m_dirty;
static std::vector<std::string> m_poData;
static std::string m_poFileName;

const std::string c_poLinePrefix = "#: ";
const std::string c_poMsgId = "msgid ";
const std::string c_poMsgStr = "msgstr ";
const std::string c_poQuote = "\"";
