#pragma once

#include <concepts>
#include <iterator>

#include "book.hpp"

namespace bookdb {

template <typename T>
concept BookContainerLike = requires(T &t, typename T::value_type v) { t.push_back(v); } &&
                            std::same_as<typename T::value_type, bookdb::Book>;

template <typename T>
concept BookIterator = std::random_access_iterator<T> &&
                       std::same_as<typename std::iterator_traits<T>::value_type, bookdb::Book>;

template <typename S, typename I>
concept BookSentinel = requires(S s, I i) {
    { s == i } -> std::convertible_to<bool>;
    { i == s } -> std::convertible_to<bool>;
};

template <typename P, typename T>
concept BookPredicate = requires(P pred, T &&val) {
    { pred(std::forward<T>(val)) } -> std::convertible_to<bool>;
};

template <typename C, typename T>
concept BookComparator = requires(C comp, T a, T b) {
    { comp(a, b) } -> std::convertible_to<bool>;
};

}  // namespace bookdb