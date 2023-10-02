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
    //std::list<Node *> nodes = {};
    Node * firstFolder = new Folder("", "firstFolder");
    firstFolder->add(new Folder(firstFolder->name() + "/secondFolder", "secondFolder"));
    Iterator * it = firstFolder->createIterator();
    it->first();
    ASSERT_TRUE(it->isDone());
}