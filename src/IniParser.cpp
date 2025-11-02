#include "IniParser.h"

#include <fstream>

namespace {
    void trim(std::string& str) {
        const size_t start_pos {str.find_first_not_of(" \t\n\r\f\v")};
        if (start_pos == std::string::npos) {
            str.clear();
            return;
        }

        const size_t end_pos {str.find_last_not_of(" \t\n\r\f\v")};

        str = str.substr(start_pos, end_pos - start_pos + 1);
    }
}

bool IniParser::loadFile(std::string_view filename) {
    if (filename.empty()) {
        std::cerr << "Error: invalid filename" << std::endl;
        return false;
    }

    std::ifstream file {filename.data()};
    if (!file.is_open()) {
        std::cerr << "Error: could not open file " << filename << std::endl;
        return false;
    }

    std::string current_section {};
    std::string line {};
    while (getline(file, line)) {
        trim(line);

        if (line.empty() || line.starts_with(';') || line.starts_with('#')) {
            continue;
        }

        if (line.starts_with('[') && line.ends_with(']')) {
            current_section = line.substr(1, line.size() - 2);
            trim(current_section);
        } else if (auto equal_pos {line.find('=')}; equal_pos != std::string::npos) {
            std::string key {line.substr(0, equal_pos)};
            trim(key);
            std::string value {line.substr(equal_pos + 1)};
            trim(value);

            auto [section, _] {data.try_emplace(current_section)};
            section->second.insert_or_assign(key, value);
        }
    }
    return true;
}

std::string IniParser::getValue(const std::string_view section, const std::string_view key) const {
    if (const auto section_it {data.find(section)}; section_it != data.end()) {
        if (const auto key_it {section_it->second.find(key)}; key_it != section_it->second.end()) {
            return key_it->second;
        }
    }

    return "";
}
