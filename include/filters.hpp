#pragma once

#include <algorithm>
#include <functional>
#include <vector>

#include "book.hpp"
#include "book_database.hpp"
#include "concepts.hpp"

namespace bookdb {

auto YearBetween(int year_from, int year_to) {
    return [year_from, year_to](const Book &book) {
        return book.year >= year_from && book.year <= year_to;
    };
}

auto RatingAbove(double rating) {
    return [rating](const Book &book) { return book.rating > rating; };
}

auto GenreIs(bookdb::Genre genre) {
    return [genre](const Book &book) { return book.genre == genre; };
}

template <typename Pred>
auto all_of(Pred pred) {
    return pred;
}

// Рекурсивный случай: объединяем первый предикат с остальными
template <typename Pred, typename... Preds>
auto all_of(Pred pred, Preds... preds) {
    return [pred, rest = all_of(preds...)](const auto &x) { return pred(x) && rest(x); };
}

template <typename Pred>
auto any_of(Pred pred) {
    return pred;
}

template <typename Pred, typename... Preds>
auto any_of(Pred pred, Preds... preds) {
    return [pred, rest = all_of(preds...)](const auto &x) { return pred(x) || rest(x); };
}

template <class Iterator, class UnaryPred>
auto filterBooks(Iterator it_first, Iterator it_last, UnaryPred pred) {
    using RefType = typename std::iterator_traits<Iterator>::reference;
    std::vector<std::reference_wrapper<std::remove_reference_t<RefType>>> out;

    for (; it_first != it_last; it_first++) {
        if (pred(*it_first)) {
            out.push_back(*it_first);
        }
    }

    return out;
}

}  // namespace bookdb