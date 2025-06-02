#pragma once

#include <concepts>
#include <iterator>

#include "book.hpp"

namespace bookdb {

template <typename T>
concept BookContainerLike =
    requires(T &t, typename T::value_type v) { t.push_back(v); } && std::same_as<typename T::value_type, bookdb::Book>;

template <typename T>
concept BookIterator = std::random_access_iterator<T> &&  // рандом-доступный итератор
                       std::same_as<typename std::iterator_traits<T>::value_type, bookdb::Book>;

template <typename S, typename I>
concept BookSentinel = true;

template <typename P>
concept BookPredicate = true;

template <typename C>
concept BookComparator = true;

}  // namespace bookdb