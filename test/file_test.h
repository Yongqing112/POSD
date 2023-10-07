#include "../src/file.h"

TEST(FileSuite, Ping){
    ASSERT_TRUE(true);
}

TEST(FileSuite, CreateFile){
    File firstFile("/firstFolder/firstFile.txt");
    ASSERT_EQ("/firstFolder/firstFile.txt", firstFile.path());
    ASSERT_EQ("firstFile.txt", firstFile.name());
}