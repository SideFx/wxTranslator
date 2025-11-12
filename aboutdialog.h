/////////////////////////////////////////////////////////////////////////////
// Name:        aboutdialog.h
// Purpose:     Header file for aboutdialog.cpp
// Author:      Jan Buchholz
// Created:     2025-11-12
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/wx.h>

class AboutDialog : public wxDialog {   
public:
    AboutDialog(wxFrame* parent);
    void showDialog();

private:
    wxBitmap loadEmbeddedPng();
    wxDialog* m_dialog;
    wxFrame* m_parent;
};
