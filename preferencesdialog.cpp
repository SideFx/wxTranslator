//
// Created by janbu on 27.10.2025.
//

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

int PreferencesDialog::showDialog(app_settings preferences) {
    m_prefs = std::move(preferences);
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
    wxClientDC dc(m_dialog);
    dc.SetFont(wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT));
    int w, h;
    dc.GetTextExtent("X", &w, &h);
    m_inp_exclusion = new wxTextCtrl(m_dialog, wxID_ANY, wxEmptyString,
    wxDefaultPosition, wxSize(200, 3 * (h + 2)), wxTE_MULTILINE | wxTE_BESTWRAP);
    m_inp_exclusion->SetValue(m_prefs.exclude_folders);
    gridBagSizer->Add(m_inp_exclusion, wxGBPosition(1, 1), wxDefaultSpan, wxEXPAND);
    auto* lbl_msgfmt_path = new wxStaticText(m_dialog, wxID_ANY, _("Path to msgfmt tool:"));
    gridBagSizer->Add(lbl_msgfmt_path, wxGBPosition(2, 0),
        wxDefaultSpan, wxALIGN_CENTER_VERTICAL);
    m_filePicker = new wxFilePickerCtrl(m_dialog, wxID_ANY, "", "", "",
       wxDefaultPosition, wxDefaultSize,
       wxFLP_USE_TEXTCTRL | wxFLP_SMALL | wxFLP_FILE_MUST_EXIST);
    m_filePicker->SetFileName(toWxString(m_prefs.msgfmt_path));
    gridBagSizer->Add(m_filePicker, wxGBPosition(2, 1), wxDefaultSpan, wxEXPAND);
    auto* buttonBox = new wxBoxSizer(wxHORIZONTAL);
    auto* btn_ok = new wxButton(m_dialog, wxID_OK, CAP_OK);
    btn_ok->Bind(wxEVT_BUTTON, &PreferencesDialog::onOkClicked, this);
    auto* btn_cancel = new wxButton(m_dialog, wxID_CANCEL, CAP_CANCEL);
    btn_cancel->Bind(wxEVT_BUTTON, &PreferencesDialog::onCancelClicked, this);
    buttonBox->Add(btn_ok);
    buttonBox->Add(btn_cancel);
    gridBagSizer->Add(buttonBox, wxGBPosition(3, 1), wxDefaultSpan, wxEXPAND | wxALIGN_RIGHT);
    m_dialog->SetSizerAndFit(vBoxSizer);
    m_dialog->Layout();
    m_dialog->Fit();
    m_dialog->CenterOnParent();
    m_dialog->ShowModal();
    return m_dialog->GetReturnCode();
}

app_settings PreferencesDialog::getPreferences() {
    return m_prefs;
}

void PreferencesDialog::onOkClicked(wxCommandEvent& event) {
    m_prefs.exclude_folders = toStdString(m_inp_exclusion->GetValue()); ;
    m_prefs.msgfmt_path = toStdString(m_filePicker->GetFileName().GetFullPath());;
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
