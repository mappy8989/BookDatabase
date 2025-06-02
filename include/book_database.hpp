#pragma once

#include <initializer_list>
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
        books_.insert(BooksBegin(), list.begin(), list.end());
    }

    void Clear() {
        books_.clear();
        authors_.clear();
    }

    // Standard container interface methods
    iterator BooksBegin() { return books_.begin(); }
    iterator BooksEnd() { return books_.end(); }

    reference EmplaceBack(Book &&book) { return books_.emplace_back(book); }
    void PushBack(Book &book) { books_.push_back(book); }
    // Ваш код здесь

    const BookContainer &GetBooks(void) { return books_; }
    const AuthorContainer &GetAuthors(void) { return authors_; }

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
        /*
        Раскомментируйте, когда bookdb::BookDatabase поддержит интерфейсы, доступные стандартным
        контейнерам (size/begin/...)

        format_to(fc.out(), "BookDatabase (size = {}): ", db.size());

        format_to(fc.out(), "Books:\n");
        for (const auto &book : db.GetBooks()) {
            format_to(fc.out(), "- {}\n", book);
        }

        format_to(fc.out(), "Authors:\n");
        for (const auto &author : db.GetAuthors()) {
            format_to(fc.out(), "- {}\n", author);
        }
        */
        return fc.out();
    }

    constexpr auto parse(format_parse_context &ctx) {
        return ctx.begin();  // Просто игнорируем пользовательский формат
    }
};
}  // namespace std
