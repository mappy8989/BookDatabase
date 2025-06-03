#pragma once

#include <flat_map>
#include <initializer_list>
#include <ostream>
#include <print>
#include <string>
#include <string_view>
#include <vector>

#include "book.hpp"
#include "concepts.hpp"
#include "heterogeneous_lookup.hpp"

namespace bookdb {

template <BookContainerLike BookContainer = std::vector<Book>>
class BookDatabase {
public:
    // Type aliases
    using value_type = Book;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using iterator = BookContainer::iterator;
    using const_iterator = BookContainer::const_iterator;
    using difference_type = std::ptrdiff_t;
    using size_type = std::size_t;
    // Ваш код здесь

    using AuthorContainer = std::vector<std::string>;

    BookDatabase() = default;

    BookDatabase(std::initializer_list<Book> list) {
        books_.insert(begin(), list.begin(), list.end());
    }

    void Clear() {
        books_.clear();
        authors_.clear();
    }

    // Standard container interface methods
    iterator begin() { return books_.begin(); }
    iterator end() { return books_.end(); }

    const_iterator cbegin() const { return books_.cbegin(); }
    const_iterator cend() const { return books_.cend(); }

    iterator rbegin() { return books_.rbegin(); }
    iterator rend() { return books_.rend(); }

    template <typename... Args>
    void EmplaceBack(Args &&...args) {
        auto ref = books_.emplace_back(std::forward<Args>(args)...);
        authors_.push_back(std::string(books_.back().author));
    }

    void PushBack(Book &book) {
        books_.push_back(book);
        authors_.push_back(std::string(book.author));
    }
    // Ваш код здесь

    const BookContainer &GetBooks(void) const { return books_; }
    const AuthorContainer &GetAuthors(void) const { return authors_; }

    size_type size() const { return books_.size(); }

private:
    BookContainer books_;
    AuthorContainer authors_;
};

}  // namespace bookdb

namespace std {
template <>
struct formatter<bookdb::BookDatabase<std::vector<bookdb::Book>>> {
    template <typename FormatContext>
    auto format(const bookdb::BookDatabase<std::vector<bookdb::Book>> &db,
                FormatContext &fc) const {

        format_to(fc.out(), "BookDatabase (size = {}): ", db.size());

        format_to(fc.out(), "Books:\n");
        for (const auto &book : db.GetBooks()) {
            format_to(fc.out(), "- {}\n", book);
        }

        format_to(fc.out(), "Authors:\n");
        for (const auto &author : db.GetAuthors()) {
            format_to(fc.out(), "- {}\n", author);
        }

        return fc.out();
    }

    constexpr auto parse(format_parse_context &ctx) {
        return ctx.begin();  // Просто игнорируем пользовательский формат
    }
};

template <>
struct formatter<std::flat_map<std::string_view, int>> {
    template <typename FormatContext>
    auto format(const std::flat_map<std::string_view, int> &map, FormatContext &fc) const {

        format_to(fc.out(), "Authors (size = {}): ", map.size());

        format_to(fc.out(), "Books number:\n");
        for (const auto &elem : map) {
            format_to(fc.out(), "{} - {}\n", elem.first, elem.second);
        }

        return fc.out();
    }

    constexpr auto parse(format_parse_context &ctx) {
        return ctx.begin();  // Просто игнорируем пользовательский формат
    }
};

template <>
struct formatter<std::flat_map<bookdb::Genre, double>> {
    template <typename FormatContext>
    auto format(const std::flat_map<bookdb::Genre, double> &map, FormatContext &fc) const {

        format_to(fc.out(), "Genres (size = {}): ", map.size());

        format_to(fc.out(), "Ratings:\n");
        for (const auto &elem : map) {
            format_to(fc.out(), "{} - {}\n", elem.first, elem.second);
        }

        return fc.out();
    }

    constexpr auto parse(format_parse_context &ctx) {
        return ctx.begin();  // Просто игнорируем пользовательский формат
    }
};
}  // namespace std
