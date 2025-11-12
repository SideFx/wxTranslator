//
// Created by janbu on 28.10.2025.
//

#pragma once

#include <wx/wx.h>
#include "jbtypes.h"

class MainFrame; // forward declaration

class AppSettings {
public:
    static AppSettings& instance(wxFrame* mainWin = nullptr);
    // prohibit copying
    AppSettings(const AppSettings&) = delete;
    // prohibit overwrite
    AppSettings& operator=(const AppSettings&) = delete;
    //[[nodiscard]] MainFrame* getMainWindow() const;
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
