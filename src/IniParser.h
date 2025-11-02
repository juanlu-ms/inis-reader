#ifndef INI_PARSER_H
#define INI_PARSER_H

#include <string>
#include <map>
#include <iostream>

class IniParser {
public:
    IniParser() = default;

    bool loadFile(std::string_view filename);
    [[nodiscard]] std::string getValue(std::string_view section, std::string_view key) const;

private:
    using KeyValueMap = std::map<std::string, std::string, std::less<>>;
    std::map<std::string, KeyValueMap, std::less<>> data;
};

#endif // INI_PARSER_H
