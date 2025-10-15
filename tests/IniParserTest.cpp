#include <gtest/gtest.h>
#include <fstream>
#include "../src/IniParser.h"

class IniParserLoadTest : public testing::Test {
protected:
    void SetUp() override {
        std::ofstream testFile("test.ini");
        testFile << "[Database]\n";
        testFile << "host=localhost\n";
        testFile << "port = 8080\n\n";
        testFile << "; Comentario\n";
        testFile << "[User]\n";
        testFile << "name=juanlu\n";
        testFile.close();
    }

    void TearDown() override {
        remove("test.ini");
    }

    IniParser parser;
};

TEST_F(IniParserLoadTest, ReadValuesCorrectly) {
    const bool loadSuccess = parser.loadFile("test.ini");
    ASSERT_TRUE(loadSuccess)<<"Failed to load INI file";

    ASSERT_EQ(parser.getValue("Database", "host"), "localhost")<<"Failed to read 'host' key from 'Database' section";
    ASSERT_EQ(parser.getValue("Database", "port"), "8080")<<"Failed to read 'port' key from 'Database' section";

    ASSERT_EQ(parser.getValue("User", "name"), "juanlu")<<"Failed to read 'name' key from 'User' section";
}

TEST_F(IniParserLoadTest, ReturnsEmptyForNonExistentKey) {
    parser.loadFile("test.ini");
    ASSERT_EQ(parser.getValue("Database", "non_existent_key"), "")<<"Non-existent key should return empty string";
}

TEST(IniParserStandaloneTest, FailsIfFileDoesNotExist) {
    IniParser p;
    ASSERT_FALSE(p.loadFile("non_existent_file.ini"))<<"Loading a non-existent file should fail";
}