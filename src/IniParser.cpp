#include "IniParser.h"
#include <cstring>
#include <iostream>

/**
 * @brief Destructor for the IniParser class.
 *
 * Frees all the dynamically allocated memory for sections and their key-value pairs.
 */
IniParser::~IniParser() {
    if (sections == nullptr) {
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

/**
 * @brief Removes leading and trailing whitespace from a line.
 * @param line The line to clean.
 */
void IniParser::trim(char* line) {
    if (line == nullptr || line[0] == '\0') {
        return;
    }

    char* end_ptr = line + (strlen(line) - 1);
    while (end_ptr >= line && isspace(static_cast<unsigned char>(*end_ptr))) {
        end_ptr--;
    }
    *(end_ptr + 1) = '\0';


    const char* start_ptr = line;
    while (*start_ptr && isspace(static_cast<unsigned char>(*start_ptr))) {
        start_ptr++;
    }
    memmove(line, start_ptr, strlen(start_ptr) + 1);
}

/**
 * @brief Resizes the internal array of sections, doubling its capacity.
 */
void IniParser::resize_section_array() {
    int new_capacity {capacity == 0 ? 10 : capacity * 2};
    auto* new_sections {new Section[new_capacity]};
    if (sections != nullptr) {
        for (int i = 0; i < size; ++i) {
            new_sections[i] = sections[i];
        }
        delete[] sections;
    }
    sections = new_sections;
    capacity = new_capacity;
}

/**
 * @brief Adds a new section to the parser.
 * @param section_name The name of the section.
 * @param section_name_size The length of the section name.
 */
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

/**
 * @brief Resizes the key-value array for the current section, doubling its capacity.
 */
void IniParser::resize_key_value_array() {
    int new_capacity {current_section->capacity == 0 ? 10 : current_section->capacity * 2};
    auto* new_data {new KeyValue[new_capacity]};
    if (current_section->data != nullptr) {
        for (int i = 0; i < current_section->size; ++i) {
            new_data[i] = current_section->data[i];
        }
        delete[] current_section->data;
    }
    current_section->data = new_data;
    current_section->capacity = new_capacity;
}

/**
 * @brief Adds a key-value pair to the current section.
 * @param str The line containing the key-value pair.
 */
void IniParser::add_key_value_to_section(char* str) {
    auto* equals_ptr {strchr(str, '=')};
    if (equals_ptr == nullptr) {
        return;
    }

    *equals_ptr = '\0';
    char* key_ptr {str};
    char* value_ptr {equals_ptr + 1};

    trim(key_ptr);
    trim(value_ptr);

    if (current_section->capacity == current_section->size) {
        resize_key_value_array();
    }

    const size_t key_len = strlen(key_ptr);
    const auto new_key {new char[key_len + 1]};
    strncpy(new_key, key_ptr, key_len);
    new_key[key_len] = '\0';

    const size_t value_len = strlen(value_ptr);
    const auto new_value {new char[value_len + 1]};
    strncpy(new_value, value_ptr, value_len);
    new_value[value_len] = '\0';

    KeyValue& new_pair = current_section->data[current_section->size];
    new_pair.key = new_key;
    new_pair.value = new_value;

    current_section->size++;
}

/**
 * @brief Loads and parses an INI file.
 * @param filename The path to the INI file.
 * @return True if the file was loaded successfully, false otherwise.
 */
bool IniParser::loadFile(const char* filename) {
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
        trim(buffer);

        if (buffer[0] == '\0' || buffer[0] == ';' || buffer[0] == '#') {
            continue;
        }

        if (buffer[0] == '[' && buffer[strlen(buffer) - 1] == ']') {
            char* section_name = buffer + 1;
            buffer[strlen(buffer) - 1] = '\0';
            trim(section_name);
            add_section(section_name, strlen(section_name));
        } else if (strchr(buffer, '=') != nullptr && current_section != nullptr) {
            add_key_value_to_section(buffer);
        }
    }

    fclose(file);
    return true;
}

/**
 * @brief Retrieves a value from a specific section and key.
 * @param section The name of the section.
 * @param key The name of the key.
 * @return The value as a string, or an empty string if not found.
 */
const char* IniParser::getValue(const char* section, const char* key) const {
    int i {0};
    while (i < size && strcmp(sections[i].name, section) != 0) {
        i++;
    }
    if (i == size) {
        return "";
    }

    const Section* wanted_section {&sections[i]};
    int j {0};
    while (j < wanted_section->size && strcmp(wanted_section->data[j].key, key) != 0) {
        j++;
    }
    if (j == wanted_section->size) {
        return "";
    }

    return wanted_section->data[j].value;
}
