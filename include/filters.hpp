#pragma once

#include <algorithm>
#include <functional>
#include <vector>

#include "book.hpp"
#include "book_database.hpp"
#include "concepts.hpp"

namespace bookdb {

constexpr auto YearBetween(int year_from, int year_to) {
    return [year_from, year_to](const Book &book) {
        return book.year >= year_from && book.year <= year_to;
    };
}

constexpr auto RatingAbove(double rating) {
    return [rating](const Book &book) { return book.rating > rating; };
}

constexpr auto GenreIs(bookdb::Genre genre) {
    return [genre](const Book &book) { return book.genre == genre; };
}

template <typename Pred>
constexpr auto all_of(Pred pred) {
    return pred;
}

// Рекурсивный случай: объединяем первый предикат с остальными
template <typename Pred, typename... Preds>
constexpr auto all_of(Pred pred, Preds... preds) {
    return [pred, rest = all_of(preds...)](const auto &x) { return pred(x) && rest(x); };
}

template <typename Pred>
constexpr auto any_of(Pred pred) {
    return pred;
}

template <typename Pred, typename... Preds>
constexpr auto any_of(Pred pred, Preds... preds) {
    return [pred, rest = all_of(preds...)](const auto &x) { return pred(x) || rest(x); };
}

template <class Iterator, class UnaryPred>
constexpr auto filterBooks(Iterator it_first, Iterator it_last, UnaryPred pred) {
    std::vector<std::reference_wrapper<const std::iter_value_t<Iterator>>> out;

    std::for_each(it_first, it_last, [&](const auto &elem) {
        if (pred(elem)) {
            out.push_back(std::cref(elem));
        }
    });

    return out;
}

}  // namespace bookdb