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
    ASSERT_TRUE(loadSuccess);

    ASSERT_EQ(parser.getValue("Database", "host"), "localhost");
    ASSERT_EQ(parser.getValue("Database", "port"), "8080");

    ASSERT_EQ(parser.getValue("User", "name"), "juanlu");
}

TEST_F(IniParserLoadTest, ReturnsEmptyForNonExistentKey) {
    parser.loadFile("test.ini");
    ASSERT_EQ(parser.getValue("Database", "non_existent_key"), "");
}

TEST(IniParserStandaloneTest, FailsIfFileDoesNotExist) {
    IniParser p;
    ASSERT_FALSE(p.loadFile("non_existent_file.ini"));
}