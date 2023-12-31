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
        
        g_folder = Folder::create("test_actual_file_or_folder/g");
        test_actual_file_or_folder->add(g_folder);

        a_file = File::create("test_actual_file_or_folder/a.txt");
        test_actual_file_or_folder->add(a_file);

        b_file = File::create("test_actual_file_or_folder/b.txt");
        test_actual_file_or_folder->add(b_file);

        c_file = File::create("test_actual_file_or_folder/c.txt");
        test_actual_file_or_folder->add(c_file);

        e_file_2 = File::create("test_actual_file_or_folder/e.txt");
        test_actual_file_or_folder->add(e_file_2);

        i_folder = Folder::create("test_actual_file_or_folder/i");
        test_actual_file_or_folder->add(i_folder);

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
        delete i_folder_2;
        delete a_file;
        delete b_file;
        delete c_file;
        delete e_file;
        delete e_file_2;
        delete h_file;
        delete j_file;
    }
    
    Node * test_actual_file_or_folder;
    Node * d_folder;
    Node * g_folder;
    Node * i_folder;
    Node * i_folder_2;
    Node * a_file;
    Node * b_file;
    Node * c_file;
    Node * e_file;
    Node * e_file_2;
    Node * h_file;
    Node * j_file;
};

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

TEST_F(VisitorTest, ManyFindByNameVisitFolder){
    Visitor * visitor = new FindByNameVisitor("i");
    test_actual_file_or_folder->accept(visitor);
    ASSERT_FALSE(dynamic_cast<FindByNameVisitor *>(visitor)->getPaths().empty());
    auto paths = dynamic_cast<FindByNameVisitor *>(visitor)->getPaths();
    ASSERT_EQ("test_actual_file_or_folder/g/i", paths.front());
    paths.pop_front();
    ASSERT_EQ("test_actual_file_or_folder/i", paths.front());
}

TEST_F(VisitorTest, ManyFindByNameVisitFile){
    Visitor * visitor = new FindByNameVisitor("e.txt");
    test_actual_file_or_folder->accept(visitor);
    ASSERT_FALSE(dynamic_cast<FindByNameVisitor *>(visitor)->getPaths().empty());
    auto paths = dynamic_cast<FindByNameVisitor *>(visitor)->getPaths();
    ASSERT_EQ("test_actual_file_or_folder/d/e.txt", paths.front());
    paths.pop_front();
    ASSERT_EQ("test_actual_file_or_folder/e.txt", paths.front());
}

TEST_F(VisitorTest, NothingFindByNameVisitFolder){
    Visitor * visitor = new FindByNameVisitor("test_actual_file_or_folder/k");
    test_actual_file_or_folder->accept(visitor);
    ASSERT_TRUE(dynamic_cast<FindByNameVisitor *>(visitor)->getPaths().empty());
}

TEST_F(VisitorTest, NothingFindByNameVisitFile){
    Visitor * visitor = new FindByNameVisitor("test_actual_file_or_folder/k.txt");
    test_actual_file_or_folder->accept(visitor);
    ASSERT_TRUE(dynamic_cast<FindByNameVisitor *>(visitor)->getPaths().empty());
}

TEST_F(VisitorTest, StreamOutVisitFile){
    ASSERT_EQ("test_actual_file_or_folder/a.txt", a_file->path());
    Visitor * visitor = new StreamOutVisitor();
    a_file->accept(visitor);
    std::string expected_string = "_____________________________________________\ntest_actual_file_or_folder/a.txt\n---------------------------------------------\nI am file a.\n_____________________________________________\n";
    ASSERT_EQ(expected_string, dynamic_cast<StreamOutVisitor *>(visitor)->getResult());
}

TEST_F(VisitorTest, StreamOutVisitFolder){
    ASSERT_EQ("test_actual_file_or_folder", test_actual_file_or_folder->path());
    Visitor * visitor = new StreamOutVisitor();
    test_actual_file_or_folder->accept(visitor);
    std::string expected_string = "_____________________________________________\ntest_actual_file_or_folder/d/e.txt\n---------------------------------------------\nI am file e.\n_____________________________________________\n\n_____________________________________________\ntest_actual_file_or_folder/g/h.txt\n---------------------------------------------\nI am file h.\n_____________________________________________\n\n_____________________________________________\ntest_actual_file_or_folder/g/i/j.txt\n---------------------------------------------\nI am file j.\n_____________________________________________\n\n_____________________________________________\ntest_actual_file_or_folder/a.txt\n---------------------------------------------\nI am file a.\n_____________________________________________\n\n_____________________________________________\ntest_actual_file_or_folder/b.txt\n---------------------------------------------\nI am file b.\n_____________________________________________\n\n_____________________________________________\ntest_actual_file_or_folder/c.txt\n---------------------------------------------\nI am file c.\n_____________________________________________\n\n_____________________________________________\ntest_actual_file_or_folder/e.txt\n---------------------------------------------\nI am file e.\n_____________________________________________\n\n";
    ASSERT_EQ(expected_string, dynamic_cast<StreamOutVisitor *>(visitor)->getResult());
}

TEST_F(VisitorTest, StreamOutVisitNestedFolder){
    ASSERT_EQ("test_actual_file_or_folder/g/i", i_folder->path());
    Visitor * visitor = new StreamOutVisitor();
    i_folder->accept(visitor);
    std::string expected_string = "_____________________________________________\ntest_actual_file_or_folder/g/i/j.txt\n---------------------------------------------\nI am file j.\n_____________________________________________\n";
    ASSERT_EQ(expected_string, dynamic_cast<StreamOutVisitor *>(visitor)->getResult());
}
