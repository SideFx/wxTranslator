/////////////////////////////////////////////////////////////////////////////
// Name:        mainwindow.h
// Purpose:     Header file for mainwindow.cpp
// Author:      Jan Buchholz
// Created:     2025-11-12
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/wx.h>
#include <wx/event.h>
#include <wx/splitter.h>
#include <wx/listctrl.h>
#include "appsettings.h"
#include "translationfile.h"
#include "jbtypes.h"

class MainWindow final : public wxFrame {
public:
    MainWindow();
    AppSettings* m_appSettings;
    TranslationFile m_translationFile{};
    wxSplitterWindow* m_splitter;

private:
    void onFileNew(wxCommandEvent& event);
    void onFileOpen(wxCommandEvent& event);
    void onFileSave(wxCommandEvent& event);
    void onEditPreferences(wxCommandEvent& event);
    void onEditMakeMoFile(wxCommandEvent& event);
    void onFileExit(wxCommandEvent& event);
    void onHelpAbout(wxCommandEvent& event);
    int showMessage(const mo_message& m);
    void scanProjectFolder();
    void onClose(wxCloseEvent& event);
    void onSplitterSashMoved(wxSplitterEvent& event);
    void onFileListBoxSelection(wxCommandEvent& event);
    void showDataForFile(const wxString& selectedFile);
    void showDataForTextIndex(int textIndex);
    void getTranslationsFromFile();
    void onOriginalTextListBoxSelection(wxListEvent& event);
    void onResize(wxSizeEvent& event);
    bool dialogUnsavedChanges();
    void moveToNextText();
    void onMoveToPreviousText(wxCommandEvent& event);
    void onMoveToNextText(wxCommandEvent& event);
    void onSetTextAsTranslated(wxCommandEvent& event);
    void onTranslatedTextChanged(wxCommandEvent& event);
    void setTitleWithFileName();
    void resetData();
    void setFunctionsEnabled(bool enabled);

    std::vector<mo_single_translation> m_scans{};
    const int c_toolBarIconSize = 18;
    const int c_minLeftPanelSize = 300;
    const int c_maxLeftPanelSize = 600;
    wxString m_appTitle;
    wxListBox* m_fileListBox;
    wxListCtrl* m_originalTextListBox;
    wxMenuBar* m_menuBar;
    wxToolBar* m_toolBar;
    wxToolBar* m_tbText;
    wxTextCtrl* m_txtFileName;
    wxTextCtrl* m_originalText;
    wxTextCtrl* m_translatedText;
    wxString m_selectedFile;
    long m_selectedTextIndex;

};

