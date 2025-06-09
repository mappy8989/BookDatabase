#pragma once

#include <algorithm>
#include <flat_map>
#include <iostream>
#include <iterator>
#include <optional>
#include <random>
#include <stdexcept>
#include <string_view>

#include "book_database.hpp"
#include "comparators.hpp"

namespace bookdb {

class GenreStats {
public:
    void Add(double rating) {
        total_rating += rating;
        count++;
    }
    double Average() const {
        if (!count) {
            return 0.0;
        }
        return total_rating / count;
    };
    void Reset() {
        total_rating = 0.0;
        count = 0;
    };

private:
    double total_rating = 0.0;
    size_t count = 0;
};

template <BookContainerLike T>
auto buildAuthorHistogramFlat(const BookDatabase<T> &cont) {
    std::flat_map<std::string, int> histogram;
    for (const Book &book : cont.GetBooks()) {
        histogram[std::string(book.author)]++;
    }

    return histogram;
}

template <BookContainerLike T>
auto calculateGenreRatings(const BookDatabase<T> &cont) {
    std::flat_map<Genre, GenreStats> histogram;
    std::flat_map<Genre, double> average_rating;
    for (const Book &book : cont.GetBooks()) {
        histogram.try_emplace(book.genre).first->second.Add(book.rating);
    }

    for (const auto &entry : histogram) {
        Genre genre = entry.first;
        const auto &stats = entry.second;
        average_rating[genre] = stats.Average();
    }

    return average_rating;
}

template <BookContainerLike T>
auto calculateAverageRating(const BookDatabase<T> &cont) {

    double sum = std::transform_reduce(cont.cbegin(), cont.cend(), 0.0, std::plus<>(),
                                       [](const Book &book) { return book.rating; });

    return (sum / std::distance(cont.cbegin(), cont.cend()));
}

template <BookContainerLike T>
std::optional<std::vector<std::reference_wrapper<const Book>>>
sampleRandomBooks(const BookDatabase<T> &cont, int n) {
    if (n <= 0 || n > cont.size()) {
        std::cerr << "Incorrect element size n = " << n << std::endl;
        return std::nullopt;
    }

    std::vector<std::reference_wrapper<const Book>> out;
    out.reserve(n);
    std::sample(cont.BooksBegin(), cont.BooksEnd(), std::back_inserter(out), n);

    return out;
}

template <BookContainerLike T, typename Comparator = bookdb::comp::LessByPopularity>
std::vector<std::reference_wrapper<const Book>> getTopNBy(BookDatabase<T> &cont, int n,
                                                          Comparator comp) {
    if (n <= 0 || n > (int)cont.size()) {
        std::cerr << "Incorrect element size n = " << n << std::endl;
        return {};
    }

    std::vector<std::reference_wrapper<const Book>> out;
    out.reserve(n);
    std::nth_element(cont.begin(), cont.end() - n, cont.end(), comp);
    std::sort(cont.end() - n, cont.end(), comp);

    out.insert(out.end(), std::prev(cont.end(), n), cont.end());

    return out;
}
}  // namespace bookdb
