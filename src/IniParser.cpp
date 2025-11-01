#include "IniParser.h"

namespace {
    void trim(std::string& str) {
        str.erase(0, str.find_first_not_of(" \n\r\t"));
        str.erase(str.find_last_not_of(" \n\r\t") + 1);
    }
}

bool IniParser::loadFile(std::string_view filename) {
}

std::string IniParser::getValue(std::string_view section, std::string_view key) const {
}
