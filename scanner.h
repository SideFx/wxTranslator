/////////////////////////////////////////////////////////////////////////////
// Name:        scanner.h
// Purpose:     Header file for scanner.cpp
// Author:      Jan Buchholz
// Created:     2025-11-12
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include <filesystem>
#include <string>
#include <vector>
#include "translationfile.h"

class Scanner {
public:
    explicit Scanner(const TranslationFile* tf);
    std::vector<mo_single_translation> scanFolder();
    std::vector<std::string> processFile(const std::filesystem::path& filepath);

private:
    std::string removeComments(const std::string& code);
    std::string mergeStringLiterals(const std::string& code);
    std::vector<std::string> extractTranslationStrings(const std::string& code);
    std::vector<std::string> splitAtNewline(const std::string& input);
    bool wildcardMatch(const std::string& pattern, const std::string& target);
    const TranslationFile* m_tf;
    std::vector<std::string> m_exclusionList;
    std::string m_projectFolder;
    mt_extensions m_extensions;
};


