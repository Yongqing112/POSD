#pragma once
#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"
#include "../src/visitor.h"
#include "../src/find_by_name_visitor.h"
#include "../src/stream_out_visitor.h"
#include <iostream>


class VisitorTest: public ::testing::Test {
protected:
    void SetUp() {
        // home = new Folder("/Users/user/home");

        // profile = new File("/Users/user/home/my_profile");
        // home->add(profile);

        // download = new Folder("/Users/user/home/Downloads");
        // home->add(download);

        // document = new Folder("/Users/user/home/Documents");
        // home->add(document);

        // note = new File("/Users/user/home/Documents/note.txt");
        // document->add(note);

        // favorite = new Folder("/Users/user/home/Documents/favorites");
        // document->add(favorite);
        // ddd = new File("/Users/user/home/Documents/favorites/domain-driven-design.pdf");
        // favorite->add(ddd);
        // ca = new File("/Users/user/home/Documents/favorites/clean-architecture.pdf");
        // favorite->add(ca);
        // cqrs = new File("/Users/user/home/Documents/favorites/cqrs.pdf");
        // favorite->add(cqrs);
    }

    void TearDown() {
        // delete home;
        // delete profile;
        // delete download;
        // delete document;
        // delete note;
        // delete favorite;
        // delete ddd;
        // delete ca;
        // delete cqrs;
    }
    
    // Node * home;
    // Node * profile;
    // Node * download;
    // Node * document;
    // Node * note;
    // Node * favorite;
    // Node * ddd;
    // Node * ca;
    // Node * cqrs;
};

TEST_F(VisitorTest, lstatFolder){
    Folder folder = Folder::create("test");
    ASSERT_EQ("test", folder.path());
}

TEST_F(VisitorTest, lstatFile){
    File file = File::create("test/a.txt");
    ASSERT_EQ("test/a.txt", file.path());
    Visitor * visitor = new StreamOutVisitor();
    file.accept(visitor);
    cout << dynamic_cast<StreamOutVisitor *>(visitor)->getResult() << endl;
}

// TEST_F(VisitorTest, FindByNameVisitFolder){
//     Visitor * visitor = new FindByNameVisitor("favorites");
//     home->accept(visitor);
//     ASSERT_FALSE(dynamic_cast<FindByNameVisitor *>(visitor)->getPaths().empty());
//     ASSERT_EQ("/Users/user/home/Documents/favorites", dynamic_cast<FindByNameVisitor *>(visitor)->getPaths().front());
// }

// TEST_F(VisitorTest, FindByNameVisitFile){
//     Visitor * visitor = new FindByNameVisitor("note.txt");
//     home->accept(visitor);
//     ASSERT_FALSE(dynamic_cast<FindByNameVisitor *>(visitor)->getPaths().empty());
//     ASSERT_EQ("/Users/user/home/Documents/note.txt", dynamic_cast<FindByNameVisitor *>(visitor)->getPaths().front());
// }

// TEST_F(VisitorTest, StreamOutVisitFolder){
//     Visitor * visitor = new StreamOutVisitor();
//     home->accept(visitor);
//     // ASSERT_FALSE(dynamic_cast<FindByNameVisitor *>(visitor)->getPaths().empty());
//     // ASSERT_EQ("/Users/user/home/Documents/favorites", dynamic_cast<FindByNameVisitor *>(visitor)->getPaths().front());
// }

// TEST_F(VisitorTest, StreamOutVisitFile){
//     Visitor * visitor = new StreamOutVisitor();
//     note->accept(visitor);
//     // ASSERT_FALSE(dynamic_cast<FindByNameVisitor *>(visitor)->getPaths().empty());
//     // ASSERT_EQ("/Users/user/home/Documents/favorites", dynamic_cast<FindByNameVisitor *>(visitor)->getPaths().front());
// }