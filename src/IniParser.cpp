#include "IniParser.h"
#include <cstring>
#include <iostream>

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

// Remove leading and trailing whitespace from a line
void IniParser::cleanLine(char* line) {
    if (line == nullptr || line[0] == '\0') {
        return;
    }

    // Trim trailing whitespace
    char* end_ptr = line + (strlen(line) - 1);
    while (end_ptr >= line && isspace(*end_ptr)) {
        end_ptr--;
    }
    *(end_ptr + 1) = '\0';

    // Trim leading whitespace
    const char* start_ptr = line;
    while (*start_ptr && isspace(*start_ptr)) {
        start_ptr++;
    }
    memmove(line, start_ptr, strlen(start_ptr) + 1);
}

void IniParser::resize_section_array() {
    int new_capacity {};
    capacity == 0 ? new_capacity = 10 : new_capacity = capacity * 2;
    auto* new_sections{new Section[new_capacity]};
    if (sections != nullptr) {
        memcpy(new_sections, sections, sizeof(Section) * capacity);
        delete[] sections;
    }
    sections = new_sections;
    capacity = new_capacity;
}

void IniParser::add_section(const char* section_name, const size_t section_name_size) {
    if (section_name == nullptr || section_name_size == 0) {
        return;
    }

    auto* name{new char[section_name_size + 1]};
    strncpy(name, section_name, section_name_size);
    name[section_name_size] = '\0';

    if (capacity == size) {
        resize_section_array();
        sections[size++] = Section{name, nullptr, 0};
    } else {
        sections[size++] = Section{name, nullptr, 0};
    }
}

bool IniParser::loadFile(const char *filename) {
    if (filename == nullptr || filename[0] == '\0') {
        std::cerr << "Error: invalid filename" << std::endl;
        return false;
    }

    const auto file = fopen(filename, "r");
    if (file == nullptr) {
        std::cerr << "Error: could not open file " << filename << std::endl;
        return false;
    }

    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, file) != nullptr) {
        cleanLine(buffer);

        // Skip empty lines and comments
        if (buffer[0] == '\0' || buffer[0] == ';' || buffer[0] == '#') {
            continue;
        }

        // Section header
        if (buffer[0] == '[' && buffer[strlen(buffer) - 1] == ']') {
            add_section(buffer + 1, strlen(buffer) - 2);
        }
    }

    fclose(file);
    return true;
}

const char* IniParser::getValue(const char* section, const char* key) {
    return "";
}
