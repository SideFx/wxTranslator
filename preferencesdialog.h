/////////////////////////////////////////////////////////////////////////////
// Name:        preferencesdialog.h
// Purpose:     Header file for preferencesdialog.cpp
// Author:      Jan Buchholz
// Created:     2025-11-12
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/wx.h>
#include <wx/filepicker.h>
#include "jbtypes.h"

class PreferencesDialog {
public:
    explicit PreferencesDialog(wxFrame* parent);
    ~PreferencesDialog();
    int showDialog(mo_app_settings preferences);
    mo_app_settings getPreferences();

private:
    wxDialog* m_dialog;
    wxFrame* m_parent;
    wxFilePickerCtrl* m_filePicker;
    wxTextCtrl* m_inp_exclusion;
    mo_app_settings m_prefs;
    std::vector<wxCheckBox*> m_extensionBoxes;
    void onOkClicked(wxCommandEvent& event);
    void onCancelClicked(wxCommandEvent& event);
};


