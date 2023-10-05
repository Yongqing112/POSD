#include "../src/file.h"
#include "../src/folder.h"

TEST(FolderSuite, Ping){
    ASSERT_TRUE(true);
}

TEST(FolderSuite, CreateFolder){
    Folder firstFolder("/firstFolder");
    ASSERT_EQ("firstFolder", firstFolder.name());
    ASSERT_EQ("/firstFolder", firstFolder.path());
}

TEST(FolderSuite, FolderAsNode){
    Folder * firstFolder = new Folder("/firstFolder");
    ASSERT_EQ("firstFolder", firstFolder->name());
    ASSERT_EQ("/firstFolder", firstFolder->path());
}

TEST(FolderSuite, AddIncorrectPathFileToFolder){
    Folder * firstFolder = new Folder("/firstFolder");
    Folder * thirdFolder = new Folder("/firstFolder/secondFolder/thirdFolder");
    ASSERT_ANY_THROW(firstFolder->add(thirdFolder));
}

TEST(FolderSuite, Remove){
    Folder * firstFolder = new Folder("/firstFolder");
    Folder * secondFolder = new Folder("/firstFolder/secondFolder");
    Folder * thirdFolder = new Folder("/firstFolder/secondFolder/thirdFolder");
    File * firstFile = new File("/firstFolder/firstFile.txt");
    File * secondFile = new File("/firstFolder/secondFolder/secondFile.txt");
    firstFolder->add(firstFile);
    firstFolder->add(secondFolder);
    secondFolder->add(thirdFolder);
    secondFolder->add(secondFile);
    firstFolder->remove("/firstFolder/secondFolder/secondFile.txt");
    ASSERT_EQ(nullptr, firstFolder->find("/firstFolder/secondFolder/secondFile.txt"));
}

TEST(FolderSuite, GetChildByName){
    Folder * firstFolder = new Folder("/firstFolder");
    File * firstFile = new File("/firstFolder/firstFile.txt");
    firstFolder->add(firstFile);
    ASSERT_EQ("firstFile.txt", firstFolder->getChildByName("firstFile.txt")->name());
    firstFolder->remove("/firstFolder/firstFile.txt");
    ASSERT_EQ(nullptr, firstFolder->getChildByName("firstFile.txt"));
}

TEST(FolderSuite, Find){
    Folder * firstFolder = new Folder("/firstFolder");
    Folder * secondFolder = new Folder("/firstFolder/secondFolder");
    Folder * thirdFolder = new Folder("/firstFolder/secondFolder/thirdFolder");
    File * firstFile = new File("/firstFolder/firstFile.txt");
    File * secondFile = new File("/firstFolder/secondFolder/secondFile.txt");
    firstFolder->add(firstFile);
    firstFolder->add(secondFolder);
    secondFolder->add(thirdFolder);
    secondFolder->add(secondFile);
    ASSERT_EQ(firstFile, firstFolder->find("/firstFolder/firstFile.txt"));
    ASSERT_EQ(secondFile, firstFolder->find("/firstFolder/secondFolder/secondFile.txt"));
}

TEST(FolderSuite, NumberOfFiles){
    Folder * firstFolder = new Folder("/firstFolder");
    Folder * secondFolder = new Folder("/firstFolder/secondFolder");
    Folder * thirdFolder = new Folder("/firstFolder/secondFolder/thirdFolder");
    File * firstFile = new File("/firstFolder/firstFile.txt");
    File * secondFile = new File("/firstFolder/secondFolder/secondFile.txt");
    firstFolder->add(firstFile);
    firstFolder->add(secondFolder);
    secondFolder->add(thirdFolder);
    secondFolder->add(secondFile);
    ASSERT_EQ(2, firstFolder->numberOfFiles());
}