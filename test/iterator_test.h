#include "../src/file.h"
#include "../src/folder.h"
#include "../src/iterator.h"

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

TEST_F(IteratorSuite, NumberOfFiles){
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

TEST_F(IteratorSuite, SetParent){
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

TEST_F(IteratorSuite, IsDone){
    Folder * firstFolder = new Folder("/firstFolder");
    File * firstFile = new File("/firstFolder/firstFile.txt");
    firstFolder->add(firstFile);

    FolderIterator * it = firstFolder->createIterator();

    it->first();//firstFile
    it->next();
    ASSERT_TRUE(it->isDone());
}

TEST_F(IteratorSuite, DFS){
    DfsIterator * it = new DfsIterator(firstFolder);
    
    firstFolder->add(forthFolder);
    firstFolder->add(secondFolder);
    firstFolder->add(firstFile);
    firstFolder->add(fifthFolder);
    
    secondFolder->add(thirdFolder);
    secondFolder->add(secondFile);
    
    thirdFolder->add(thirdFile);
    
    cout << "first ------ forthFolder" << endl << endl;
    it->first();//forthFolder
    ASSERT_EQ("forthFolder", it->currentItem()->name());
    ASSERT_EQ("/firstFolder/forthFolder", it->currentItem()->path());

    cout << "go to ------ secondFolder" << endl;
    it->next();//secondFolder 
    ASSERT_EQ("secondFolder", it->currentItem()->name());
    ASSERT_EQ("/firstFolder/secondFolder", it->currentItem()->path());
    ASSERT_FALSE(it->isDone());
    
    cout << "go to ------ thirdFolder" << endl;
    it->next();//thirdFolder
    ASSERT_EQ("thirdFolder", it->currentItem()->name());
    ASSERT_EQ("/firstFolder/secondFolder/thirdFolder", it->currentItem()->path());
    ASSERT_FALSE(it->isDone());
    
    cout << "go to ------ thirdFile" << endl;
    it->next();//thirdFile
    ASSERT_EQ("thirdFile.txt", it->currentItem()->name());
    ASSERT_EQ("/firstFolder/secondFolder/thirdFolder/thirdFile.txt", it->currentItem()->path());
    ASSERT_FALSE(it->isDone());
    
    cout << "go to ------ secondFile" << endl;
    it->next();//secondFile
    ASSERT_EQ("secondFile.txt", it->currentItem()->name());
    ASSERT_EQ("/firstFolder/secondFolder/secondFile.txt", it->currentItem()->path());
    ASSERT_FALSE(it->isDone());
    
    cout << "go to ------ firstFile" << endl;
    it->next();//firstFile
    ASSERT_EQ("firstFile.txt", it->currentItem()->name());
    ASSERT_EQ("/firstFolder/firstFile.txt", it->currentItem()->path());
    ASSERT_FALSE(it->isDone());

    cout<< "go to ------ fifthFolder" << endl;
    it->next();
    ASSERT_EQ("fifthFolder", it->currentItem()->name());
    ASSERT_EQ("/firstFolder/fifthFolder", it->currentItem()->path());
    ASSERT_FALSE(it->isDone());

    cout<< "go to ------ ???????????" << endl;
    it->next();
    ASSERT_TRUE(it->isDone());

    delete it;
}

TEST_F(IteratorSuite, BFS){
    BfsIterator * it = new BfsIterator(firstFolder);
    
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

    cout << "first ------ forthFolder" << endl << endl;
    it->first();//forthFolder
    ASSERT_EQ("forthFolder", it->currentItem()->name());
    ASSERT_EQ("/firstFolder/forthFolder", it->currentItem()->path());

    cout << "go to ------ secondFolder" << endl;
    it->next();//secondFolder 
    ASSERT_EQ("secondFolder", it->currentItem()->name());
    ASSERT_EQ("/firstFolder/secondFolder", it->currentItem()->path());
    ASSERT_FALSE(it->isDone());

    cout << "go to ------ firstFile" << endl;
    it->next();//firstFile 
    ASSERT_EQ("firstFile.txt", it->currentItem()->name());
    ASSERT_EQ("/firstFolder/firstFile.txt", it->currentItem()->path());
    ASSERT_FALSE(it->isDone());

    cout << "go to ------ fifthFolder" << endl;
    it->next();//fifthFolder 
    ASSERT_EQ("fifthFolder", it->currentItem()->name());
    ASSERT_EQ("/firstFolder/fifthFolder", it->currentItem()->path());
    ASSERT_FALSE(it->isDone());

    cout << "go to ------ thirdFolder" << endl;
    it->next();//thirdFolder 
    ASSERT_EQ("thirdFolder", it->currentItem()->name());
    ASSERT_EQ("/firstFolder/secondFolder/thirdFolder", it->currentItem()->path());
    ASSERT_FALSE(it->isDone());

    cout << "go to ------ secondFile" << endl;
    it->next();//secondFile 
    ASSERT_EQ("secondFile.txt", it->currentItem()->name());
    ASSERT_EQ("/firstFolder/secondFolder/secondFile.txt", it->currentItem()->path());
    ASSERT_FALSE(it->isDone());

    cout << "go to ------ sixthFolder" << endl;
    it->next();//sixthFolder 
    ASSERT_EQ("sixthFolder", it->currentItem()->name());
    ASSERT_EQ("/firstFolder/secondFolder/sixthFolder", it->currentItem()->path());
    ASSERT_FALSE(it->isDone());

    cout << "go to ------ seventhFolder" << endl;
    it->next();//seventhFolder 
    ASSERT_EQ("seventhFolder", it->currentItem()->name());
    ASSERT_EQ("/firstFolder/fifthFolder/seventhFolder", it->currentItem()->path());
    ASSERT_FALSE(it->isDone());

    cout << "go to ------ forthFile" << endl;
    it->next();//forthFile
    ASSERT_EQ("forthFile.txt", it->currentItem()->name());
    ASSERT_EQ("/firstFolder/fifthFolder/forthFile.txt", it->currentItem()->path());
    ASSERT_FALSE(it->isDone());

    cout << "go to ------ thirdFile" << endl;
    it->next();//thirdFile 
    ASSERT_EQ("thirdFile.txt", it->currentItem()->name());
    ASSERT_EQ("/firstFolder/secondFolder/thirdFolder/thirdFile.txt", it->currentItem()->path());
    ASSERT_FALSE(it->isDone());

    cout << "go to ------ ?????????" << endl;
    it->next();
    ASSERT_TRUE(it->isDone());
    delete it;
}