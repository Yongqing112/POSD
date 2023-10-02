#include "../src/file.h"
#include "../src/node.h"

TEST(FileSuite, Ping){
    ASSERT_TRUE(true);
}

TEST(FileSuite, CreateFile){
    File firstFile("", "firstFile.txt");
    ASSERT_EQ("firstFile.txt", firstFile.path());
    ASSERT_EQ("firstFile.txt", firstFile.name());
}

TEST(FileSuite, FileAsNode){
    Node * firstFile = new File("", "firstFile.txt");
    ASSERT_EQ("firstFile.txt", firstFile->path());
    ASSERT_EQ("firstFile.txt", firstFile->name());
}