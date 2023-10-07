#include "../src/file.h"
#include "../src/folder.h"
#include "../src/iterator.h"
#include "../src/null_iterator.h"
#include "../src/dfs_iterator.h"

class IteratorSuite : public ::testing::Test {
protected:
    void SetUp() override {}

    Folder * firstFolder = new Folder("/firstFolder");
    Folder * secondFolder = new Folder("/firstFolder/secondFolder");
    Folder * thirdFolder = new Folder("/firstFolder/secondFolder/thirdFolder");
    Folder * forthFolder = new Folder("/firstFolder/forthFolder");
    Folder * fifthFolder = new Folder("/firstFolder/fifthFolder");
    Folder * sixthFolder = new Folder("/firstFolder/secondFolder/sixthFolder");
    Folder * seventhFolder = new Folder("/firstFolder/fifthFolder/seventhFolder");
    
    File * firstFile = new File("/firstFolder/firstFile.txt");
    File * secondFile = new File("/firstFolder/secondFolder/secondFile.txt");
    File * thirdFile = new File("/firstFolder/secondFolder/thirdFolder/thirdFile.txt");
    File * forthFile = new File("/firstFolder/fifthFolder/forthFile.txt");
};

TEST_F(IteratorSuite, AddAndGetChildByNameAndFindInSubNode){
    firstFolder->add(secondFolder);
    FolderIterator * it = firstFolder->createIterator();
    it->first();
    it->currentItem()->add(secondFile);
    ASSERT_EQ("secondFile.txt", it->currentItem()->getChildByName("secondFile.txt")->name());
    ASSERT_EQ(secondFile, it->currentItem()->find("/firstFolder/secondFolder/secondFile.txt"));
    delete it;
}

TEST_F(IteratorSuite, NumberOfFiles){
    firstFolder->add(firstFile);
    firstFolder->add(secondFolder);
    secondFolder->add(thirdFolder);
    FolderIterator * it = firstFolder->createIterator();
    it->first();//firstFile
    it->next();//secondFolder
    it->currentItem()->add(secondFile);//secondFolder add secondFile
    ASSERT_EQ(2, firstFolder->numberOfFiles());
}

TEST_F(IteratorSuite, SetParent){
    firstFolder->add(firstFile);
    firstFolder->add(secondFolder);
    FolderIterator * it = firstFolder->createIterator();
    it->first();//firstFile
    ASSERT_EQ(firstFolder, it->currentItem()->getParent());
    it->next();//secondFolder
    ASSERT_EQ(firstFolder, it->currentItem()->getParent());
    delete it;
}

TEST_F(IteratorSuite, IsDone){
    firstFolder->add(firstFile);
    FolderIterator * it = firstFolder->createIterator();
    it->first();//firstFile
    it->next();
    ASSERT_TRUE(it->isDone());
}

TEST_F(IteratorSuite, NullIterator){
    NullIterator * it = firstFile->createIterator();
    ASSERT_TRUE(it->isDone());
}

TEST_F(IteratorSuite, DFS){
    firstFolder->add(forthFolder);
    firstFolder->add(secondFolder);
    firstFolder->add(firstFile);
    firstFolder->add(fifthFolder);
    secondFolder->add(thirdFolder);
    secondFolder->add(secondFile);
    thirdFolder->add(thirdFile);
    
    DfsIterator * it = new DfsIterator(firstFolder);
    it->first();//forthFolder
    ASSERT_EQ("forthFolder", it->currentItem()->name());
    ASSERT_EQ("/firstFolder/forthFolder", it->currentItem()->path());

    it->next();//secondFolder 
    ASSERT_EQ("secondFolder", it->currentItem()->name());
    ASSERT_EQ("/firstFolder/secondFolder", it->currentItem()->path());
    ASSERT_FALSE(it->isDone());
    
    it->next();//thirdFolder
    ASSERT_EQ("thirdFolder", it->currentItem()->name());
    ASSERT_EQ("/firstFolder/secondFolder/thirdFolder", it->currentItem()->path());
    ASSERT_FALSE(it->isDone());
    
    it->next();//thirdFile
    ASSERT_EQ("thirdFile.txt", it->currentItem()->name());
    ASSERT_EQ("/firstFolder/secondFolder/thirdFolder/thirdFile.txt", it->currentItem()->path());
    ASSERT_FALSE(it->isDone());
    
    it->next();//secondFile
    ASSERT_EQ("secondFile.txt", it->currentItem()->name());
    ASSERT_EQ("/firstFolder/secondFolder/secondFile.txt", it->currentItem()->path());
    ASSERT_FALSE(it->isDone());
    
    it->next();//firstFile
    ASSERT_EQ("firstFile.txt", it->currentItem()->name());
    ASSERT_EQ("/firstFolder/firstFile.txt", it->currentItem()->path());
    ASSERT_FALSE(it->isDone());

    it->next();
    ASSERT_EQ("fifthFolder", it->currentItem()->name());
    ASSERT_EQ("/firstFolder/fifthFolder", it->currentItem()->path());
    ASSERT_FALSE(it->isDone());

    it->next();
    ASSERT_TRUE(it->isDone());

    delete it;
}

TEST_F(IteratorSuite, BFS){
    firstFolder->add(forthFolder);
    firstFolder->add(secondFolder);
    firstFolder->add(firstFile);
    firstFolder->add(fifthFolder);
    secondFolder->add(thirdFolder);
    secondFolder->add(secondFile);
    secondFolder->add(sixthFolder);
    thirdFolder->add(thirdFile);
    fifthFolder->add(seventhFolder);
    fifthFolder->add(forthFile);

    BfsIterator * it = new BfsIterator(firstFolder);
    it->first();//forthFolder
    ASSERT_EQ("forthFolder", it->currentItem()->name());
    ASSERT_EQ("/firstFolder/forthFolder", it->currentItem()->path());

    it->next();//secondFolder 
    ASSERT_EQ("secondFolder", it->currentItem()->name());
    ASSERT_EQ("/firstFolder/secondFolder", it->currentItem()->path());
    ASSERT_FALSE(it->isDone());

    it->next();//firstFile 
    ASSERT_EQ("firstFile.txt", it->currentItem()->name());
    ASSERT_EQ("/firstFolder/firstFile.txt", it->currentItem()->path());
    ASSERT_FALSE(it->isDone());

    it->next();//fifthFolder 
    ASSERT_EQ("fifthFolder", it->currentItem()->name());
    ASSERT_EQ("/firstFolder/fifthFolder", it->currentItem()->path());
    ASSERT_FALSE(it->isDone());

    it->next();//thirdFolder 
    ASSERT_EQ("thirdFolder", it->currentItem()->name());
    ASSERT_EQ("/firstFolder/secondFolder/thirdFolder", it->currentItem()->path());
    ASSERT_FALSE(it->isDone());

    it->next();//secondFile 
    ASSERT_EQ("secondFile.txt", it->currentItem()->name());
    ASSERT_EQ("/firstFolder/secondFolder/secondFile.txt", it->currentItem()->path());
    ASSERT_FALSE(it->isDone());

    it->next();//sixthFolder 
    ASSERT_EQ("sixthFolder", it->currentItem()->name());
    ASSERT_EQ("/firstFolder/secondFolder/sixthFolder", it->currentItem()->path());
    ASSERT_FALSE(it->isDone());

    it->next();//seventhFolder 
    ASSERT_EQ("seventhFolder", it->currentItem()->name());
    ASSERT_EQ("/firstFolder/fifthFolder/seventhFolder", it->currentItem()->path());
    ASSERT_FALSE(it->isDone());

    it->next();//forthFile
    ASSERT_EQ("forthFile.txt", it->currentItem()->name());
    ASSERT_EQ("/firstFolder/fifthFolder/forthFile.txt", it->currentItem()->path());
    ASSERT_FALSE(it->isDone());

    it->next();//thirdFile 
    ASSERT_EQ("thirdFile.txt", it->currentItem()->name());
    ASSERT_EQ("/firstFolder/secondFolder/thirdFolder/thirdFile.txt", it->currentItem()->path());
    ASSERT_FALSE(it->isDone());

    it->next();
    ASSERT_TRUE(it->isDone());
    delete it;
}