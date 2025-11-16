/////////////////////////////////////////////////////////////////////////////
// Name:        main.cpp
// Purpose:     Main application file
// Author:      Jan Buchholz
// Created:     2025-11-12
/////////////////////////////////////////////////////////////////////////////

#include <wx/wx.h>
#include "mainwindow.h"

class MyApp final : public wxApp {
public:
    bool OnInit() override;
    wxLocale m_locale;
};

bool MyApp::OnInit() {
    auto lang = static_cast<wxLanguage>(wxLocale::GetSystemLanguage());
    if (lang >= wxLANGUAGE_GERMAN && lang <= wxLANGUAGE_GERMAN_SWISS)
    {
        if (m_locale.Init(lang, wxLOCALE_LOAD_DEFAULT)) {
             wxLocale::AddCatalogLookupPathPrefix(wxGetCwd() + "/locale");
            m_locale.AddCatalog("wxTranslate_DE");
        }
    }
    wxImage::AddHandler(new wxPNGHandler());
    auto* wnd = new MainWindow();
    wnd->Show(true);
    wnd->m_appSettings->loadPreferences();
    return true;
}

wxIMPLEMENT_APP(MyApp);

