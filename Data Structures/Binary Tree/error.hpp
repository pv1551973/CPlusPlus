#ifndef ERROR_HPP
#define ERROR_HPP
#include<type_traits>

enum class error_code{BAD_NODE_POS};

//function template to
//convert an enumeration
//class type to its corresponding
//integral type for the sake of
//printing

template <typename Enumeration>
auto as_integer(Enumeration const value)->typename std::underlying_type<Enumeration>::type{

    return static_cast<typename std::underlying_type<Enumeration>::type>(value);

}

#endif
