/////////////////////////////////////////////////////////////////////////////
// Name:        mobuilder.cpp
// Purpose:     Create binary .MO file
// Author:      Jan Buchholz
// Created:     2025-11-15
/////////////////////////////////////////////////////////////////////////////

#include "mobuilder.h"
#include "jbconversion.hpp"
#include <fstream>

bool MoBuilder::buildMoFile(const mt_translations& translations, const std::string& moFile) {
    std::string original;
    std::string translation;
    m_originalEntries.clear();
    m_translationEntries.clear();
    m_translations.clear();
    m_message = {};
    // create metadata header at index 0
    mo_single_translation prefix = {"", "", c_metaDataHeader, translated};
    m_translations.push_back(prefix);
    // append translations
    m_translations.insert(m_translations.end(), translations.begin(), translations.end());
    const uint32_t numStrings = static_cast<uint32_t>(m_translations.size());
    const uint32_t tabSize = numStrings * c_entrySize;
    const uint32_t originalTabOffset = c_headerSize;
    const uint32_t translationTabOffset = originalTabOffset + tabSize;
    const uint32_t originalStringsOffset = translationTabOffset + tabSize;
    uint32_t currentOffset = originalStringsOffset;
    for (const auto& t : m_translations) {
        // original entry
        mo_entry originalEntry;
        original = unescapeSpecials(t.original);
        originalEntry.length = static_cast<uint32_t>(original.size());
        originalEntry.offset = currentOffset;
        m_originalEntries.push_back(originalEntry);
        currentOffset += static_cast<uint32_t>(original.size() + 1);
    }
    for (const auto& t : m_translations) {
        // translation entry
        mo_entry translationEntry;
        translation = unescapeSpecials(t.translation);
        translationEntry.length = static_cast<uint32_t>(translation.size());
        translationEntry.offset = currentOffset;
        m_translationEntries.push_back(translationEntry);
        currentOffset += static_cast<uint32_t>(translation.size() + 1);
    }
   // prepare header
    m_header.magic = to_le32(c_moMagicLE);
    m_header.revision = to_le32(c_revision);
    m_header.num_strings = to_le32(numStrings);
    m_header.orig_tab_offset = to_le32(originalTabOffset);
    m_header.trans_tab_offset = to_le32(translationTabOffset); 
    m_header.hash_tab_offset = to_le32(0);
    m_header.hash_tab_size = to_le32(0);
    // write to file
    std::ofstream ofs(moFile, std::ios::binary);
    if (!ofs.is_open()) {
        m_message.mtype = error;
        m_message.message = _("I/O error while saving machine object (.mo) file.");
        return false;
    }
    // write header 
    ofs.write(reinterpret_cast<const char*>(&m_header), sizeof(mo_header));
    // write original entries
    for (const auto& entry : m_originalEntries) {
        uint32_t le_length = to_le32(entry.length);
        uint32_t le_offset = to_le32(entry.offset);
        ofs.write(reinterpret_cast<const char*>(&le_length), sizeof(uint32_t));
        ofs.write(reinterpret_cast<const char*>(&le_offset), sizeof(uint32_t));
    }
    // write translation entries
    for (const auto& entry : m_translationEntries) {
        uint32_t le_length = to_le32(entry.length);
        uint32_t le_offset = to_le32(entry.offset);
        ofs.write(reinterpret_cast<const char*>(&le_length), sizeof(uint32_t));
        ofs.write(reinterpret_cast<const char*>(&le_offset), sizeof(uint32_t));
    }
    // append original strings
    for (const auto& t : m_translations) {
        original = unescapeSpecials(t.original);
        ofs.write(original.data(), original.size());
        ofs.put('\0');
    }
    // append translation strings
    for (const auto& t : m_translations) {
        translation = unescapeSpecials(t.translation);
        ofs.write(translation.data(), translation.size());
        ofs.put('\0');
    }
    ofs.close();
    m_message.mtype = information;
    m_message.message = _("Machine object (.mo) file has been created.");
    return true;
}

mo_message MoBuilder::getMessage() {
    return m_message;
}

uint32_t MoBuilder::swap32(uint32_t x) {
    return ((x & 0x000000FF) << 24) |
           ((x & 0x0000FF00) << 8)  |
           ((x & 0x00FF0000) >> 8)  |
           ((x & 0xFF000000) >> 24);
};

uint32_t MoBuilder::to_le32(uint32_t x) {
    if constexpr (std::endian::native == std::endian::little) {
        return x; 
    } else {
        return swap32(x); 
    }
};
