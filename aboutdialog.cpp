/////////////////////////////////////////////////////////////////////////////
// Name:        aboutdialog.cpp
// Purpose:     Create and show the About dialog
// Author:      Jan Buchholz
// Created:     2025-11-12
/////////////////////////////////////////////////////////////////////////////

#include "aboutdialog.h"
#include "definitions.h"
#include "logo.hpp"
#include <wx/mstream.h>
#include <wx/image.h>
#include <wx/bitmap.h>

AboutDialog::AboutDialog(wxFrame* parent) {
    m_parent = parent;
    m_dialog = new wxDialog(parent, wxID_ANY, UNI_HELP_ABOUT, wxDefaultPosition, wxDefaultSize);
    m_dialog->SetWindowStyle(wxCAPTION | wxCLOSE_BOX);
}

void AboutDialog::showDialog() {
    const int c_padding = 30;
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxBitmap appLogoBitmap = loadEmbeddedPng();
    int width = appLogoBitmap.GetWidth() / 2;
    int height = appLogoBitmap.GetHeight() / 2;
    wxImage scaledImage = appLogoBitmap.ConvertToImage().Scale(width, height, wxIMAGE_QUALITY_HIGH);
    wxBitmap scaledBitmap(scaledImage);
    wxStaticBitmap* staticAppLogoBitmap = new wxStaticBitmap(m_dialog, wxID_ANY, scaledBitmap, 
        wxPoint(10, 10), wxSize(-1, -1));
    mainSizer->Add(staticAppLogoBitmap, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP, c_padding);
    wxString appNameVersion = wxString(APP_NAME) + SPACE + wxString(APP_VERSION);
    wxStaticText* lbl_appNameVersion = new wxStaticText(m_dialog, wxID_ANY, appNameVersion, 
        wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
    lbl_appNameVersion->SetFont(wxFontInfo(12).Bold());
    mainSizer->Add(lbl_appNameVersion, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP, c_padding);
    wxStaticText* lbl_about = new wxStaticText(m_dialog, wxID_ANY, APP_AUTHOR_STRING + DIALOG_ABOUT,
        wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
    mainSizer->Add(lbl_about, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP | wxLEFT | wxRIGHT, c_padding);
    wxStaticText* lbl_credits = new wxStaticText(m_dialog, wxID_ANY, DIALOG_CREDITS,
        wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
    mainSizer->Add(lbl_credits, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, c_padding);
    wxButton* btnOK = new wxButton(m_dialog, wxID_OK, CAP_OK);
    mainSizer->Add(btnOK, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, c_padding);
    m_dialog->SetSizerAndFit(mainSizer);
    m_dialog->Layout();
    m_dialog->Fit();
    m_dialog->CentreOnParent();
    m_dialog->ShowModal();
}

wxBitmap AboutDialog::loadEmbeddedPng() {
    wxMemoryInputStream stream(logo_png, logo_png_len);
    wxImage img(stream, wxBITMAP_TYPE_PNG);
    return wxBitmap(img);
}
