#ifndef CONCEPTS_H
#define CONCEPTS_H

#include <concepts>

template <typename T>
concept NumType = std::is_signed<T>::value || std::is_unsigned<T>::value || std::is_floating_point<T>::value ||
                  std::same_as<T, char> || std::same_as<T, double>;

#endif