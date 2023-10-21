#pragma once 

#include <string>
#include "../src/folder.h"

using namespace std;

TEST(Folder, normal) {
    Folder * test_actual_file_or_folder = Folder::create("test_actual_file_or_folder");

    ASSERT_EQ("test_actual_file_or_folder", test_actual_file_or_folder->name());
    ASSERT_EQ("test_actual_file_or_folder", test_actual_file_or_folder->path());
}

TEST(Folder, NotFolder){
    ASSERT_ANY_THROW(Folder::create("test_actual_file_or_folder/a.txt"));
}

TEST(Folder, NotExistFolder){
    ASSERT_ANY_THROW(Folder::create("test_actual_file_or_folder/k"));
}

TEST(Folder, add_file) {
    Folder * test_actual_file_or_folder = Folder::create("test_actual_file_or_folder");
    File * a_file = File::create("test_actual_file_or_folder/a.txt");
    test_actual_file_or_folder->add(a_file);

    ASSERT_EQ("a.txt", test_actual_file_or_folder->getChildByName("a.txt")->name());
}

TEST(Folder, add_incorrect_path_file_to_folder) {
    Folder * test_actual_file_or_folder = Folder::create("test_actual_file_or_folder");
    File * ut_file = File::create("test/ut_file.h");
    ASSERT_ANY_THROW(test_actual_file_or_folder->add(ut_file));
}

TEST(Folder, add_folder) {
    Folder * test_actual_file_or_folder = Folder::create("test_actual_file_or_folder");
    Folder * d_folder = Folder::create("test_actual_file_or_folder/d");
    test_actual_file_or_folder->add(d_folder);

    ASSERT_EQ("d", test_actual_file_or_folder->getChildByName("d")->name());
}