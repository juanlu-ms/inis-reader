/**
 * @file IniParser.h
 * @brief Defines the IniParser class for parsing INI files.
 */

#ifndef LECTOR_INIS_INIPARSER_H
#define LECTOR_INIS_INIPARSER_H

#include <cstdio>

#define BUFFER_SIZE 512 ///< The buffer size for reading lines from the file.

/**
 * @struct KeyValue
 * @brief Represents a single key-value pair from an INI file.
 */
struct KeyValue {
    char* key {nullptr};    ///< The key string.
    char* value {nullptr};  ///< The value string.
};

/**
 * @struct Section
 * @brief Represents a section in an INI file, containing multiple key-value pairs.
 */
struct Section {
    char* name {nullptr};       ///< The name of the section.
    KeyValue* data {nullptr};   ///< An array of key-value pairs in this section.
    int size {0};               ///< The current number of key-value pairs.
    int capacity {0};           ///< The allocated capacity of the data array.
};

/**
 * @class IniParser
 * @brief A simple parser for INI files.
 *
 * This class reads an INI file, parses its sections and key-value pairs,
 * and provides a method to retrieve values.
 */
class IniParser {
public:
    /**
     * @brief Default constructor for the IniParser.
     */
    IniParser() = default;

    /**
     * @brief Destructor for the IniParser.
     */
    ~IniParser();

    /**
     * @brief Loads and parses an INI file.
     * @param filename The path to the INI file.
     * @return True if the file was loaded successfully, false otherwise.
     */
    bool loadFile(const char* filename);

    /**
     * @brief Retrieves a value from a specific section and key.
     * @param section The name of the section.
     * @param key The name of the key.
     * @return The value as a string, or an empty string if not found.
     */
    const char* getValue(const char* section, const char* key) const;

private:
    Section* sections {nullptr};        ///< Array of all sections found in the INI file.
    Section* current_section {nullptr}; ///< Pointer to the current section being parsed.
    int size {0};                       ///< The current number of sections.
    int capacity {0};                   ///< The allocated capacity of the sections array.

    /**
     * @brief Removes leading and trailing whitespace from a line.
     * @param line The line to clean.
     */
    static void trim(char* line);

    /**
     * @brief Resizes the internal array of sections.
     */
    void resize_section_array();

    /**
     * @brief Adds a new section to the parser.
     * @param section_name The name of the section.
     * @param section_name_size The length of the section name.
     */
    void add_section(const char* section_name, size_t section_name_size);

    /**
     * @brief Resizes the key-value array for the current section.
     */
    void resize_key_value_array();

    /**
     * @brief Adds a key-value pair to the current section.
     * @param str The line containing the key-value pair.
     */
    void add_key_value_to_section(char* str);
};

#endif //LECTOR_INIS_INIPARSER_H
