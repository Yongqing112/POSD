#pragma once
#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"
#include "../src/visitor.h"
#include "../src/find_by_name_visitor.h"
#include "../src/stream_out_visitor.h"


class VisitorTest: public ::testing::Test {
protected:
    void SetUp() {
        test_actual_file_or_folder = Folder::create("test_actual_file_or_folder");

        d_folder = Folder::create("test_actual_file_or_folder/d");
        test_actual_file_or_folder->add(d_folder);
        
        a_file = File::create("test_actual_file_or_folder/a.txt");
        test_actual_file_or_folder->add(a_file);

        b_file = File::create("test_actual_file_or_folder/b.txt");
        test_actual_file_or_folder->add(b_file);

        c_file = File::create("test_actual_file_or_folder/c.txt");
        test_actual_file_or_folder->add(c_file);

        e_file = File::create("test_actual_file_or_folder/d/e.txt");
        d_folder->add(e_file);
    }

    void TearDown() {
        delete test_actual_file_or_folder;
        delete d_folder;
        delete a_file;
        delete b_file;
        delete c_file;
    }
    
    Node * test_actual_file_or_folder;
    Node * d_folder;
    Node * a_file;
    Node * b_file;
    Node * c_file;
    Node * e_file;
};

TEST_F(VisitorTest, StreamOutVisitFolder){
    ASSERT_EQ("test_actual_file_or_folder", test_actual_file_or_folder->path());
    Visitor * visitor = new StreamOutVisitor();
    test_actual_file_or_folder->accept(visitor);
    ASSERT_EQ("_____________________________________________\ntest_actual_file_or_folder/d/e.txt\n---------------------------------------------\nI am file e.\n_____________________________________________\n\n_____________________________________________\ntest_actual_file_or_folder/a.txt\n---------------------------------------------\nI am file a.\n_____________________________________________\n\n_____________________________________________\ntest_actual_file_or_folder/b.txt\n---------------------------------------------\nI am file b.\n_____________________________________________\n\n_____________________________________________\ntest_actual_file_or_folder/c.txt\n---------------------------------------------\nI am file c.\n_____________________________________________\n\n", dynamic_cast<StreamOutVisitor *>(visitor)->getResult());
}

TEST_F(VisitorTest, StreamOutVisitFile){
    ASSERT_EQ("test_actual_file_or_folder/a.txt", a_file->path());
    Visitor * visitor = new StreamOutVisitor();
    a_file->accept(visitor);
    ASSERT_EQ("_____________________________________________\ntest_actual_file_or_folder/a.txt\n---------------------------------------------\nI am file a.\n_____________________________________________\n", dynamic_cast<StreamOutVisitor *>(visitor)->getResult());
}

TEST_F(VisitorTest, FindByNameVisitFolder){
    Visitor * visitor = new FindByNameVisitor("test_actual_file_or_folder");
    test_actual_file_or_folder->accept(visitor);
    ASSERT_FALSE(dynamic_cast<FindByNameVisitor *>(visitor)->getPaths().empty());
    ASSERT_EQ("test_actual_file_or_folder", dynamic_cast<FindByNameVisitor *>(visitor)->getPaths().front());
}

TEST_F(VisitorTest, FindByNameVisitFile){
    Visitor * visitor = new FindByNameVisitor("e.txt");
    test_actual_file_or_folder->accept(visitor);
    ASSERT_FALSE(dynamic_cast<FindByNameVisitor *>(visitor)->getPaths().empty());
    ASSERT_EQ("test_actual_file_or_folder/d/e.txt", dynamic_cast<FindByNameVisitor *>(visitor)->getPaths().front());
}