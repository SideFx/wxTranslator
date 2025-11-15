/////////////////////////////////////////////////////////////////////////////
// Name:        translationfile.cpp
// Purpose:     Manage translation files and data
// Author:      Jan Buchholz
// Created:     2025-11-12
/////////////////////////////////////////////////////////////////////////////

#include "translationfile.h"
#include <iostream>
#include <fstream>
#include <utility>
#include <regex>
#include "definitions.h"
#include "jbconversion.hpp"
#include "appsettings.h"
#include "mobuilder.h"
#include <wx/wx.h>

void TranslationFile::init() {
    m_settings = {};
    m_translations = {};
    m_message = {};
    m_dirty = false;
}

bool TranslationFile::save(const std::string& fileName) {
    m_message = {};
    json j, t;
    json a = json::array();
    j[CONFIG_COMMON][CONFIG_COMMON_PROJECTFOLDER] = m_settings.project_folder;
    j[CONFIG_COMMON][CONFIG_COMMON_FILENAME] = m_settings.file_name;
    j[CONFIG_COMMON][CONFIG_COMMON_EXCLUSION] = m_settings.exclude_folders;
    for (auto& m : m_translations) {
        t[CONFIG_TRANSLATION][CONFIG_TRANSLATION_SOURCEFILE] = m.source_file;
        t[CONFIG_TRANSLATION][CONFIG_TRANSLATION_ORIGINALTEXT] = m.original;
        t[CONFIG_TRANSLATION][CONFIG_TRANSLATION_TRANSLATEDTEXT] = m.translation;
        t[CONFIG_TRANSLATION][CONFIG_TRANSLATION_STATUS] = m.status;
        a.push_back(t);
    }
    j[CONFIG_TRANSLATIONS_ARRAY] = a;
    std::ofstream ofs(fileName);
    bool b = ofs.is_open();
    if (b) {
        ofs << std::setw(4) << j << std::endl;
        ofs.close();
        m_dirty = false;
    } else {
        m_message.mtype = error;
        m_message.message = _("I/O error while saving translation file.");
    }
    return b;
}

bool TranslationFile::load(const std::string& fileName) {
    m_message = {};
    std::ifstream ifs(fileName);
    if (ifs.is_open()) {
        bool b = true;
        try {
            json j, t;
            json a = json::array();
            j = json::parse(ifs);
            ifs.close();
            m_settings = {};
            m_translations = {};
            mo_single_translation m;
            a = j[CONFIG_TRANSLATIONS_ARRAY];
            for (auto& item : a.items()) {
                t = item.value()[CONFIG_TRANSLATION];
                m.source_file = t[CONFIG_TRANSLATION_SOURCEFILE];
                m.original = t[CONFIG_TRANSLATION_ORIGINALTEXT];
                m.translation = t[CONFIG_TRANSLATION_TRANSLATEDTEXT];
                m.status = t[CONFIG_TRANSLATION_STATUS];
                m_translations.push_back(m);
            }
            m_settings.project_folder = j[CONFIG_COMMON][CONFIG_COMMON_PROJECTFOLDER];
            m_settings.file_name = fileName;
            m_settings.exclude_folders = j[CONFIG_COMMON][CONFIG_COMMON_EXCLUSION];
        }
        catch (json::parse_error&) {b = false;}
        catch (json::type_error&) {b = false;}
        catch (json::exception&) {b = false;}
        if (!b) {
            m_message.mtype = error;
            m_message.message = _("Failed to parse JSON in translation file.");
        }
        return b;
    }
    m_message.mtype = error;
    m_message.message = _("I/O error while loading translation file.");
    return false;
}

void TranslationFile::setSettings(mo_file_settings settings) {
    m_settings = std::move(settings);
}

mo_file_settings TranslationFile::getSettings() {
    return m_settings;
}

void TranslationFile::setDirty(bool dirty) {
    m_dirty = dirty;
}

bool TranslationFile::getDirty() {
    return m_dirty;
}

void TranslationFile::setTranslations(std::vector<mo_single_translation> translations) {
    m_translations = std::move(translations);
}

std::vector<mo_single_translation> TranslationFile::getTranslations() {
    return m_translations;
}

void TranslationFile::setMessage(mo_message m) {
    m_message = std::move(m);
}   

mo_message TranslationFile::getMessage() {
    return m_message;
}

bool TranslationFile::createMoFile() {
    //std::string moFileName = std::regex_replace(m_settings.file_name, std::regex(".wxtrans"), ".mo");
    std::string moFileName = std::regex_replace(m_settings.file_name, std::regex(FILE_EXT_WXTRANS), FILE_EXT_MO);
    MoBuilder* builder = new MoBuilder();
    bool b = builder->buildMoFile(m_translations, moFileName);
    m_message = builder->getMessage();
    delete builder;
    return b;
}

