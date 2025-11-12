
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
