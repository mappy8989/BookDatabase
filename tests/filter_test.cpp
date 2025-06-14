#include "book_database.hpp"
#include "filters.hpp"
#include <gtest/gtest.h>

using namespace bookdb;

template <typename DB>
void fill_db(DB &db) {
    db.EmplaceBack("Animal Farm", "George Orwell", 1945, Genre::Fiction, 4.4, 143);
    db.EmplaceBack("The Great Gatsby", "F. Scott Fitzgerald", 1925, Genre::Fiction, 4.5, 120);
    db.EmplaceBack("To Kill a Mockingbird", "Harper Lee", 1960, Genre::Fiction, 4.8, 156);
    db.EmplaceBack("Pride and Prejudice", "Jane Austen", 1813, Genre::Fiction, 4.7, 178);
    db.EmplaceBack("The Catcher in the Rye", "J.D. Salinger", 1951, Genre::Fiction, 4.3, 112);
    db.EmplaceBack("Brave New World", "Aldous Huxley", 1932, Genre::SciFi, 4.5, 98);
    db.EmplaceBack("Jane Eyre", "Charlotte Brontë", 1847, Genre::Fiction, 4.6, 110);
    db.EmplaceBack("The Hobbit", "J.R.R. Tolkien", 1937, Genre::Fiction, 4.9, 203);
    db.EmplaceBack("Lord of the Flies", "William Golding", 1954, Genre::Fiction, 4.2, 89);
}

TEST(FilterDB, allOfCheck) {
    BookDatabase bdb;
    fill_db(bdb);

    auto res = bookdb::filterBooks(bdb.GetBooks().begin(), bdb.GetBooks().end(),
                                   all_of(YearBetween(1954, 1961)));

    EXPECT_EQ(res.size(), 2);
    EXPECT_EQ(res.at(0).get().author, "Harper Lee");
    EXPECT_EQ(res.at(1).get().author, "William Golding");
}

TEST(FilterDB, anyOfCheck) {
    BookDatabase bdb;
    fill_db(bdb);

    auto res = bookdb::filterBooks(bdb.GetBooks().begin(), bdb.GetBooks().end(),
                                   any_of(RatingAbove(4.89), GenreIs(Genre::SciFi)));

    EXPECT_EQ(res.size(), 2);
    EXPECT_EQ(res.at(0).get().title, "Brave New World");
    EXPECT_EQ(res.at(1).get().title, "The Hobbit");
}

TEST(FilterDB, emptyDBcheck) {
    BookDatabase bdb;

    auto res =
        bookdb::filterBooks(bdb.GetBooks().begin(), bdb.GetBooks().end(), any_of(RatingAbove(1.0)));

    EXPECT_EQ(res.size(), 0);
}