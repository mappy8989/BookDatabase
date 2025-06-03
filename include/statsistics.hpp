#pragma once

#include <algorithm>
#include <flat_map>
#include <iterator>
#include <optional>
#include <random>
#include <stdexcept>
#include <string_view>

#include "book_database.hpp"

#include <print>

namespace bookdb {

template <BookContainerLike T, typename Comparator = TransparentStringLess>
auto buildAuthorHistogramFlat(const BookDatabase<T> &cont, Comparator comp = {}) {
    std::flat_map<std::string_view, int> histogram;
    for (Book book : cont.GetBooks()) {
        histogram[book.author]++;
    }

    return histogram;
}

template <BookContainerLike T>
auto calculateGenreRatings(const BookDatabase<T> &cont) {
    std::flat_map<Genre, std::pair<int, double>>
        histogram;  // std::pair first - number of elements, second - rating sum
    std::flat_map<Genre, double> average_rating;
    for (Book book : cont.GetBooks()) {
        histogram[book.genre].first++;
        histogram[book.genre].second += book.rating;
    }

    for (const auto &entry : histogram) {
        Genre genre = entry.first;
        const auto &stats = entry.second;
        average_rating[genre] = stats.second / stats.first;
    }

    return average_rating;
}

template <BookContainerLike T>
auto calculateAverageRating(const BookDatabase<T> &cont) {

    double sum = std::accumulate(cont.begin(), cont.end(), 0.0,
                                 [](double acc, const Book &book) { return acc += book.rating; });

    return (sum / std::distance(cont.begin(), cont.end()));
}

template <BookContainerLike T>
std::optional<std::vector<std::reference_wrapper<const Book>>>
sampleRandomBooks(const BookDatabase<T> &cont, int n) {
    if (n <= 0 || n > cont.size()) {
        std::println("incorrect element size n = {}", n);
        return std::nullopt;
    }

    std::vector<std::reference_wrapper<const Book>> out;
    out.reserve(n);
    std::sample(cont.BooksBegin(), cont.BooksEnd(), std::back_inserter(out), n);

    return out;
}

template <BookContainerLike T, typename Comparator = TransparentStringLess>
std::optional<std::vector<std::reference_wrapper<const Book>>> getTopNBy(BookDatabase<T> &cont,
                                                                         int n) {
    if (n <= 0 || n > cont.size()) {
        std::println("incorrect element size n = {}", n);
        return std::nullopt;
    }

    Comparator comp;
    std::vector<std::reference_wrapper<const Book>> out;
    out.reserve(n);
    std::sort(cont.begin(), cont.end(), comp);

    out.insert(out.end(), cont.rbegin(), std::next(cont.rbegin(), n));

    return out;
}
}  // namespace bookdb
