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
#include <wx/wx.h>

void TranslationFile::init() {
    m_settings = {};
    m_translations = {};
    m_message = {};
    m_dirty = false;
    m_poData = {};
    m_poFileName = "";
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
    std::ofstream o(fileName);
    bool b = o.good();
    if (b) {
        o << std::setw(4) << j << std::endl;
        o.close();
        m_dirty = false;
    } else {
        m_message.mtype = error;
        m_message.message = _("I/O error while saving translation file.");
    }
    return b;
}

bool TranslationFile::load(const std::string& fileName) {
    m_message = {};
    std::ifstream i(fileName);
    if (i.good()) {
        bool b = true;
        try {
            json j, t;
            json a = json::array();
            j = json::parse(i);
            i.close();
            m_settings = {};
            m_translations = {};
            single_translation m;
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

void TranslationFile::setSettings(file_settings settings) {
    m_settings = std::move(settings);
}

file_settings TranslationFile::getSettings() {
    return m_settings;
}

void TranslationFile::setDirty(bool dirty) {
    m_dirty = dirty;
}

bool TranslationFile::getDirty() {
    return m_dirty;
}

void TranslationFile::setTranslations(std::vector<single_translation> translations) {
    m_translations = std::move(translations);
}

std::vector<single_translation> TranslationFile::getTranslations() {
    return m_translations;
}

void TranslationFile::setMessage(message m) {
    m_message = std::move(m);
}   

message TranslationFile::getMessage() {
    return m_message;
}

bool TranslationFile::createPoFile() {
    std::string username = toStdString(wxGetUserId());
    m_poData = {};
    std::vector<std::string> dict{};
    m_poFileName = std::regex_replace(m_settings.file_name, std::regex(".wxtrans"), ".po");
    std::string app = std::string(APP_NAME) + SPACE + std::string(APP_VERSION);
    m_poData.push_back("# " + app);
    m_poData.push_back("msgid \"\"");
    m_poData.push_back("msgstr \"\"");
    m_poData.push_back("\"Mime-Version: 1.0\\n\"");
    m_poData.push_back("\"Content-Type: text/plain; charset=UTF-8\\n\"");
    m_poData.push_back("\"Content-Transfer-Encoding: 8bit\\n\"");
    m_poData.push_back("\"Last-Translator: " + username + "\\n\"");
    m_poData.push_back("\"X-Generator: " + app + "\\n\"");
    m_poData.push_back("");
    for (const auto& tr : m_translations) {
        bool skip_translation = false;
        for (const auto& line : dict) {
            if (tr.original == line) {
                skip_translation = true;
                break;
            }
        }
        if (!skip_translation) {
            dict.push_back(tr.original);
            m_poData.push_back(c_poLinePrefix + tr.source_file);
            std::string escapedOriginal = escapeSpecials(tr.original);
            std::string escapedTranslation = escapeSpecials(tr.translation);
            m_poData.push_back(c_poMsgId + c_poQuote + escapedOriginal + c_poQuote);
            m_poData.push_back(c_poMsgStr + c_poQuote + escapedTranslation + c_poQuote);
            m_poData.push_back("");
        }
    }
    std::ofstream o(m_poFileName);
    bool b = o.good();
    if (b) {
        for (const auto& line : m_poData) {
            o << line << std::endl;
        }
        o.close();
    } else {
        m_message.mtype = error;
        m_message.message = _("I/O error while creating PO file.");
    }
    return b;
}

bool TranslationFile::createMoFile() {
    bool b = createPoFile();
    if (!b) return false;
    AppSettings* appSettings = &AppSettings::instance();
    wxString msgfmtPath = toWxString(appSettings->getAppSettings().msgfmt_path);
    if (msgfmtPath.IsEmpty() || !wxFileExists(msgfmtPath)) {
        m_message.mtype = error;
        m_message.message = _("msgfmt tool not found. Please check the settings.");
        return false;
    }
    wxString moFileName = toWxString(std::regex_replace(m_settings.file_name, std::regex(".wxtrans"), ".mo"));
    wxString logFileName = toWxString(std::regex_replace(m_settings.file_name, std::regex(".wxtrans"), ".log"));
    wxString poFileName = toWxString(m_poFileName);
    #ifdef __WXMSW__
        wxString command = wxString::Format("cmd.exe /C \"%s -o \"%s\" \"%s\" > \"%s\" 2>&1\"", 
            msgfmtPath, moFileName, poFileName, logFileName);
    #else
        wxString command = wxString::Format("/bin/sh -c \"%s -o \"%s\" \"%s\" > \"%s\" 2>&1\"", 
            msgfmtPath, moFileName, poFileName, logFileName);
    #endif
    int result = wxExecute(command, wxEXEC_SYNC);
    if (result == 0 && wxFileExists(moFileName)) {
        m_message.mtype = information;
        m_message.message = _("MO file created successfully.");
        b = true;
    } else {
        std::string fileName = std::filesystem::path(toStdString(logFileName)).filename().string();
        m_message.mtype = error;
        m_message.message = _("Failed to create MO file. See log file for details: ") + toStdString(fileName);
        b = false;
    }   
    return b;
}

