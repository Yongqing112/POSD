#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"

TEST(NodeSuite, Ping){
    ASSERT_TRUE(true);
}

TEST(NodeSuite, FolderAsNode){
    Node * firstFolder = new Folder("/firstFolder");
    ASSERT_EQ("firstFolder", firstFolder->name());
    ASSERT_EQ("/firstFolder", firstFolder->path());
}

TEST(NodeSuite, FileAsNode){
    Node * firstFile = new File("/firstFolder/firstFile.txt");
    ASSERT_EQ("firstFile.txt", firstFile->name());
    ASSERT_EQ("/firstFolder/firstFile.txt", firstFile->path());
}

TEST(NodeSuite, AddIncorrectPathFileToFolder){
    Node * firstFolder = new Folder("/firstFolder");
    Node * thirdFolder = new Folder("/firstFolder/secondFolder/thirdFolder");
    ASSERT_ANY_THROW(firstFolder->add(thirdFolder));
}


TEST(NodeSuite, Remove){
    Node * firstFolder = new Folder("/firstFolder");
    Node * secondFolder = new Folder("/firstFolder/secondFolder");
    Node * thirdFolder = new Folder("/firstFolder/secondFolder/thirdFolder");
    Node * firstFile = new File("/firstFolder/firstFile.txt");
    Node * secondFile = new File("/firstFolder/secondFolder/secondFile.txt");
    firstFolder->add(firstFile);
    firstFolder->add(secondFolder);
    secondFolder->add(thirdFolder);
    secondFolder->add(secondFile);
    firstFolder->remove("/firstFolder/secondFolder/secondFile.txt");
    ASSERT_EQ(nullptr, firstFolder->find("/firstFolder/secondFolder/secondFile.txt"));
}

TEST(NodeSuite, GetChildByName){
    Node * firstFolder = new Folder("/firstFolder");
    Node * firstFile = new File("/firstFolder/firstFile.txt");
    firstFolder->add(firstFile);
    ASSERT_EQ("firstFile.txt", firstFolder->getChildByName("firstFile.txt")->name());
    firstFolder->remove("/firstFolder/firstFile.txt");
    ASSERT_EQ(nullptr, firstFolder->getChildByName("firstFile.txt"));
}

TEST(NodeSuite, Find){
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

TEST(NodeSuite, NumberOfFiles){
    Folder * firstFolder = new Folder("/firstFolder");
    Node * secondFolder = new Folder("/firstFolder/secondFolder");
    Node * thirdFolder = new Folder("/firstFolder/secondFolder/thirdFolder");
    Node * firstFile = new File("/firstFolder/firstFile.txt");
    Node * secondFile = new File("/firstFolder/secondFolder/secondFile.txt");
    firstFolder->add(firstFile);
    firstFolder->add(secondFolder);
    secondFolder->add(thirdFolder);
    secondFolder->add(secondFile);
    ASSERT_EQ(2, firstFolder->numberOfFiles());
    ASSERT_EQ(1, secondFolder->numberOfFiles());
}

TEST(NodeSuite, SetParent){
    Folder * firstFolder = new Folder("/firstFolder");
    Node * secondFolder = new Folder("/firstFolder/secondFolder");
    Node * firstFile = new File("/firstFolder/firstFile.txt");
    firstFolder->add(firstFile);
    firstFolder->add(secondFolder);
    ASSERT_EQ(firstFolder, secondFolder->getParent());
    ASSERT_EQ(firstFolder, firstFile->getParent());
}