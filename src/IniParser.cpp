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

void IniParser::cleanLine(char* line) {
    if (line == nullptr || line[0] == '\0') {
        return;
    }

    char* end_ptr = line + (strlen(line) - 1);
    while (end_ptr >= line && isspace(*end_ptr)) {
        end_ptr--;
    }
    *(end_ptr + 1) = '\0';


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
        for (int i = 0; i < size; ++i) {
            new_sections[i] = sections[i];
        }
        delete[] sections;
    }
    sections = new_sections;
    capacity = new_capacity;
}

void IniParser::add_section(const char* section_name, const size_t section_name_size) {
    if (section_name == nullptr || section_name_size == 0) {
        return;
    }

    if (capacity == size) {
        resize_section_array();
    }

    auto* name {new char[section_name_size + 1]};
    strncpy(name, section_name, section_name_size);
    name[section_name_size] = '\0';

    sections[size].name = name;
    sections[size].data = nullptr;
    sections[size].size = 0;
    sections[size].capacity = 0;

    current_section = &sections[size++];
}

void IniParser::resize_key_value_array() const {
    int new_capacity {};
    current_section->capacity == 0 ? new_capacity = 10 : new_capacity = capacity * 2;
    auto* new_data{new KeyValue[new_capacity]};
    if (current_section->data != nullptr) {
        for (int i = 0; i < current_section->size; ++i) {
            new_data[i] = current_section->data[i];
        }
        delete[] current_section->data;
    }
    current_section->data = new_data;
    current_section->capacity = new_capacity;
}

void IniParser::create_key_value(const char* str, const char* equals_ptr, size_t key_value_size) {

}

void IniParser::add_key_value_to_section(const char* str, const size_t str_size) {
    auto* equals_ptr {strchr(str, '=')};
    if (equals_ptr == nullptr) {
        return;
    }

    if (current_section->capacity == current_section->size) {
        resize_key_value_array();
    }

    create_key_value(str, equals_ptr, str_size);

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

        if (buffer[0] == '\0' || buffer[0] == ';' || buffer[0] == '#') {
            continue;
        }

        if (buffer[0] == '[' && buffer[strlen(buffer) - 1] == ']') {
            add_section(buffer + 1, strlen(buffer) - 2);
        } else if (strchr(buffer, '=') != nullptr && current_section != nullptr) {
            add_key_value_to_section(buffer, strlen(buffer) + 1);
        }
    }

    fclose(file);
    return true;
}

const char* IniParser::getValue(const char* section, const char* key) {
    return "";
}
