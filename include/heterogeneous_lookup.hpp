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

struct TransparentStringHash {
    using is_transparent = void;  // Marks this as transparent for heterogeneous lookup

    // Hash for std::string
    std::size_t operator()(const std::string &s) const noexcept {
        return std::hash<std::string>{}(s);
    }

    // Hash for std::string_view
    std::size_t operator()(std::string_view sv) const noexcept {
        return std::hash<std::string_view>{}(sv);
    }

    // Hash for C-style string
    std::size_t operator()(const char *s) const noexcept {
        return std::hash<std::string_view>{}(s);
    }
};

}  // namespace bookdb
