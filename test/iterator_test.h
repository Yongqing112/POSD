#include "../src/file.h"
#include "../src/folder.h"
#include "../src/iterator.h"

TEST(IteratorSuite, AddAndGetChildByNameAndFindInSubNode){
    Folder * firstFolder = new Folder("/firstFolder");
    Folder * secondFolder = new Folder("/firstFolder/secondFolder");
    File * firstFile = new File("/firstFolder/secondFolder/firstFile.txt");
    firstFolder->add(secondFolder);
    FolderIterator * it = firstFolder->createIterator();
    it->first();
    it->currentItem()->add(firstFile);
    ASSERT_EQ("firstFile.txt", it->currentItem()->getChildByName("firstFile.txt")->name());
    ASSERT_EQ(firstFile, it->currentItem()->find("/firstFolder/secondFolder/firstFile.txt"));
    delete it;
}

TEST(IteratorSuite, NumberOfFiles){
    Folder * firstFolder = new Folder("/firstFolder");
    Folder * secondFolder = new Folder("/firstFolder/secondFolder");
    Folder * thirdFolder = new Folder("/firstFolder/secondFolder/thirdFolder");
    File * firstFile = new File("/firstFolder/firstFile.txt");
    File * secondFile = new File("/firstFolder/secondFolder/secondFile.txt");
    firstFolder->add(firstFile);
    firstFolder->add(secondFolder);
    secondFolder->add(thirdFolder);
    FolderIterator * it = firstFolder->createIterator();
    it->first();//firstFile
    it->next();//secondFolder
    it->currentItem()->add(secondFile);//secondFolder add secondFile
    ASSERT_EQ(2, firstFolder->numberOfFiles());
}

TEST(IteratorSuite, SetParent){
    Folder * firstFolder = new Folder("/firstFolder");
    Folder * secondFolder = new Folder("/firstFolder/secondFolder");
    File * firstFile = new File("/firstFolder/firstFile.txt");
    firstFolder->add(firstFile);
    firstFolder->add(secondFolder);
    FolderIterator * it = firstFolder->createIterator();
    it->first();//firstFile
    Node * parent = it->currentItem()->getParent();
    ASSERT_EQ(firstFolder, parent);
    it->next();//secondFolder
    parent = it->currentItem()->getParent();
    ASSERT_EQ(firstFolder, parent);
    delete it;
}