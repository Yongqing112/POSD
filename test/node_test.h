#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"

class NodeSuite : public ::testing::Test {
protected:
    void SetUp() override {}

    Node * firstFolder = new Folder("/firstFolder");
    Node * secondFolder = new Folder("/firstFolder/secondFolder");
    Node * thirdFolder = new Folder("/firstFolder/secondFolder/thirdFolder");

    Node * firstFile = new File("/firstFolder/firstFile.txt");
    Node * secondFile = new File("/firstFolder/secondFolder/secondFile.txt");
};

TEST_F(NodeSuite, Ping){
    ASSERT_TRUE(true);
}

TEST_F(NodeSuite, FolderAsNode){
    ASSERT_EQ("firstFolder", firstFolder->name());
    ASSERT_EQ("/firstFolder", firstFolder->path());
}

TEST_F(NodeSuite, FileAsNode){
    ASSERT_EQ("firstFile.txt", firstFile->name());
    ASSERT_EQ("/firstFolder/firstFile.txt", firstFile->path());
}

TEST_F(NodeSuite, AddFileToFolder){
    Node* secondFile = new File("/firstFolder/secondFile.txt");
    firstFolder->add(secondFile);
    ASSERT_EQ(secondFile, firstFolder->find("/firstFolder/secondFile.txt"));
}

TEST_F(NodeSuite, AddFolderToFolder){
    firstFolder->add(secondFolder);
    ASSERT_EQ(secondFolder, firstFolder->find("/firstFolder/secondFolder"));
}

TEST_F(NodeSuite, AddIncorrectPathFileToFolder){
    ASSERT_ANY_THROW(firstFolder->add(thirdFolder));
}

TEST_F(NodeSuite, RemoveFile){
    firstFolder->add(firstFile);
    firstFolder->remove("/firstFolder/firstFile.txt");
    ASSERT_EQ(nullptr, firstFolder->find("/firstFolder/firstFile.txt"));
}

TEST_F(NodeSuite, RemoveDeepFile){
    firstFolder->add(firstFile);
    firstFolder->add(secondFolder);
    secondFolder->add(thirdFolder);
    secondFolder->add(secondFile);
    firstFolder->remove("/firstFolder/secondFolder/secondFile.txt");
    ASSERT_EQ(nullptr, firstFolder->find("/firstFolder/secondFolder/secondFile.txt"));
}

TEST_F(NodeSuite, GetChildByName){
    firstFolder->add(firstFile);
    ASSERT_EQ("firstFile.txt", firstFolder->getChildByName("firstFile.txt")->name());
    firstFolder->remove("/firstFolder/firstFile.txt");
    ASSERT_EQ(nullptr, firstFolder->getChildByName("firstFile.txt"));
}

TEST_F(NodeSuite, FindFileAndFolder){
    firstFolder->add(firstFile);
    firstFolder->add(secondFolder);
    secondFolder->add(thirdFolder);
    secondFolder->add(secondFile);
    ASSERT_EQ(firstFile, firstFolder->find("/firstFolder/firstFile.txt"));
    ASSERT_EQ(thirdFolder, firstFolder->find("/firstFolder/secondFolder/thirdFolder"));
}

TEST_F(NodeSuite, NumberOfFiles){
    firstFolder->add(firstFile);
    firstFolder->add(secondFolder);
    secondFolder->add(thirdFolder);
    secondFolder->add(secondFile);
    ASSERT_EQ(2, firstFolder->numberOfFiles());
    ASSERT_EQ(1, secondFolder->numberOfFiles());
}

TEST_F(NodeSuite, SetParent){
    firstFolder->add(firstFile);
    firstFolder->add(secondFolder);
    ASSERT_EQ(firstFolder, secondFolder->getParent());
    ASSERT_EQ(firstFolder, firstFile->getParent());
}