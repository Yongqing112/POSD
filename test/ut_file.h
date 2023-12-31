#pragma once 

#include "../src/file.h"

TEST(File, normal) {
    File * hello = File::create("test_actual_file_or_folder/a.txt");
    ASSERT_EQ("a.txt", hello->name());
    ASSERT_EQ("test_actual_file_or_folder/a.txt", hello->path());
}

TEST(File, NotFile){
    ASSERT_ANY_THROW(File::create("test_actual_file_or_folder/d"));
}

TEST(File, NotExistFile){
    ASSERT_ANY_THROW(File::create("test_actual_file_or_folder/k.txt"));
}