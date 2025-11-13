/////////////////////////////////////////////////////////////////////////////
// Name:        jbconversion.hpp
// Purpose:     String conversion and manipulation utilities
// Author:      Jan Buchholz
// Created:     2025-11-12
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/filename.h>
#include <string>

inline wxString toWxString(const std::string& str) {
    return wxString::FromUTF8(str.c_str());
}

inline std::string toStdString(const wxString& str) {
    return {str.mb_str(wxConvUTF8)};
}

inline std::string getPathSeparator() {
    const wxString sep = wxFileName::GetPathSeparator(wxPATH_NATIVE);
    return toStdString(sep);
}

inline std::string escapeSpecials(const std::string& input) {
    std::string result = input;
    size_t pos = 0;
    // \n -> \\n
    while ((pos = result.find('\n', pos)) != std::string::npos) {
        result.replace(pos, 1, "\\n");
        pos += 2;
    }
    pos = 0;
    // \t -> \\t
    while ((pos = result.find('\t', pos)) != std::string::npos) {
        result.replace(pos, 1, "\\t");
        pos += 2;
    }
    return result;
}
