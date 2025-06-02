#pragma once

#include "book.hpp"

namespace bookdb::comp {

struct LessByAuthor {
    bool operator()(const Book &b1, const Book &b2) { return (b1.author < b2.author); }
};

struct LessByYear {
    bool operator()(const Book &b1, const Book &b2) { return (b1.year < b2.year); }
};

struct LessByRating {
    bool operator()(const Book &b1, const Book &b2) { return (b1.rating < b2.rating); }
};

}  // namespace bookdb::comp