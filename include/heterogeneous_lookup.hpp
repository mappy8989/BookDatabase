#pragma once

#include <string>
#include <string_view>

namespace bookdb {

struct TransparentStringLess {
    using is_transparent = void;

    bool operator()(const Book &b1, const Book &b2) { return b1.author < b2.author; }
    bool operator()(const Book &b1, const std::string_view &author) { return b1.author < author; }
    bool operator()(const std::string_view &author, const Book &b1) {
        return this->operator()(b1, author);
    }
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
};

}  // namespace bookdb
