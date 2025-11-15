/////////////////////////////////////////////////////////////////////////////
// Name:        appsettings.h
// Purpose:     Header file for appsettings.cpp
// Author:      Jan Buchholz
// Created:     2025-11-12
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/wx.h>
#include "jbtypes.h"

class MainWindow; // forward declaration

class AppSettings {
public:
    static AppSettings& instance(MainWindow* mainWin = nullptr);
    // prohibit copying
    AppSettings(const AppSettings&) = delete;
    // prohibit overwrite
    AppSettings& operator=(const AppSettings&) = delete;
    void loadPreferences();
    void savePreferences();
    void openPreferencesDialog();
    mo_app_settings getAppSettings();

private:
    // private constructor with parent MainFrame
    explicit AppSettings(MainWindow* mainWin);

    MainWindow* m_mainWindow = nullptr;
    mo_app_settings m_prefs;
    std::string m_prefsPath;

    const int c_windowHeight = 800;
    const int c_windowWidth = 1280;
    const int c_sashPos = 200;
    const int c_windowPosX = 300;
    const int c_windowsPosY = 100;
};
