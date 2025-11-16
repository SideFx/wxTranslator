/////////////////////////////////////////////////////////////////////////////
// Name:        mainwindow.cpp
// Purpose:     The main window of the application
// Author:      Jan Buchholz
// Created:     2025-11-12
/////////////////////////////////////////////////////////////////////////////

#include "mainwindow.h"
#include <wx/stdpaths.h>
#include <wx/gbsizer.h>
#include "iconpool.h"
#include "definitions.h"
#include "translationdialog.h"
#include "scanner.h"
#include "jbconversion.hpp"
#include "aboutdialog.h"

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, wxEmptyString) {
    const int c_hPadding = 10;
    #ifdef __WXMSW__
        SetIcon(wxICON(windowicon));
    #endif
    auto* menuFile = new wxMenu;
    menuFile->Append(wxID_NEW, MENU_FILE_NEW, UNI_CREATE_TRANSLATION_FILE);
    menuFile->Append(wxID_OPEN, MENU_FILE_OPEN, TIP_FILE_OPEN);
    menuFile->Append(wxID_SAVE, MENU_FILE_SAVE, TIP_FILE_SAVE);
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT, MENU_FILE_EXIT, TIP_FILE_EXIT);
    auto *menuEdit = new wxMenu;
    menuEdit->Append(ID_MAKE_MO_FILE, MENU_EDIT_MAKE_MO_FILE, TIP_EDIT_MAKE_MO_FILE);
    menuEdit->AppendSeparator();
    menuEdit->Append(wxID_PREFERENCES, MENU_EDIT_PREFERENCES, TIP_EDIT_PREFERENCES);
    auto *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT, MENU_HELP_ABOUT, UNI_HELP_ABOUT);
    m_menuBar = new wxMenuBar;
    m_menuBar->Append(menuFile, MENU_FILE);
    m_menuBar->Append(menuEdit, MENU_EDIT);
    m_menuBar->Append(menuHelp, MENU_HELP);
    wxFrameBase::SetMenuBar(m_menuBar);
    wxFrameBase::CreateStatusBar();
    Bind(wxEVT_MENU, &MainWindow::onFileNew, this, wxID_NEW);
    Bind(wxEVT_MENU, &MainWindow::onFileOpen, this, wxID_OPEN);
    Bind(wxEVT_MENU, &MainWindow::onFileSave, this, wxID_SAVE);
    Bind(wxEVT_MENU, &MainWindow::onEditPreferences, this, wxID_PREFERENCES);
    Bind(wxEVT_MENU, &MainWindow::onEditMakeMoFile, this, ID_MAKE_MO_FILE);
    Bind(wxEVT_MENU, &MainWindow::onHelpAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainWindow::onFileExit, this, wxID_EXIT);
    auto* mainSizer = new wxBoxSizer(wxVERTICAL);
    m_toolBar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
        wxNO_BORDER|wxTB_FLAT|wxTB_NODIVIDER|wxTB_NOALIGN);
    mainSizer->Add(m_toolBar, 0, wxEXPAND);
    m_toolBar->AddTool(wxID_NEW, wxEmptyString,
        IconPool::getBitmapBundleByName("FILE_NEW", c_toolBarIconSize), UNI_CREATE_TRANSLATION_FILE);
    m_toolBar->AddTool(wxID_OPEN, wxEmptyString,
        IconPool::getBitmapBundleByName("FILE_OPEN", c_toolBarIconSize), TIP_FILE_OPEN);
    m_toolBar->AddTool(wxID_SAVE, wxEmptyString,
        IconPool::getBitmapBundleByName("FILE_SAVE", c_toolBarIconSize), TIP_FILE_SAVE);
    m_toolBar->AddSeparator();
    m_toolBar->AddTool(wxID_PREFERENCES, wxEmptyString,
        IconPool::getBitmapBundleByName("MISC_SETTINGS", c_toolBarIconSize), TIP_EDIT_PREFERENCES);
    m_toolBar->AddSeparator();
    m_toolBar->AddTool(ID_MAKE_MO_FILE, wxEmptyString,
        IconPool::getBitmapBundleByName("MISC_BUILD", c_toolBarIconSize), TIP_EDIT_MAKE_MO_FILE);    
    m_toolBar->AddStretchableSpace();
    m_toolBar->AddTool(wxID_ABOUT, wxEmptyString,
        IconPool::getBitmapBundleByName("HELP_INFO", c_toolBarIconSize), UNI_HELP_ABOUT);
    m_toolBar->AddTool(wxID_EXIT, wxEmptyString,
        IconPool::getBitmapBundleByName("FILE_QUIT_2", c_toolBarIconSize), TIP_FILE_EXIT);
    m_toolBar->Realize();
    m_splitter = new wxSplitterWindow(this, wxID_ANY,
                wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE | wxSP_BORDER);
    m_splitter->SetSashGravity(0.1);
    m_splitter->SetMinimumPaneSize(c_minLeftPanelSize);
    m_splitter->Bind(wxEVT_SPLITTER_SASH_POS_CHANGING, &MainWindow::onSplitterSashMoved, this);
    auto* leftPanel = new wxPanel(m_splitter, wxID_ANY);
    auto* leftSizer = new wxBoxSizer(wxVERTICAL);
    auto* lbl_source = new wxStaticText(leftPanel, wxID_ANY, _("Source files:"), wxDefaultPosition,
        wxDefaultSize, wxEXPAND);  
    leftSizer->Add(lbl_source, 0, wxEXPAND | wxRIGHT | wxLEFT, c_hPadding);
    m_fileListBox = new wxListBox(leftPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize,
        {}, wxLB_SINGLE, wxDefaultValidator, wxEmptyString);
    m_fileListBox->Bind(wxEVT_LISTBOX, &MainWindow::onFileListBoxSelection, this);
    leftSizer->Add(m_fileListBox, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, c_hPadding);
    auto* rightPanel = new wxPanel(m_splitter, wxID_ANY);
    auto* rightSizer = new wxBoxSizer(wxVERTICAL);
    auto* lbl_fileName = new wxStaticText(rightPanel, wxID_ANY, _("Selected source file:"), wxDefaultPosition,
        wxDefaultSize, wxEXPAND);    
    rightSizer->Add(lbl_fileName, 0, wxEXPAND | wxRIGHT | wxLEFT, c_hPadding);
    m_txtFileName = new wxTextCtrl(rightPanel, wxID_ANY, wxEmptyString,
        wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    m_txtFileName->SetBackgroundColour(wxColour(255, 255, 255));     
    rightSizer->Add(m_txtFileName, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, c_hPadding);
    auto* lbl_selectText = new wxStaticText(rightPanel, wxID_ANY, _("List of source texts:"), 
        wxDefaultPosition, wxDefaultSize, wxEXPAND); 
    rightSizer->Add(lbl_selectText, 0, wxEXPAND | wxRIGHT | wxLEFT, c_hPadding);
    m_originalTextListBox = new wxListCtrl(rightPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize,
        wxLC_REPORT | wxLC_SINGLE_SEL, wxDefaultValidator, wxEmptyString);
    m_originalTextListBox->InsertColumn(0, _("Status"), wxLIST_FORMAT_LEFT, 200);
    m_originalTextListBox->InsertColumn(1, _("Source Text"), wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE);    
    m_originalTextListBox->Bind(wxEVT_LIST_ITEM_SELECTED, &MainWindow::onOriginalTextListBoxSelection, this);    
    rightSizer->Add(m_originalTextListBox, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, c_hPadding);    
    auto* lbl_originalText = new wxStaticText(rightPanel, wxID_ANY, _("Selected source text:"), wxDefaultPosition,
        wxDefaultSize, wxEXPAND); 
    rightSizer->Add(lbl_originalText, 0, wxEXPAND | wxRIGHT | wxLEFT, c_hPadding);
    m_originalText = new wxTextCtrl(rightPanel, wxID_ANY, wxEmptyString,
        wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_BESTWRAP | wxTE_READONLY); 
    int lineHeight = m_originalText->GetCharHeight();
    m_originalText->SetMinSize(wxSize(-1, (lineHeight + 3) * 4));
    rightSizer->Add(m_originalText, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, c_hPadding);
    auto* gridBagSizer = new wxGridBagSizer(0, 0);
    auto* lbl_translatedText = new wxStaticText(rightPanel, wxID_ANY, _("Translated text:"), wxDefaultPosition,
        wxDefaultSize, wxEXPAND); 
    gridBagSizer->Add(lbl_translatedText, wxGBPosition(0, 0), wxGBSpan(1, 1),
        wxEXPAND | wxRIGHT | wxTOP, c_hPadding);
    m_tbText = new wxToolBar(rightPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize,
               wxNO_BORDER | wxTB_FLAT | wxTB_NODIVIDER | wxTB_NOALIGN);
    m_tbText->AddTool(ID_MOVE_UP, wxEmptyString, IconPool::getBitmapBundleByName("MISC_UP", c_toolBarIconSize),
        TIP_PREVIOUS_TEXT);
    m_tbText->AddTool(ID_MOVE_DOWN, wxEmptyString, IconPool::getBitmapBundleByName("MISC_DOWN", c_toolBarIconSize), 
        TIP_NEXT_TEXT);
    m_tbText->AddSeparator();
    m_tbText->AddTool(ID_SET_TRANSLATED, wxEmptyString, IconPool::getBitmapBundleByName("MISC_CHECK", c_toolBarIconSize), 
        TIP_SET_TRANSLATED);
    m_tbText->EnableTool(ID_SET_TRANSLATED, false);
    m_tbText->Realize();
    m_tbText->Bind(wxEVT_TOOL, &MainWindow::onMoveToPreviousText, this, ID_MOVE_UP);
    m_tbText->Bind(wxEVT_TOOL, &MainWindow::onMoveToNextText, this, ID_MOVE_DOWN);
    m_tbText->Bind(wxEVT_TOOL, &MainWindow::onSetTextAsTranslated, this, ID_SET_TRANSLATED);
    gridBagSizer->Add(m_tbText, wxGBPosition(0, 1), wxGBSpan(1, 1),
        wxEXPAND | wxRIGHT | wxLEFT, c_hPadding);
    rightSizer->Add(gridBagSizer, 0, wxEXPAND | wxRIGHT | wxLEFT, c_hPadding);
    m_translatedText = new wxTextCtrl(rightPanel, wxID_ANY, wxEmptyString,
        wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_BESTWRAP);
    m_translatedText->SetMinSize(wxSize(-1, (lineHeight + 3) * 4));    
    m_translatedText->SetEditable(false); 
    m_translatedText->SetBackgroundColour(wxColour(255, 255, 255));   
    m_translatedText->Bind(wxEVT_TEXT, &MainWindow::onTranslatedTextChanged, this); 
    m_translatedText->Bind(wxEVT_CHAR, [=](wxKeyEvent& event) {
        if (event.GetKeyCode() == WXK_RETURN || event.GetKeyCode() == WXK_NUMPAD_ENTER) {
            return; // ignore Enter key
        }
        event.Skip(); 
    });
    rightSizer->Add(m_translatedText, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, c_hPadding);
    leftPanel->SetSizer(leftSizer);
    rightPanel->SetSizer(rightSizer);
    m_splitter->SplitVertically(leftPanel, rightPanel);
    mainSizer->Add(m_splitter, 1, wxEXPAND | wxALL, 0);
    SetSizer(mainSizer);
    Bind(wxEVT_CLOSE_WINDOW, &MainWindow::onClose, this);
    Bind(wxEVT_SIZE, &MainWindow::onResize, this);
    m_appTitle = wxString(APP_NAME) + SPACE  + wxString(APP_VERSION );
    wxTopLevelWindowBase::Layout();
    resetData();
    m_appSettings = &AppSettings::instance(this);
}

void MainWindow::setFunctionsEnabled(bool enabled) {
    m_menuBar->Enable(wxID_SAVE, enabled);
    m_toolBar->EnableTool(wxID_SAVE, enabled);
    m_menuBar->Enable(ID_MAKE_MO_FILE, enabled);
    m_toolBar->EnableTool(ID_MAKE_MO_FILE, enabled);
}

void MainWindow::resetData() {
    m_selectedFile = "";
    m_selectedTextIndex = -1;
    m_translationFile.init();
    m_fileListBox->Clear();
    m_txtFileName->Clear();
    m_originalTextListBox->DeleteAllItems();
    m_originalText->Clear();
    m_translatedText->ChangeValue("");
    setFunctionsEnabled(false);
    wxFrameBase::SetTitle(m_appTitle);
}

void MainWindow::fixColumnWidth() {
    const int totalWidth = m_originalTextListBox->GetClientSize().GetWidth();
    int firstColWidth = 200;
    #if defined(__WXMAC__)
        firstColWidth = 150;
    #endif
    const int secondColWidth = totalWidth - firstColWidth;
    m_originalTextListBox->SetColumnWidth(1, secondColWidth);
}

void MainWindow::onResize(wxSizeEvent& event) {
    event.Skip();
    fixColumnWidth(); 
}   

void MainWindow::scanProjectFolder() {
    fixColumnWidth(); // fix wxListCtrl column width on macOS
    m_selectedFile = "";
    auto sc = new Scanner(&m_translationFile);
    m_scans = sc->scanFolder();
    delete sc;
    m_fileListBox->Clear();
    std:: string path{};
    bool b = false;
    std::vector<std::string> allPaths{};
    for (const auto& m : m_scans) {
        if (path != m.source_file) {
            path = m.source_file;
            allPaths.push_back(path);
            b = true;
        }
    }
    if (b) {
        std::stable_sort(allPaths.begin(), allPaths.end(), [](const std::string &a, const std::string &b) {
            return a < b;
        });
        for (auto& p : allPaths) m_fileListBox->AppendString(toWxString(p));
        m_fileListBox->SetSelection(0);
        m_selectedFile = m_fileListBox->GetString(0);
    }
}

void MainWindow::getTranslationsFromFile() {
    std::vector<mo_single_translation> translations = m_translationFile.getTranslations();
    for (auto& scan : m_scans) {
        bool found = false;
        for (auto& trans : translations) {
            if (scan.source_file == trans.source_file &&
                scan.original == trans.original) {  
                found = true;
                scan.translation = trans.translation; 
                break;
            }
        }  
        if (!found) {
            scan.status = newtext;
        } else {
            if (scan.translation != "") {
                scan.status = translated;
            } else {
                scan.status = untranslated;
            }
        }           
    }      
}

void MainWindow::showDataForFile(const wxString& selectedFile) {
    if (selectedFile == "") return;
    bool b = false;
    wxString path = toWxString(m_translationFile.getSettings().project_folder) +
        wxFileName::GetPathSeparator() + selectedFile;
    m_txtFileName->SetValue(path);
    m_originalTextListBox->DeleteAllItems();
    for (auto& s : m_scans) {
        if (s.source_file == selectedFile) {
            wxString status;
            switch (s.status) {
                case newtext:
                    status = STATUS_NEW;
                    break;
                case untranslated:
                    status = STATUS_UNTRANSLATED;
                    break;
                case translated:
                    status = STATUS_TRANSLATED;
                    break;
                default:
                    status = STATUS_UNKNOWN;
                    break;
            }
            long rowIndex = m_originalTextListBox->GetItemCount();            
            rowIndex = m_originalTextListBox->InsertItem(rowIndex, status);
            m_originalTextListBox->SetItem(rowIndex, 1, toWxString(s.original));
            b = true;
        }
    }
    if (b) {
        m_selectedTextIndex = 0;
        m_originalTextListBox->SetItemState(m_selectedTextIndex, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
        showDataForTextIndex(m_selectedTextIndex);
    }
}

void MainWindow::showDataForTextIndex(int textIndex) {
    if (textIndex < 0 || m_selectedFile == "") return;
    int index = -1;
    for (const auto& st : m_scans) {
        if (st.source_file == toStdString(m_selectedFile)) {
            index++;
            if (textIndex == index) {
                m_originalText->SetValue(toWxString(st.original));
                m_translatedText->ChangeValue(toWxString(st.translation)); // do not trigger event
                m_tbText->EnableTool(ID_SET_TRANSLATED, !m_translatedText->GetValue().IsEmpty());
                return;
            }
        }
    }
}

void MainWindow::onFileNew(wxCommandEvent& event) {
    if (!dialogUnsavedChanges()) return;
    resetData();
    mo_file_settings fs{.exclude_folders = m_appSettings->getAppSettings().exclude_folders};
    m_translationFile.setSettings(fs);
    auto* dlg = new TranslationDialog(this);
    int result = dlg->showDialog(&m_translationFile, wxNEW);
    delete dlg;
    if (result == wxID_OK) {
        const mo_message m = m_translationFile.getMessage();
        if (!m.message.empty()) showMessage(m);
        if (m.mtype != error) {
            scanProjectFolder();
            showDataForFile(m_selectedFile);
            m_menuBar->Enable(wxID_SAVE, true);
            m_toolBar->EnableTool(wxID_SAVE, true);
            m_translationFile.setTranslations(m_scans);
            m_translationFile.setDirty(true);
            setTitleWithFileName();
            setFunctionsEnabled(true);
            m_translatedText->SetEditable(true); 
            return;
        }
    }
}

void MainWindow::onFileOpen(wxCommandEvent& event) {
    if (!dialogUnsavedChanges()) return;
    resetData();
    auto* dlg = new TranslationDialog(this);
    int result = dlg->showDialog(&m_translationFile, wxOPEN);
    delete dlg;
    if (result == wxID_OK) {
        const mo_message m = m_translationFile.getMessage();
        if (!m.message.empty()) showMessage(m);
        if (m.mtype != error) {
            scanProjectFolder();
            getTranslationsFromFile();
            showDataForFile(m_selectedFile);
            m_menuBar->Enable(wxID_SAVE, true);
            m_toolBar->EnableTool(wxID_SAVE, true);
            setTitleWithFileName();
            setFunctionsEnabled(true);
            m_translatedText->SetEditable(true); 
            return;
        }
    }
}

void MainWindow::onFileSave(wxCommandEvent& event) { 
    m_translationFile.setTranslations(m_scans);
    if (!m_translationFile.save(m_translationFile.getSettings().file_name)) {
        mo_message m = m_translationFile.getMessage();
        if (!m.message.empty()) showMessage(m);
    }
}

void MainWindow::onFileExit(wxCommandEvent& event) {
    Close(false);
}

void MainWindow::onEditPreferences(wxCommandEvent& event) {
    m_appSettings->openPreferencesDialog();
}

void MainWindow::onEditMakeMoFile(wxCommandEvent& event) {
    m_translationFile.setTranslations(m_scans);
    m_translationFile.createMoFile();
    mo_message m = m_translationFile.getMessage();
    if (!m.message.empty()) showMessage(m);
}

void MainWindow::onHelpAbout(wxCommandEvent& event) {
    auto* dlg = new AboutDialog(this);
    dlg->showDialog();
    delete dlg;
}

void MainWindow::onMoveToPreviousText(wxCommandEvent& event) {
    if (m_selectedTextIndex > 0) {
        m_selectedTextIndex--;
        m_originalTextListBox->SetItemState(m_selectedTextIndex, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
        m_originalTextListBox->EnsureVisible(m_selectedTextIndex);
        showDataForTextIndex(m_selectedTextIndex);
    }
}

void MainWindow::moveToNextText() {
    if (m_selectedTextIndex < m_originalTextListBox->GetItemCount() - 1) {
        m_selectedTextIndex++;
        m_originalTextListBox->SetItemState(m_selectedTextIndex, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
        m_originalTextListBox->EnsureVisible(m_selectedTextIndex);
        showDataForTextIndex(m_selectedTextIndex);
    }    
}

void MainWindow::onMoveToNextText(wxCommandEvent& event) {
    moveToNextText();
}

void MainWindow::onSetTextAsTranslated(wxCommandEvent& event) {
    if (m_selectedTextIndex < 0 || m_selectedFile == "") return;
    int index = -1;
    for (auto& st : m_scans) {
        if (st.source_file == toStdString(m_selectedFile)) {
            index++;
            if (m_selectedTextIndex == index) {
                st.translation = toStdString(m_translatedText->GetValue());
                st.status = translated;
                m_originalTextListBox->SetItem(index, 0, STATUS_TRANSLATED);
                m_translationFile.setDirty(true);
                moveToNextText();
                return;
            }
        }
    }
}

void MainWindow::onTranslatedTextChanged(wxCommandEvent& event) {
    wxString text = event.GetString();
    m_tbText->EnableTool(ID_SET_TRANSLATED, !text.IsEmpty());
    m_translationFile.setDirty(true);
}

void MainWindow::onClose(wxCloseEvent& event) {
    m_appSettings->savePreferences();
    if (!dialogUnsavedChanges()) {
        event.Veto();
        return;
    }   
    Destroy();
}

void MainWindow::onFileListBoxSelection(wxCommandEvent& event) {
    m_selectedFile = event.GetString();
    showDataForFile(m_selectedFile);
}

void MainWindow::onOriginalTextListBoxSelection(wxListEvent& event) {
    m_selectedTextIndex = event.GetIndex();
    showDataForTextIndex(m_selectedTextIndex);
}

void MainWindow::onSplitterSashMoved(wxSplitterEvent& event) {
    event.Skip();
    int newPos = event.GetSashPosition();
    if (newPos > c_maxLeftPanelSize) event.SetSashPosition(c_maxLeftPanelSize);
}

int MainWindow::showMessage(const mo_message& m) {
    long style;
    switch (m.mtype) {
        case information: style = wxICON_INFORMATION | wxOK;
            break;
        case warning: style = wxICON_WARNING | wxOK;
            break;
        case question: style = wxICON_WARNING | wxYES_NO | wxCANCEL | wxCANCEL_DEFAULT;
            break;
        default: style = wxICON_ERROR | wxOK;
    }
    auto* dlg = new wxMessageDialog(this, toWxString(m.message), APP_NAME, style);
    dlg->CenterOnParent();
    int res = dlg->ShowModal();
    delete dlg;
    return res;
}

void MainWindow::setTitleWithFileName() {
    std::string filename = std::filesystem::path(m_translationFile.getSettings().file_name).filename().string();
    wxString title = m_appTitle;
    if (filename != "") {
        title += " - " + toWxString(filename);
    }
    wxFrameBase::SetTitle(title);
}

bool MainWindow::dialogUnsavedChanges() {
    if (m_translationFile.getDirty()) {
        mo_message m{
            .mtype = question,
            .message = toStdString(TEXT_UNSAVED_CHANGES)
        };
        int res = showMessage(m);
        if (res == wxID_CANCEL) {
            return false;
        } else if (res == wxID_YES) {
            m_translationFile.setTranslations(m_scans);
            if (!m_translationFile.save(m_translationFile.getSettings().file_name)) {
                mo_message m = m_translationFile.getMessage();
                if (!m.message.empty()) showMessage(m);
                return false;
            }
        }
    }
    return true;
}

/*
#ifdef __WXMSW__
#elif defined(__WXMAC__)
#elif defined(__WXGTK__)
#else
#endif
*/
