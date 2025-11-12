//
// Created by janbu on 27.10.2025.
//

#pragma once

#include <wx/wx.h>
#include <wx/filepicker.h>
#include "jbtypes.h"

class PreferencesDialog {
public:
    explicit PreferencesDialog(wxFrame* parent);
    ~PreferencesDialog();
    int showDialog(app_settings preferences);
    app_settings getPreferences();

private:
    wxDialog* m_dialog;
    wxFrame* m_parent;
    wxFilePickerCtrl* m_filePicker;
    wxTextCtrl* m_inp_exclusion;
    app_settings m_prefs;
    std::vector<wxCheckBox*> m_extensionBoxes;
    void onOkClicked(wxCommandEvent& event);
    void onCancelClicked(wxCommandEvent& event);
};


