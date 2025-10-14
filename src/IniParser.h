#ifndef LECTOR_INIS_INIPARSER_H
#define LECTOR_INIS_INIPARSER_H

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
};

#endif //LECTOR_INIS_INIPARSER_H