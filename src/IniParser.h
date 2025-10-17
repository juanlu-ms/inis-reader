#ifndef LECTOR_INIS_INIPARSER_H
#define LECTOR_INIS_INIPARSER_H

#include <cstdio>

#define BUFFER_SIZE 512

struct KeyValue {
    char* key {nullptr};
    char* value {nullptr};
};

struct Section {
    char* name {nullptr};
    KeyValue* data {nullptr};
    int size {0};
};

class IniParser {
public:
    IniParser() = default;
    ~IniParser();

    bool loadFile(const char* filename);
    const char* getValue(const char* section, const char* key);

private:
    Section* sections {nullptr};
    int size {0};
    int capacity {0};

    static void cleanLine(char* line);
    void resize_section_array();
    void add_section(const char* section_name, const size_t section_name_size);
};

#endif //LECTOR_INIS_INIPARSER_H