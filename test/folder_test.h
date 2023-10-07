#include "../src/file.h"
#include "../src/folder.h"

class FolderSuite : public ::testing::Test {
protected:
    void SetUp() override {}

    Folder * firstFolder = new Folder("/firstFolder");
    Folder * secondFolder = new Folder("/firstFolder/secondFolder");
    Folder * thirdFolder = new Folder("/firstFolder/secondFolder/thirdFolder");

    File * firstFile = new File("/firstFolder/firstFile.txt");
    File * secondFile = new File("/firstFolder/secondFolder/secondFile.txt");
};


TEST_F(FolderSuite, Ping){
    ASSERT_TRUE(true);
}

TEST_F(FolderSuite, CreateFolder){
    ASSERT_EQ("firstFolder", firstFolder->name());
    ASSERT_EQ("/firstFolder", firstFolder->path());
}

TEST_F(FolderSuite, AddFileToFolder){
    firstFolder->add(firstFile);
    ASSERT_EQ(firstFile, firstFolder->find("/firstFolder/firstFile.txt"));
}

TEST_F(FolderSuite, AddFolderToFolder){
    firstFolder->add(secondFolder);
    ASSERT_EQ(secondFolder, firstFolder->find("/firstFolder/secondFolder"));
}

TEST_F(FolderSuite, AddIncorrectPathFileToFolder){
    ASSERT_ANY_THROW(firstFolder->add(thirdFolder));
}

TEST_F(FolderSuite, RemoveFile){
    firstFolder->add(firstFile);
    firstFolder->remove("/firstFolder/firstFile.txt");
    ASSERT_EQ(nullptr, firstFolder->find("/firstFolder/firstFile.txt"));
}

TEST_F(FolderSuite, RemoveDeepFile){
    firstFolder->add(firstFile);
    firstFolder->add(secondFolder);
    secondFolder->add(thirdFolder);
    secondFolder->add(secondFile);
    firstFolder->remove("/firstFolder/secondFolder/secondFile.txt");
    ASSERT_EQ(nullptr, firstFolder->find("/firstFolder/secondFolder/secondFile.txt"));
}

TEST_F(FolderSuite, GetChildByName){
    firstFolder->add(firstFile);
    ASSERT_EQ("firstFile.txt", firstFolder->getChildByName("firstFile.txt")->name());
    firstFolder->remove("/firstFolder/firstFile.txt");
    ASSERT_EQ(nullptr, firstFolder->getChildByName("firstFile.txt"));
}

TEST_F(FolderSuite, FindFileAndFolder){
    firstFolder->add(firstFile);
    firstFolder->add(secondFolder);
    secondFolder->add(thirdFolder);
    secondFolder->add(secondFile);
    ASSERT_EQ(firstFile, firstFolder->find("/firstFolder/firstFile.txt"));
    ASSERT_EQ(thirdFolder, firstFolder->find("/firstFolder/secondFolder/thirdFolder"));
}

TEST_F(FolderSuite, NumberOfFiles){
    firstFolder->add(firstFile);
    firstFolder->add(secondFolder);
    secondFolder->add(thirdFolder);
    secondFolder->add(secondFile);
    ASSERT_EQ(2, firstFolder->numberOfFiles());
}