//
// Created by janbu on 30.10.2025.
//

#include "translationdialog.h"
#include "definitions.h"
#include <wx/sizer.h>
#include <wx/filefn.h>
#include "jbconversion.hpp"

TranslationDialog::TranslationDialog(wxFrame* parent) {
    m_parent = parent;
    m_dirPicker = nullptr;
    m_filePicker = nullptr;
    m_inp_exclusion = nullptr;
    m_okButton = nullptr;
    m_cancelButton = nullptr;
    m_tf = nullptr;
    m_mode = displayMode::wxNONE;
    m_message = {};
    m_dialog = new wxDialog(parent, wxID_ANY, wxEmptyString,
        wxDefaultPosition, wxDefaultSize);
    m_dialog->SetBackgroundColour(wxColor(* wxWHITE));
    m_dialog->SetWindowStyle(wxCAPTION | wxCLOSE_BOX);
    m_dialog->SetMinSize(wxSize(950, -1));
}

TranslationDialog::~TranslationDialog() = default;

int TranslationDialog::showDialog(TranslationFile* tf, displayMode mode) {
    m_mode = mode;
    m_tf = tf;
    m_fileSettings = {};
    m_fileSettings_tf = {};
    constexpr int c_width = 600;
    std::vector<wxControl*> dlgObjects{};
    int proportion, index = 0;
    int filePickerStyle = wxFLP_USE_TEXTCTRL | wxFLP_SMALL;;
    if (m_mode == displayMode::wxOPEN) filePickerStyle |= wxFLP_FILE_MUST_EXIST;
    m_lblProjectFolder = new wxStaticText(m_dialog, wxID_ANY, _("Project folder:"));
    auto* lbl_exclude_folders = new wxStaticText(m_dialog, wxID_ANY, TEXT_EXCLUDE_FOLDERS);
    auto* lbl_translation_file = new wxStaticText(m_dialog, wxID_ANY, _("Translation file:"));
    m_dirPicker = new wxDirPickerCtrl(m_dialog, wxID_ANY, "", "",
    wxDefaultPosition, wxSize(c_width, -1),
    wxDIRP_USE_TEXTCTRL | wxDIRP_SMALL | wxDIRP_DIR_MUST_EXIST);
    m_dirPicker->GetTextCtrl()->SetEditable(false);
    m_dirPicker->GetTextCtrl()->SetBackgroundColour(wxColour(255, 255, 255));
    m_dirPicker->Bind(wxEVT_DIRPICKER_CHANGED, &TranslationDialog::onDirChanged, this);
    m_filePicker = new wxFilePickerCtrl(m_dialog, wxID_ANY, wxEmptyString, wxEmptyString,
        TRANSLATION_FILE_FILTER, wxDefaultPosition, wxSize(c_width, -1), filePickerStyle);
    m_filePicker->GetTextCtrl()->SetEditable(false);
    m_filePicker->GetTextCtrl()->SetBackgroundColour(wxColour(255, 255, 255));
    m_filePicker->Bind(wxEVT_FILEPICKER_CHANGED, &TranslationDialog::onFileChanged, this);
    wxClientDC dc(m_dialog);
    dc.SetFont(wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT));
    int w, h;
    dc.GetTextExtent("X", &w, &h);
    m_inp_exclusion = new wxTextCtrl(m_dialog, wxID_ANY, wxEmptyString,
    wxDefaultPosition, wxSize(c_width, 4 * (h + 2)), wxTE_MULTILINE | wxTE_BESTWRAP);
    m_inp_exclusion->Clear();
    auto* buttonBox = new wxBoxSizer(wxHORIZONTAL);
    m_okButton = new wxButton(m_dialog, wxID_OK, CAP_OK);
    m_okButton->Bind(wxEVT_BUTTON, &TranslationDialog::onOkClicked, this);
    m_okButton->Enable(false);
    m_cancelButton = new wxButton(m_dialog, wxID_CANCEL, CAP_CANCEL);
    m_cancelButton->Bind(wxEVT_BUTTON, &TranslationDialog::onCancelClicked, this);
    buttonBox->Add(m_okButton);
    buttonBox->Add(m_cancelButton);
    if (m_mode == displayMode::wxNEW) {
        m_dialog->SetTitle(UNI_CREATE_TRANSLATION_FILE);
        m_inp_exclusion->SetValue(m_tf->getSettings().exclude_folders);
        dlgObjects.push_back(m_lblProjectFolder);
        dlgObjects.push_back(m_dirPicker);
        dlgObjects.push_back(lbl_exclude_folders);
        dlgObjects.push_back(m_inp_exclusion);
        dlgObjects.push_back(lbl_translation_file);
        dlgObjects.push_back(m_filePicker);
    } else {
        m_dialog->SetTitle(_("Open translation file and review settings"));
        m_inp_exclusion->SetEditable(false);
        m_inp_exclusion->SetBackgroundColour(wxColour(255, 255, 255));
        m_dirPicker->Enable(false);
        dlgObjects.push_back(lbl_translation_file);
        dlgObjects.push_back(m_filePicker);
        dlgObjects.push_back(lbl_exclude_folders);
        dlgObjects.push_back(m_inp_exclusion);
        dlgObjects.push_back(m_lblProjectFolder);
        dlgObjects.push_back(m_dirPicker);
    }
    auto* vBoxSizer = new wxBoxSizer(wxVERTICAL);
    auto* gridSizer = new wxFlexGridSizer(2, 10, 10);
    gridSizer->SetFlexibleDirection(wxBOTH);
    gridSizer->AddGrowableCol(0, 150);
    gridSizer->AddGrowableCol(1, 600);
    vBoxSizer->Add(gridSizer, 1, wxEXPAND | wxALL, 30);
    for (const auto control : dlgObjects) {
        index++;
        if ((index & 1) == 1) proportion = 0; else proportion = 1;
        gridSizer->Add(control, proportion, 0, wxNO_BORDER);
    }
    gridSizer->Add(new wxPanel(m_dialog), 0, wxEXPAND);
    gridSizer->Add(buttonBox, 1, wxALIGN_RIGHT, wxNO_BORDER);
    m_dialog->SetSizerAndFit(vBoxSizer);
    m_dialog->Layout();
    m_dialog->Fit();
    m_dialog->CenterOnParent();
    m_dialog->ShowModal();
    return m_dialog->GetReturnCode();
}

file_settings TranslationDialog::getFileSettings() {
    return m_fileSettings;
}

void TranslationDialog::onOkClicked(wxCommandEvent& event) {
    m_fileSettings.exclude_folders = toStdString(m_inp_exclusion->GetValue());
    m_fileSettings.file_name = toStdString(m_filePicker->GetFileName().GetFullPath());
    m_fileSettings.project_folder = toStdString(m_dirPicker->GetPath());
    m_tf->setSettings(m_fileSettings);
    if (m_mode == displayMode::wxNEW) {
        m_tf->setDirty();
    }
    if (m_mode == displayMode::wxOPEN) {
        if (m_fileSettings_tf.exclude_folders != m_fileSettings.exclude_folders ||
            m_fileSettings_tf.project_folder != m_fileSettings.project_folder) {
            m_tf->setDirty();
        }
    }
    m_dialog->EndModal(wxID_OK);
}

void TranslationDialog::onCancelClicked(wxCommandEvent& event) {
    m_dialog->EndModal(wxID_CANCEL);
}

void TranslationDialog::onFileChanged(wxFileDirPickerEvent& event) {
    wxString path = event.GetPath();
    m_fileSettings_tf = {};
    if (m_mode == displayMode::wxOPEN) {
        if (wxFileExists(path)) {
            if (m_tf->load(toStdString(path))) {
                m_fileSettings_tf = m_tf->getSettings();
                m_inp_exclusion->SetValue(toWxString(m_fileSettings_tf.exclude_folders));
                m_inp_exclusion->SetEditable(true);
                wxString projFolder = toWxString(m_fileSettings_tf.project_folder);
                if (wxDirExists(projFolder)) {
                    m_dirPicker->SetPath(projFolder);
                    m_okButton->Enable(true);
                } else {
                    m_dirPicker->SetPath(wxEmptyString);
                    m_lblProjectFolder->SetForegroundColour(wxColour("red"));
                    m_lblProjectFolder->Refresh();
                    m_lblProjectFolder->Update();
                }
                m_dirPicker->Enable(true);
                m_dialog->Layout();
            }
        }
    } else {
        if (!path.empty()) {
                m_okButton->Enable(true);
        }
    }
}

void TranslationDialog::onDirChanged(wxFileDirPickerEvent& event) {
    const wxString path = event.GetPath();
    m_fileSettings.project_folder = toStdString(path);
    m_lblProjectFolder->SetForegroundColour(wxColour("black"));
    m_lblProjectFolder->Refresh();
    m_lblProjectFolder->Update();
    m_okButton->Enable(true);
}
