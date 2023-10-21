#pragma once 

#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"

class NodeTest: public ::testing::Test {
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


TEST_F(NodeTest, numberOfFiles) {
    ASSERT_EQ(6, test_actual_file_or_folder->numberOfFiles());
}

TEST_F(NodeTest, find_a_file) {
    Node * result = test_actual_file_or_folder->find("test_actual_file_or_folder/a.txt");
    ASSERT_EQ(a_file, result);
}

TEST_F(NodeTest, find_a_file_not_exist) {
    Node * result = test_actual_file_or_folder->find("test_actual_file_or_folder/not_exist.txt");
    ASSERT_EQ(nullptr, result);
}

TEST_F(NodeTest, find_a_folder) {
    Node * result = test_actual_file_or_folder->find("test_actual_file_or_folder/g/i");
    ASSERT_EQ(i_folder, result);
}

TEST_F(NodeTest, find_a_folder_not_exist) {
    Node * result = g_folder->find("test_actual_file_or_folder/g/i/not_exist.txt");
    ASSERT_EQ(nullptr, result);
}

TEST_F(NodeTest, delete_a_file) {
    ASSERT_EQ(j_file->name(), test_actual_file_or_folder->find("test_actual_file_or_folder/g/i/j.txt")->name());
    test_actual_file_or_folder->remove("test_actual_file_or_folder/g/i/j.txt");
    ASSERT_EQ(nullptr, test_actual_file_or_folder->find("test_actual_file_or_folder/g/i/j.txt"));
}

TEST_F(NodeTest, delete_a_folder) {
    ASSERT_EQ(i_folder->name(), test_actual_file_or_folder->find("test_actual_file_or_folder/g/i")->name());
    test_actual_file_or_folder->remove("test_actual_file_or_folder/g/i");
    ASSERT_EQ(nullptr, test_actual_file_or_folder->find("test_actual_file_or_folder/g/i"));
}
