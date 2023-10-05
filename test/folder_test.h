#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"
#include <list>

TEST(FolderSuite, Ping){
    ASSERT_TRUE(true);
}

TEST(FolderSuite, CreateFolder){
    Folder firstFolder("/firstFolder");
    ASSERT_EQ("firstFolder", firstFolder.name());
    ASSERT_EQ("/firstFolder", firstFolder.path());
}

TEST(FolderSuite, FolderAsNode){
    Node * firstFolder = new Folder("/firstFolder");
    ASSERT_EQ("firstFolder", firstFolder->name());
    ASSERT_EQ("/firstFolder", firstFolder->path());
}

TEST(FolderSuite, AddAndIterator){
    Folder * firstFolder = new Folder("/firstFolder");
    Node * firstFile = new File("/firstFolder/firstFile.txt");
    firstFolder->add(firstFile);
    FolderIterator * it = firstFolder->createIterator();
    it->first();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("firstFile.txt", it->currentItem()->getName());
    ASSERT_EQ("/firstFolder/firstFile.txt", it->currentItem()->getPath());
    it->next();
    ASSERT_TRUE(it->isDone());
    delete it;
}

TEST(FolderSuite, AddIncorrectPathFileToFolder){
    Node * firstFolder = new Folder("/firstFolder");
    Folder * thirdFolder = new Folder("/firstFolder/secondFolder/thirdFolder");
    ASSERT_ANY_THROW(firstFolder->add(thirdFolder));
}


TEST(FolderSuite, Remove){
    Folder * firstFolder = new Folder("/firstFolder");
    Node * firstFile = new File("/firstFolder/firstFile.txt");
    firstFolder->add(firstFile);
    FolderIterator * it = firstFolder->createIterator();
    it->first();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("firstFile.txt", it->currentItem()->getName());
    firstFolder->remove("/firstFolder/firstFile.txt");
    it->first();
    ASSERT_TRUE(it->isDone());
    delete it;
}

TEST(FolderSuite, GetChildByName){
    Folder * firstFolder = new Folder("/firstFolder");
    Node * firstFile = new File("/firstFolder/firstFile.txt");
    firstFolder->add(firstFile);
    ASSERT_EQ("firstFile.txt", firstFolder->getChildByName("firstFile.txt")->name());
    firstFolder->remove("/firstFolder/firstFile.txt");
    ASSERT_EQ(nullptr, firstFolder->getChildByName("firstFile.txt"));
}

TEST(FolderSuite, Find){
    Node * firstFolder = new Folder("/firstFolder");
    Node * secondFolder = new Folder("/firstFolder/secondFolder");
    Node * thirdFolder = new Folder("/firstFolder/secondFolder/thirdFolder");
    Node * firstFile = new File("/firstFolder/firstFile.txt");
    Node * secondFile = new File("/firstFolder/secondFolder/secondFile.txt");
    firstFolder->add(firstFile);
    firstFolder->add(secondFolder);
    secondFolder->add(thirdFolder);
    secondFolder->add(secondFile);
    ASSERT_EQ(firstFile, firstFolder->find("/firstFolder/firstFile.txt"));
    ASSERT_EQ(secondFile, firstFolder->find("/firstFolder/secondFolder/secondFile.txt"));
}

TEST(FolderSuite, AddAndGetChildByNameAndFindInSubNode){
    Folder * firstFolder = new Folder("/firstFolder");
    Folder * secondFolder = new Folder("/firstFolder/secondFolder");
    Node * firstFile = new File("/firstFolder/secondFolder/firstFile.txt");
    firstFolder->add(secondFolder);
    FolderIterator * it = firstFolder->createIterator();
    it->first();
    it->currentItem()->add(firstFile);
    ASSERT_EQ("firstFile.txt", it->currentItem()->getChildByName("firstFile.txt")->name());
    ASSERT_EQ("/firstFolder/secondFolder/firstFile.txt", it->currentItem()->find("/firstFolder/secondFolder/firstFile.txt")->path());
    delete it;
}

TEST(FolderSuite, NumberOfFiles){
    Folder * firstFolder = new Folder("/firstFolder");
    Folder * secondFolder = new Folder("/firstFolder/secondFolder");
    Folder * thirdFolder = new Folder("/firstFolder/secondFolder/thirdFolder");
    Node * firstFile = new File("/firstFolder/firstFile.txt");
    Node * secondFile = new File("/firstFolder/secondFolder/secondFile.txt");
    firstFolder->add(firstFile);
    firstFolder->add(secondFolder);
    secondFolder->add(thirdFolder);
    FolderIterator * it = firstFolder->createIterator();
    it->first();//firstFile
    it->next();//secondFolder
    it->currentItem()->add(secondFile);//secondFolder add secondFile
    ASSERT_EQ(2, firstFolder->numberOfFiles());
}

TEST(FolderSuite, SetParent){
    Folder * firstFolder = new Folder("/firstFolder");
    Folder * secondFolder = new Folder("/firstFolder/secondFolder");
    Node * firstFile = new File("/firstFolder/firstFile.txt");
    firstFolder->add(firstFile);
    firstFolder->add(secondFolder);
    FolderIterator * it = firstFolder->createIterator();
    it->first();//firstFile
    Node * parent = it->currentItem()->getParent();
    ASSERT_EQ("/firstFolder", parent->path());
    it->next();//secondFolder
    parent = it->currentItem()->getParent();
    ASSERT_EQ("/firstFolder", parent->path());
    delete it;
}