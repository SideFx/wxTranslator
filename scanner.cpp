/////////////////////////////////////////////////////////////////////////////
// Name:        scanner.cpp
// Purpose:     Search wxTranslation macros in source code files
// Author:      Jan Buchholz
// Created:     2025-11-12
/////////////////////////////////////////////////////////////////////////////

#include "scanner.h"
#include <regex>
#include <sstream>
#include <fstream>
#include <iostream>
#include "appsettings.h"

Scanner::Scanner(const TranslationFile* tf) {
    m_tf = tf;
    m_projectFolder = m_tf->getSettings().project_folder;
    m_exclusionList = splitAtNewline(m_tf->getSettings().exclude_folders);
    AppSettings* appSettings = &AppSettings::instance();
    m_extensions = appSettings->getAppSettings().extensions;
}

std::vector<std::string> Scanner::splitAtNewline(const std::string& input) {
    std::vector<std::string> result{};
    std::istringstream stream(input);
    std::string line;
    while (std::getline(stream, line)) result.push_back(line);
    return result;
}

bool Scanner::wildcardMatch(const std::string& pattern, const std::string& target) {
    std::string regex_pattern;
    std::string p = pattern, t = target;
    std::ranges::transform(p, p.begin(), ::tolower);
    std::ranges::transform(t, t.begin(), ::tolower);
    for (const char c : p) {
        switch (c) {
            case '*': regex_pattern += ".*";
                break;
            case '?': regex_pattern += ".";
                break;
            case '.': regex_pattern += "\\.";
                break;
            default:  regex_pattern += c;
        }
    }
    const std::regex re(regex_pattern);
    return std::regex_search(t, re);
}

// Remove single and multi line comments
std::string Scanner::removeComments(const std::string& code) {
    std::string no_comments = code;
    // remove /* */ comments
    // /\* = /*
    // \*/ = */
    // [\s\S] = any character (whitespace or not whitespace)
    // *? = find as many, but non-greedy    
    no_comments = std::regex_replace(no_comments, std::regex(R"(/\*[\s\S]*?\*/)"), "");
    return no_comments;
}

// Concatenate cohesive string literals
std::string Scanner::mergeStringLiterals(const std::string& code) {
    // remove whitespace characters between string literals
    // R"delim(...)delim") = delim begin and end of Raw string
    // "(\s*)"\s* = regex expression, removes whitespace and '"' characters
    // "text1 "\n"text2" => "text1 text2"
    return std::regex_replace(code, std::regex(R"delim("(\s*)"\s*)delim"), "");
}

// Extract text to be translated from wx macro
std::vector<std::string> Scanner::extractTranslationStrings(const std::string& code) {
    std::vector<std::string> entries{};
    // match _() and wxTRANSLATE()
    // Microsoft Copilot helped here :)
    std::regex pattern("(?:_|wxTRANSLATE)\\s*\\(\\s*\"((?:[^\"\\\\]|\\\\.|[\\n\\r])*)\"\\s*\\)", std::regex::ECMAScript);
    auto begin = std::sregex_iterator(code.begin(), code.end(), pattern);
    std::sregex_iterator end;
    for (auto it = begin; it != end; ++it) {
        entries.push_back((*it)[1].str()); // extract captured group
    }   
    return entries;
}

std::vector<std::string> Scanner::processFile(const std::filesystem::path& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) return {};
    const std::string content((std::istreambuf_iterator(file)),
        std::istreambuf_iterator<char>());
    std::string clean = removeComments(content);
    clean = mergeStringLiterals(clean);
    return extractTranslationStrings(clean);
}

// Traverse directory
std::vector<mo_single_translation> Scanner::scanFolder() {
    std::vector<mo_single_translation> translations{};
    std::filesystem::recursive_directory_iterator dirIt(m_projectFolder), endIt;
    while (dirIt != endIt) {
        const std::filesystem::directory_entry& entry = *dirIt;
        std::filesystem::path relativePath = std::filesystem::relative(entry.path(), m_projectFolder);
        std::string entryName = relativePath.string();
        if (entry.is_directory()) {
            for (auto& ex : m_exclusionList) {
                if (wildcardMatch(ex, entryName)) {
                    dirIt.disable_recursion_pending();
                    break;
                }
            }
        } else if (entry.is_regular_file()) {
            bool skip = false;
            for (auto& ex : m_exclusionList) {
                if (wildcardMatch(ex, entryName)) {
                    skip = true;
                    break;
                }
            }
            if (!skip) {
                auto ext = relativePath.extension();
                for (auto& ex : m_extensions) {
                    if (ex.second && ex.first == ext) {
                        std::vector<std::string> trs = processFile(entry.path());
                        for (const auto& tr : trs) {
                            mo_single_translation s = {.source_file = entryName, .original = tr, .status = untranslated};
                            translations.push_back(s);
                        }
                    }
                }
            }
        }
        ++dirIt;
    }
    return translations;
}

