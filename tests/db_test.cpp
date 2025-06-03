#include "book_database.hpp"
#include <gtest/gtest.h>

using namespace bookdb;

TEST(BooksDataBase, PushBackCheck) {
    Book bk("1984", "George Orwell", 1949, Genre::SciFi, 4., 190);
    BookDatabase bdb;

    bdb.PushBack(bk);
    EXPECT_EQ(bdb.GetBooks().at(0).genre, Genre::SciFi);
}

TEST(BooksDataBase, EmplaceBackCheck) {
    BookDatabase bdb;

    bdb.EmplaceBack("Lord of the Flies", "William Golding", 1954, Genre::Fiction, 4.2, 89);
    EXPECT_EQ(bdb.GetBooks().at(0).genre, Genre::Fiction);
}

TEST(BooksDataBase, InitializerListCheck) {
    Book bk1("1984", "George Orwell", 1949, Genre::SciFi, 4., 190);
    Book bk2("Animal Farm", "George Orwell", 1945, Genre::Fiction, 4.4, 143);
    Book bk3("The Great Gatsby", "F. Scott Fitzgerald", 1925, Genre::Fiction, 4.5, 120);

    BookDatabase bdb = {bk1, bk2, bk3};
    EXPECT_EQ(bdb.GetBooks().at(2).genre, Genre::Fiction);
}
