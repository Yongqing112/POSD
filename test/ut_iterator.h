#pragma once 

#include "../src/node.h"
#include "../src/folder.h"
#include "../src/file.h"
#include "../src/iterator.h"
#include "../src/dfs_iterator.h"

class IteratorTest: public ::testing::Test {
protected:
    void SetUp() {
        test_actual_file_or_folder = Folder::create("test_actual_file_or_folder");

        d_folder = Folder::create("test_actual_file_or_folder/d");
        test_actual_file_or_folder->add(d_folder);
        
        g_folder = Folder::create("test_actual_file_or_folder/g");
        test_actual_file_or_folder->add(g_folder);

        a_file = File::create("test_actual_file_or_folder/a.txt");
        test_actual_file_or_folder->add(a_file);

        b_file = File::create("test_actual_file_or_folder/b.txt");
        test_actual_file_or_folder->add(b_file);

        c_file = File::create("test_actual_file_or_folder/c.txt");
        test_actual_file_or_folder->add(c_file);

        e_file = File::create("test_actual_file_or_folder/d/e.txt");
        d_folder->add(e_file);

        h_file = File::create("test_actual_file_or_folder/g/h.txt");
        g_folder->add(h_file);

        i_folder = Folder::create("test_actual_file_or_folder/g/i");
        g_folder->add(i_folder);

        j_file = File::create("test_actual_file_or_folder/g/i/j.txt");
        i_folder->add(j_file);
    }

    void TearDown() {
        delete test_actual_file_or_folder;
        delete d_folder;
        delete g_folder;
        delete i_folder;
        delete a_file;
        delete b_file;
        delete c_file;
        delete e_file;
        delete h_file;
        delete j_file;
    }
    
    Node * test_actual_file_or_folder;
    Node * d_folder;
    Node * g_folder;
    Node * i_folder;
    Node * a_file;
    Node * b_file;
    Node * c_file;
    Node * e_file;
    Node * h_file;
    Node * j_file;
};

TEST_F(IteratorTest, Normal) {
    Iterator * it = test_actual_file_or_folder->createIterator();
    it->first();
    ASSERT_FALSE(it->isDone());
    
    ASSERT_EQ("d", it->currentItem()->name());
    
    it->next();
    ASSERT_EQ("g", it->currentItem()->name());

    it->next();
    ASSERT_EQ("a.txt", it->currentItem()->name());

    it->next();
    ASSERT_EQ("b.txt", it->currentItem()->name());

    it->next();
    ASSERT_EQ("c.txt", it->currentItem()->name());

    it->next();
    ASSERT_TRUE(it->isDone());
}

TEST_F(IteratorTest, DFS) {
    Iterator * dfsIt = new DfsIterator(test_actual_file_or_folder);

    dfsIt->first();
    ASSERT_EQ("d", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("e.txt", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("g", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("h.txt", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("i", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("j.txt", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("a.txt", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("b.txt", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("c.txt", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_TRUE(dfsIt->isDone());
}


TEST_F(IteratorTest, BFS) {
    Iterator * bfsIt = new BfsIterator(test_actual_file_or_folder);

    bfsIt->first();
    ASSERT_EQ("d", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_EQ("g", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_EQ("a.txt", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_EQ("b.txt", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_EQ("c.txt", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_EQ("e.txt", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_EQ("h.txt", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_EQ("i", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_EQ("j.txt", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_TRUE(bfsIt->isDone());
}
