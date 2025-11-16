/////////////////////////////////////////////////////////////////////////////
// Name:        preferencesdialog.cpp
// Purpose:     The preferences dialog implementation
// Author:      Jan Buchholz
// Created:     2025-11-12
/////////////////////////////////////////////////////////////////////////////

#include "preferencesdialog.h"
#include "definitions.h"
#include "jbconversion.hpp"
#include <wx/gbsizer.h>

PreferencesDialog::PreferencesDialog(wxFrame* parent) {
    m_parent = parent;
    m_prefs = {};
    m_filePicker = nullptr;
    m_inp_exclusion = nullptr;
    m_extensionBoxes.clear();
    m_dialog = new wxDialog(parent, wxID_ANY, TITLE_PREFERENCES, wxDefaultPosition, wxDefaultSize);
    m_dialog->SetBackgroundColour(wxColor(* wxWHITE));
    m_dialog->SetWindowStyle(wxCAPTION | wxCLOSE_BOX);
}

PreferencesDialog::~PreferencesDialog() = default;

int PreferencesDialog::showDialog(mo_app_settings preferences) {
    m_prefs = std::move(preferences);
    const int baseWidth = wxSystemSettings::GetMetric(wxSYS_SCREEN_X) / 4;
    auto* vBoxSizer = new wxBoxSizer(wxVERTICAL);
    auto* gridBagSizer = new wxGridBagSizer(10, 10);
    vBoxSizer->Add(gridBagSizer, 1, wxEXPAND | wxALL, 30);
    auto* lbl_file_extensions = new wxStaticText(m_dialog, wxID_ANY,
        _("Scan files for wx translation\nmacros:"));
    gridBagSizer->Add(lbl_file_extensions, wxGBPosition(0, 0),
        wxDefaultSpan, wxALIGN_CENTER_VERTICAL);
    auto* gridSizer = new wxGridSizer(6, 10, 10);
    for (auto& p : m_prefs.extensions) {
        auto* ch = new wxCheckBox(m_dialog, wxID_ANY, p.first);
        ch->SetName(toWxString(p.first));
        ch->SetValue(p.second);
        m_extensionBoxes.push_back(ch);
        gridSizer->Add(ch, 0, wxALL, 5);
    }
    gridBagSizer->Add(gridSizer, wxGBPosition(0, 1), wxDefaultSpan, wxEXPAND);
    auto* lbl_exclude_folders = new wxStaticText(m_dialog, wxID_ANY, TEXT_EXCLUDE_FOLDERS);
    gridBagSizer->Add(lbl_exclude_folders, wxGBPosition(1, 0),
        wxDefaultSpan, wxALIGN_CENTER_VERTICAL);
    m_inp_exclusion = new wxTextCtrl(m_dialog, wxID_ANY, wxEmptyString,
    wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_BESTWRAP);
    int lineHeight = m_inp_exclusion->GetCharHeight();
    m_inp_exclusion->SetMinSize(wxSize(baseWidth, (lineHeight + 3) * 4));
    m_inp_exclusion->SetValue(m_prefs.exclude_folders);
    gridBagSizer->Add(m_inp_exclusion, wxGBPosition(1, 1), wxDefaultSpan, wxEXPAND);
    auto* buttonBox = new wxBoxSizer(wxHORIZONTAL);
    auto* btn_ok = new wxButton(m_dialog, wxID_OK, CAP_OK);
    btn_ok->Bind(wxEVT_BUTTON, &PreferencesDialog::onOkClicked, this);
    auto* btn_cancel = new wxButton(m_dialog, wxID_CANCEL, CAP_CANCEL);
    btn_cancel->Bind(wxEVT_BUTTON, &PreferencesDialog::onCancelClicked, this);
    buttonBox->Add(btn_ok);
    buttonBox->Add(btn_cancel);
    gridBagSizer->Add(buttonBox, wxGBPosition(2, 1), wxDefaultSpan, wxEXPAND | wxALIGN_RIGHT);
    m_dialog->SetSizerAndFit(vBoxSizer);
    m_dialog->Layout();
    m_dialog->Fit();
    m_dialog->CenterOnParent();
    m_dialog->ShowModal();
    return m_dialog->GetReturnCode();
}

mo_app_settings PreferencesDialog::getPreferences() {
    return m_prefs;
}

void PreferencesDialog::onOkClicked(wxCommandEvent& event) {
    m_prefs.exclude_folders = toStdString(m_inp_exclusion->GetValue()); ;
    for (auto& ch : m_extensionBoxes) {
        for (auto& p : m_prefs.extensions) {
            if (p.first == toStdString(ch->GetName())) {
                p.second = ch->GetValue();
                break;
            }
        }
    }
    m_dialog->EndModal(wxID_OK);
}

void PreferencesDialog::onCancelClicked(wxCommandEvent& event) {
    m_dialog->EndModal(wxID_CANCEL);
}
