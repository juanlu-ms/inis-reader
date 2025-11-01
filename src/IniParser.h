#ifndef INI_PARSER_H
#define INI_PARSER_H

#include <string>
#include <map>
#include <iostream>

class IniParser {
public:
    IniParser() = default;

    bool loadFile(const std::string& filename);
    std::string getValue(const std::string& section, const std::string& key) const;

private:
    std::map<std::string, std::map<std::string, std::string>> data;

    void trim(std::string& str) const;
};

#endif // INI_PARSER_H