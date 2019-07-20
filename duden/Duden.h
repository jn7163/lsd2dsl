#pragma once

#include "dictlsd/BitStream.h"
#include <cstdint>
#include <string>
#include <vector>
#include <map>

namespace duden {

enum class HicEntryType {
    Plain = 1,
    Reference = 2,
    Range = 4,
    Unknown6 = 6,
    Unknown7 = 7,
    Unknown8 = 8,
    Multi = 10,
    Unknown11 = 11
};

struct HicEntry {
    std::string heading;
    HicEntryType type;
    int32_t textOffset;
    bool isLeaf;
};

struct HicFile {
    std::string name;
    uint8_t version;
    std::vector<HicEntry> entries;
};

struct FsiEntry {
    std::string name;
    uint32_t offset;
    uint32_t size;
};

std::vector<HicEntry> parseHicNode45(dictlsd::IRandomAccessStream* stream);
std::vector<HicEntry> parseHicNode6(dictlsd::IRandomAccessStream* stream);
void decodeBofBlock(const void* blockData,
                    uint32_t blockSize,
                    std::vector<char>& output);
std::vector<uint32_t> parseIndex(dictlsd::IRandomAccessStream* stream);
std::vector<FsiEntry> parseFsiBlock(dictlsd::IRandomAccessStream* stream);
std::vector<FsiEntry> parseFsiFile(dictlsd::IRandomAccessStream* stream);
HicFile parseHicFile(dictlsd::IRandomAccessStream* stream);
std::string dudenToUtf8(std::string str);
std::string win1252toUtf8(std::string str);

} // namespace duden
