//
// Created by janbu on 28.10.2025.
//

#include "appsettings.h"
#include <wx/stdpaths.h>
#include <wx/window.h>
#include "json.hpp"
#include "definitions.h"
#include "preferencesdialog.h"
#include <fstream>
#include "jbconversion.hpp"

using json = nlohmann::json;

AppSettings& AppSettings::instance(wxFrame* mainWin) {
    static AppSettings settings(mainWin);
    return settings;
}

// private constructor with optional mainWindow
AppSettings::AppSettings(wxFrame* mainWin) : m_mainWindow(mainWin) {
    m_prefs = {};
    m_prefs.extensions = {
        {".h", true},
        {".hpp", true},
        {".hxx", false},
        {".c", true},
        {".cpp", true},
        {".cxx", false}
    };
    m_prefsPath = toStdString(wxStandardPaths::Get().GetUserConfigDir());
}

//MainFrame* AppSettings::getMainWindow() const {
//    return m_mainWindow;
//}

void AppSettings::savePreferences() {
    wxFrame* frame = dynamic_cast<wxFrame*>(m_mainWindow);
    const auto pos = m_mainWindow->GetPosition();
    const auto size = m_mainWindow->GetSize();
    //const auto sash1pos = m_mainWindow->m
    m_prefs.coordinates = {pos.x, pos.y, size.x, size.y, m_mainWindow->IsMaximized()};
    const std::string fullPath = m_prefsPath + getPathSeparator() + APP_VENDOR + "." + APP_NAME + FILE_EXT_JSON;
    json j;
    j[CONFIG_WINDOW]["x"] = m_prefs.coordinates.pos_x;
    j[CONFIG_WINDOW]["y"] = m_prefs.coordinates.pos_y;
    j[CONFIG_WINDOW]["w"] = m_prefs.coordinates.size_w;
    j[CONFIG_WINDOW]["h"] = m_prefs.coordinates.size_h;
    j[CONFIG_WINDOW]["m"] = m_prefs.coordinates.maximized;
    j[CONFIG_COMMON][CONFIG_COMMON_EXCLUSION] = m_prefs.exclude_folders;
    j[CONFIG_COMMON][CONFIG_COMMON_MSGFMT] = m_prefs.msgfmt_path;
    for (const auto& ex : m_prefs.extensions) {
        j[CONFIG_COMMON][CONFIG_COMMON_EXTENSION + ex.first] = ex.second;
    }
    std::ofstream o(fullPath);
    if (o.good()) {
        o << std::setw(4) << j << std::endl;
        o.close();
    }
}

void AppSettings::loadPreferences() {
    const std::string fullPath = m_prefsPath + getPathSeparator() + APP_VENDOR + "." + APP_NAME + FILE_EXT_JSON;
    std::ifstream i(fullPath);
    if (i.good()) {
        try {
            json j = json::parse(i);
            i.close();
            m_prefs.msgfmt_path = j[CONFIG_COMMON][CONFIG_COMMON_MSGFMT];
            m_prefs.exclude_folders = j[CONFIG_COMMON][CONFIG_COMMON_EXCLUSION];
            m_prefs.coordinates.pos_x = j[CONFIG_WINDOW]["x"];
            m_prefs.coordinates.pos_y = j[CONFIG_WINDOW]["y"];
            m_prefs.coordinates.size_w = j[CONFIG_WINDOW]["w"];
            m_prefs.coordinates.size_h = j[CONFIG_WINDOW]["h"];
            m_prefs.coordinates.maximized = j[CONFIG_WINDOW]["m"];
            for (auto& ex : m_prefs.extensions) {
                ex.second = j[CONFIG_COMMON][CONFIG_COMMON_EXTENSION + ex.first];
            }
        }
        catch (json::parse_error&) {}
        catch (json::type_error&) {}
        catch (json::exception&) {}
    }
    if (m_prefs.coordinates.size_h == 0 || m_prefs.coordinates.size_w == 0) {
        m_prefs.coordinates.size_h = windowHeight;
        m_prefs.coordinates.size_w = windowWidth;
    }
    const wxPoint pt(m_prefs.coordinates.pos_x, m_prefs.coordinates.pos_y);
    m_mainWindow->Move(pt);
    m_mainWindow->SetSize(wxSize(m_prefs.coordinates.size_w, m_prefs.coordinates.size_h));
    m_mainWindow->Maximize(m_prefs.coordinates.maximized);
}

void AppSettings::openPreferencesDialog() {
    auto *dlg = new PreferencesDialog(m_mainWindow);
    if (dlg->showDialog(m_prefs) == wxID_OK) {
        m_prefs = dlg->getPreferences();
    };
    delete dlg;
}

app_settings AppSettings::getAppSettings() {
    return m_prefs;
}
