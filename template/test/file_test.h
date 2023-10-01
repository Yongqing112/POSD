#include "../src/file.h"
#include "../src/node.h"

TEST(FileSuite, Ping){
    ASSERT_TRUE(true);
}

TEST(FileSuite, CreateFile){
    File f("/Users/user/home/", "create.txt");
    ASSERT_EQ("/Users/user/home/create.txt", f.path());
    ASSERT_EQ("create.txt", f.name());
}

TEST(FileSuite, FileAsNode){
    Node * file = new File("/Users/user/home/", "create.txt");
    ASSERT_EQ("/Users/user/home/create.txt", file->path());
    ASSERT_EQ("create.txt", file->name());
}