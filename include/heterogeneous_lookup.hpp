#pragma once

#include <string>
#include <string_view>

namespace bookdb {

struct TransparentStringLess {
    using is_transparent = void;

    bool operator()(const Book &b1, const Book &b2) { return b1.rating < b2.rating; }
    bool operator()(const Book &b1, const double &rating) { return b1.rating < rating; }
    bool operator()(const double &rating, const Book &b1) { return this->operator()(b1, rating); }
};

struct TransparentStringEqual {
    using is_transparent = void;

    bool operator()(const Book &b1, const Book &b2) {
        return b1.author == b2.author && b1.title == b2.title && b1.year == b2.year;
    }
    bool operator()(const Book &b1, const std::string &title) { return b1.title == title; }
    bool operator()(const std::string &title, const Book &b1) {
        return this->operator()(b1, title);
    }
};

struct TransparentStringHash {};

}  // namespace bookdb
