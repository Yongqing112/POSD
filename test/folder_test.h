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
    std::vector<Node *> nodes = {new File("/firstFolder/","firstFile.txt"), new File("/firstFolder/","secondFile.txt")};
    Folder * firstFolder = new Folder("", "firstFolder", nodes);
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

TEST(FolderSuite, Add){
    std::vector<Node *> nodes = {new Folder("/firstFolder/", "secondFolder")};
    Folder * firstFolder = new Folder("", "firstFolder", nodes);
    FolderIterator * it = firstFolder->createIterator();
    it->first();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("secondFolder", it->currentItem()->name());
    File firstFile("/firstFolder/", "firstFile.txt");
    firstFolder->add(&firstFile);
    Node * f = firstFolder->getChildByName("firstFile.txt");
    ASSERT_EQ("firstFile.txt", f->name());
    
    delete it;

}

TEST(FolderSuite, Remove){
    std::vector<Node *> nodes = {new Folder("/firstFolder/", "secondFolder")};
    Folder * firstFolder = new Folder("", "firstFolder", nodes);
    firstFolder->remove("/firstFolder/secondFolder");
    FolderIterator * it = firstFolder->createIterator();
    it->first();
    ASSERT_TRUE(it->isDone());
    delete it;

}

TEST(FolderSuite, GetChildByName){
    std::vector<Node *> nodes = {new File("/firstFolder/","firstFile.txt"), new File("/firstFolder/","secondFile.txt")};
    Folder * firstFolder = new Folder("/firstFolder/", "firstFolder", nodes);
    Node * f = firstFolder->getChildByName("firstFile.txt");
    ASSERT_EQ("firstFile.txt", f->name());
}

TEST(FolderSuite, AddAndGetChildByNameInSubFolder){
    std::vector<Node *> nodes = {new Folder("/firstFolder/", "secondFolder")};
    Folder * firstFolder = new Folder("", "firstFolder", nodes);
    FolderIterator * it = firstFolder->createIterator();
    Folder * thirdFolder= new Folder("/firstFolder/secondFolder", "thirdFolder");
    it->first();
    it->currentItem()->add(thirdFolder);
    Node * f = it->currentItem();
    Node * folder = f->getChildByName("thirdFolder");
    ASSERT_EQ("thirdFolder", folder->name());
    delete it;
}


TEST(FolderSuite, Find){
    std::vector<Node *> secondFolderNodes = {new File("/firstFolder/secondFolder","firstFile.txt")};
    std::vector<Node *> nodes = {new File("/firstFolder/", "firstFile.txt"),new File("/firstFolder/","secondFile.txt"), new Folder("/firstFolder/", "secondFolder", secondFolderNodes)};
    Folder * firstFolder = new Folder("/fistFolder/", "firstFolder", nodes);
    Node * f = firstFolder->find("/firstFolder/firstFile.txt");
    ASSERT_EQ("/firstFolder/firstFile.txt", f->path());
    f = firstFolder->find("/firstFolder/secondFolder/firstFile.txt");
    // ASSERT_EQ("/firstFolder/firstFile.txt", f->path());
}