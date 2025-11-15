/////////////////////////////////////////////////////////////////////////////
// Name:        mobuilder.h
// Purpose:     Header for mobuilder.cpp
// Author:      Jan Buchholz
// Created:     2025-11-15
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "jbtypes.h"
#include <bit>

class MoBuilder { 
public:
    MoBuilder() = default;
    ~MoBuilder() = default;
    bool buildMoFile(const mt_translations& translations, const std::string& moFile);
    mo_message getMessage();

private:
    uint32_t swap32(uint32_t x);
    uint32_t to_le32(uint32_t x);

    mo_header m_header;
    mt_moentries m_originalEntries;
    mt_moentries m_translationEntries;
    mt_translations m_translations;
    mo_message m_message;

    const uint32_t c_moMagicLE = 0x950412de;
    const uint32_t c_revision = 0;
    const uint32_t c_headerSize = sizeof(mo_header) ;
    const uint32_t c_entrySize = sizeof(mo_entry);
    static_assert(sizeof(mo_entry) == 8, "mo_entry must be 8 bytes of size!");
    static_assert(sizeof(mo_header) == 28, "mo_header must be 28 bytes of size!");
    const std::string c_metaDataHeader =
    "Mime-Version: 1.0\n"
    "Content-Type: text/plain; charset=UTF-8\n"
    "Content-Transfer-Encoding: 8bit\n"
    "X-Generator: wxTranslator\n";
 
};
