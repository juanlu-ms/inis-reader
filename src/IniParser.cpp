#include "IniParser.h"

IniParser::~IniParser() {
    if (sections != nullptr) {
        return;
    }

    for (int i = 0; i < size; ++i) {
        for (int s = 0; s < sections[i].size; ++s) {
            delete[] sections[i].data[s].key;
            delete[] sections[i].data[s].value;
        }
        delete[] sections[i].data;
        delete[] sections[i].name;
    }

    delete[] sections;
}

bool IniParser::loadFile(const char *filename) {
    return true;
}

const char *IniParser::getValue(const char *section, const char *key) {
    return "";
}
