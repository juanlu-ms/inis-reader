#include <gtest/gtest.h>
#include <fstream>
#include "../src/IniParser.h"

class IniParserLoadTest : public testing::Test {
protected:
    void SetUp() override {
        std::ofstream testFile("test.ini");
        testFile << "[EmptySection]\n\n";
        testFile << "[NextSection]\n";
        testFile << "key=value\n";
        testFile << "[  SpacingTest  ]\n";
        testFile << "  spaced_key  =  spaced_value  \n";
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

TEST_F(IniParserLoadTest, HandlesWhitespaceCorrectly) {
    parser.loadFile("test.ini");
    ASSERT_STREQ(parser.getValue("SpacingTest", "spaced_key"), "spaced_value");
}

TEST_F(IniParserLoadTest, HandlesEmptySection) {
    parser.loadFile("test.ini");
    ASSERT_STREQ(parser.getValue("NextSection", "key"), "value");
    ASSERT_STREQ(parser.getValue("EmptySection", "some_key"), "");
}

TEST_F(IniParserLoadTest, ReadValuesCorrectly) {
    const bool loadSuccess = parser.loadFile("test.ini");
    ASSERT_TRUE(loadSuccess) << "Failed to load INI file";

    ASSERT_STREQ(parser.getValue("Database", "host"), "localhost") << "Failed to read 'host' key from 'Database' section";
    ASSERT_STREQ(parser.getValue("Database", "port"), "8080") << "Failed to read 'port' key from 'Database' section";

    ASSERT_STREQ(parser.getValue("User", "name"), "juanlu") << "Failed to read 'name' key from 'User' section";
}

TEST_F(IniParserLoadTest, ReturnsEmptyForNonExistentKey) {
    parser.loadFile("test.ini");
    ASSERT_STREQ(parser.getValue("Database", "non_existent_key"), "") << "Non-existent key should return empty string";
}

TEST(IniParserStandaloneTest, FailsIfFileDoesNotExist) {
    IniParser p;
    ASSERT_FALSE(p.loadFile("non_existent_file.ini")) << "Loading a non-existent file should fail";
}

TEST(IniParserStressTest, HandlesResizeCorrectly) {
    std::ofstream testFile("stress.ini");
    testFile << "[Section0]\n";
    testFile << "key0=val0\n";

    for (int i = 1; i <= 20; ++i) {
        testFile << "[Section" << i << "]\n";
        for (int j = 1; j <= 15; ++j) {
            testFile << "key" << j << "=val" << j << "\n";
        }
    }
    testFile.close();

    IniParser parser;
    ASSERT_TRUE(parser.loadFile("stress.ini"));

    ASSERT_STREQ(parser.getValue("Section20", "key15"), "val15");

    remove("stress.ini");
}
