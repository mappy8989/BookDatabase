#include <gtest/gtest.h>

#include "book_database.hpp"
#include "statsistics.hpp"

using namespace bookdb;

TEST(ProcessDB, histogramCheck) {
    BookDatabase db;
    db.EmplaceBack("Book 1", "Author 1", 1945, Genre::Fiction, 4.4, 143);
    db.EmplaceBack("Book 2", "Author 1", 1925, Genre::Fiction, 4.5, 120);
    db.EmplaceBack("Book 1", "Author 2", 1960, Genre::Fiction, 4.8, 156);

    auto histogram = buildAuthorHistogramFlat(db);

    EXPECT_EQ(histogram.size(), 2);
    EXPECT_EQ(histogram["Author 1"], 2);
    EXPECT_EQ(histogram["Author 2"], 1);
}

TEST(ProcessDB, GenreRatingCheck) {
    BookDatabase db;
    db.EmplaceBack("Book 1", "Author 1", 1945, Genre::Fiction, 4.4, 143);
    db.EmplaceBack("Book 2", "Author 2", 1925, Genre::Fiction, 4.5, 120);
    db.EmplaceBack("Book 3", "Author 3", 1960, Genre::Fiction, 4.6, 156);

    auto histogram = calculateGenreRatings(db);

    EXPECT_EQ(histogram.size(), 1);
    EXPECT_EQ(histogram[Genre::Fiction], 4.5);
    EXPECT_EQ(histogram[Genre::SciFi], 0.0);
}

TEST(ProcessDB, TopNByCheck) {
    BookDatabase db;
    db.EmplaceBack("Animal Farm", "George Orwell", 1945, Genre::Fiction, 4.4, 143);
    db.EmplaceBack("The Great Gatsby", "F. Scott Fitzgerald", 1925, Genre::Fiction, 4.5, 120);
    db.EmplaceBack("To Kill a Mockingbird", "Harper Lee", 1960, Genre::Fiction, 4.8, 156);
    db.EmplaceBack("Pride and Prejudice", "Jane Austen", 1813, Genre::Fiction, 4.7, 178);
    db.EmplaceBack("The Catcher in the Rye", "J.D. Salinger", 1951, Genre::Fiction, 4.3, 112);
    db.EmplaceBack("Brave New World", "Aldous Huxley", 1932, Genre::SciFi, 4.5, 98);
    db.EmplaceBack("Jane Eyre", "Charlotte Brontë", 1847, Genre::Fiction, 4.6, 110);
    db.EmplaceBack("The Hobbit", "J.R.R. Tolkien", 1937, Genre::Fiction, 4.9, 203);
    db.EmplaceBack("Lord of the Flies", "William Golding", 1954, Genre::Fiction, 4.2, 89);

    auto histogram = getTopNBy(db, 3, comp::LessByPopularity{});

    EXPECT_EQ(histogram.size(), 3);
    EXPECT_EQ(histogram.at(0).get().rating, 4.7);
    EXPECT_EQ(histogram.at(1).get().rating, 4.8);
    EXPECT_EQ(histogram.at(2).get().rating, 4.9);
}