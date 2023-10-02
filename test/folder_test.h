#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"
#include <list>

TEST(FolderSuite, Ping){
    ASSERT_TRUE(true);
}

TEST(FolderSuite, CreateFolder){
    Folder firstFolder("", "firstFolder");
    ASSERT_EQ("firstFolder", firstFolder.name());
    ASSERT_EQ("firstFolder", firstFolder.path());
}

TEST(FolderSuite, FolderAsNode){
    Node * firstFolder = new Folder("", "firstFolder");
    ASSERT_EQ("firstFolder", firstFolder->name());
    ASSERT_EQ("firstFolder", firstFolder->path());
}

TEST(FolderSuite, Iterator){
    std::vector<Node *> nodes = {new File("/firstFolder/firstFile.txt","firstFile.txt"), new File("/firstFolder/secondFile.txt","secondFile.txt")};
    Folder * firstFolder = new Folder("/firstFolder/", "firstFolder", nodes);
    FolderIterator * it = firstFolder->createIterator();
    it->first();
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("secondFile.txt", it->currentItem()->name());
    it->next();
    ASSERT_TRUE(it->isDone());
    delete it;
}