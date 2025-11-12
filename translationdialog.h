/////////////////////////////////////////////////////////////////////////////
// Name:        translationdialog.h
// Purpose:     Header file for translationdialog.cpp
// Author:      Jan Buchholz
// Created:     2025-11-12
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/filepicker.h>
#include <wx/wx.h>
#include "jbtypes.h"
#include "translationfile.h"

class TranslationDialog {
public:
    explicit TranslationDialog(wxFrame* parent);
    ~TranslationDialog();
    int showDialog(TranslationFile* tf, displayMode mode);
    file_settings getFileSettings();

private:
    wxDialog* m_dialog;
    wxFrame* m_parent;
    wxButton* m_okButton;
    wxButton* m_cancelButton;
    wxTextCtrl* m_inp_exclusion;
    wxFilePickerCtrl* m_filePicker;
    wxDirPickerCtrl* m_dirPicker;
    wxStaticText* m_lblProjectFolder; 
    displayMode m_mode;
    file_settings m_fileSettings;
    file_settings m_fileSettings_tf;
    TranslationFile* m_tf;
    message m_message;
    void onOkClicked(wxCommandEvent& event);
    void onCancelClicked(wxCommandEvent& event);
    void onFileChanged(wxFileDirPickerEvent& event);
    void onDirChanged(wxFileDirPickerEvent& event);
};
