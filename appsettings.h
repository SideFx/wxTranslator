/////////////////////////////////////////////////////////////////////////////
// Name:        appsettings.h
// Purpose:     Header file for appsettings.cpp
// Author:      Jan Buchholz
// Created:     2025-11-12
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/wx.h>
#include "jbtypes.h"

class AppSettings {
public:
    static AppSettings& instance(wxFrame* mainWin = nullptr);
    // prohibit copying
    AppSettings(const AppSettings&) = delete;
    // prohibit overwrite
    AppSettings& operator=(const AppSettings&) = delete;
    void loadPreferences();
    void savePreferences();
    void openPreferencesDialog();
    app_settings getAppSettings();

private:
    // private constructor with parent MainFrame
    explicit AppSettings(wxFrame* mainWin);

    wxFrame* m_mainWindow = nullptr;
    app_settings m_prefs;
    std::string m_prefsPath;

    const int windowHeight = 600;
    const int windowWidth = 800;
};
