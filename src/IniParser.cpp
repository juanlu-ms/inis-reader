#include "IniParser.h"

void IniParser::trim(std::string& str) {
    str.erase(0, str.find_first_not_of(" \n\r\t"));
    str.erase(str.find_last_not_of(" \n\r\t") + 1);
}

bool IniParser::loadFile(const std::string& filename) {

}

std::string IniParser::getValue(const std::string& section, const std::string& key) const {

}
