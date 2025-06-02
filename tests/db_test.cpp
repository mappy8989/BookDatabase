#include "book_database.hpp"
#include <gtest/gtest.h>

using namespace bookdb;

TEST(BooksDataBase, PushBackCheck) {
    Book bk(Genre::Fiction);
    BookDatabase bdb;

    bdb.PushBack(bk);
    EXPECT_EQ(bdb.GetBooks().at(0).genre, Genre::Fiction);
}

TEST(BooksDataBase, EmplaceBackCheck) {
    Book bk(Genre::Fiction);
    BookDatabase bdb;

    bdb.EmplaceBack({"NonFiction"});
    EXPECT_EQ(bdb.GetBooks().at(0).genre, Genre::NonFiction);
}

TEST(BooksDataBase, InitializerListCheck) {
    Book bk1(Genre::Fiction), bk2(Genre::NonFiction), bk3(Genre::Mystery);
    BookDatabase bdb = {bk1, bk2, bk3};
    EXPECT_EQ(bdb.GetBooks().at(2).genre, Genre::Mystery);
}
