
//This is refer to https://github.com/adah1972/output_container/blob/master/output_container.h 

#ifndef OUTPUT_CONTAINER_H
#define OUTPUT_CONTAINER_H

#include <ostream>      // std::ostream
#include <type_traits>  // std::false_type/true_type/decay_t/is_same_v
#include <utility>      // std::declval/pair

// Type trait to detect std::pair
template <typename T>
struct is_pair : std::false_type {};
template <typename T, typename U>
struct is_pair<std::pair<T, U>> : std::true_type {};
// template <typename T>
// bool is_pair_v = is_pair<T>::value;//need let warning disappear

//peter modify
template <typename T>
struct ISPAIRV
{
    constexpr static T  is_pair_v = is_pair<T>::value;
};

template <typename T>
constexpr T ISPAIRV<T>::is_pair_v;




// Type trait to detect whether an output function already exists
template <typename T>
struct has_output_function {
    template <class U>
    static auto output(U* ptr)
        -> decltype(::std::declval<std::ostream&>() << *ptr,
                    ::std::true_type());
    template <class U>
    static std::false_type output(...);
    static constexpr bool value =
        decltype(output<T>(nullptr))::value;
};
template <typename T>
inline constexpr bool has_output_function_v =
    has_output_function<T>::value;
/* NB: Visual Studio 2017 (or below) may have problems with
 *     has_output_function_v<T>: you should then use
 *     has_output_function<T>::value instead, or upgrade to
 *     Visual Studio 2019. */



// Output function for std::pair
template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& pr);

// Element output function for containers that define a key_type and
// have its value type as std::pair
template <typename T, typename Cont>
auto output_element(std::ostream& os, const T& element,
                    const Cont&, std::true_type)
    -> decltype(std::declval<typename Cont::key_type>(), os);
// Element output function for other containers
template <typename T, typename Cont>
auto output_element(std::ostream& os, const T& element,
                    const Cont&, ...)
    -> decltype(os);

//due to need modify decay_t
template< class T >
    using decay_tt = typename std::decay<T>::type; 
template< class T, class U >
    inline constexpr bool is_same_vv = std::is_same<T, U>::value;
template<bool _Cond, typename _Tp = void>
    using enable_if_tt = typename std::enable_if<_Cond, _Tp>::type;
template <typename T,
          typename = enable_if_tt<!has_output_function_v<T>>>
// template <typename T,
//           typename = typename std::enable_if<!has_output_function<T>::value>::type>
auto operator<<(std::ostream& os, const T& container)
    -> decltype(container.begin(), container.end(), os)
{
    //using std::decay_t;  
    //using std::is_same_v;

    using element_type = decay_tt<decltype(*container.begin())>;
    //using element_type = typename std::decay<T>::type<decltype(*container.begin())>;
    constexpr bool is_char_v = is_same_vv<element_type, char>;
    //constexpr bool is_char_v = typename std::is_same<element_type, char>::value;
    if (!is_char_v) {
        os << '{';
    }
    auto end = container.end();
    bool on_first_element = true;
    for (auto it = container.begin(); it != end; ++it) {
        if constexpr (is_char_v) {
            if (*it == '\0') {
                break;
            }
        } else {
            if (!on_first_element) {
                os << ", ";
            } else {
                os << ' ';
                on_first_element = false;
            }
        }
        output_element(os, *it, container, is_pair<element_type>());
    }
    if (!is_char_v) {
        if (!on_first_element) {  // Not empty
            os << ' ';
        }
        os << '}';
    }
    return os;
}

template <typename T, typename Cont>
auto output_element(std::ostream& os, const T& element,
                    const Cont&, std::true_type)
    -> decltype(std::declval<typename Cont::key_type>(), os)
{
    os << element.first << " => " << element.second;
    return os;
}

template <typename T, typename Cont>
auto output_element(std::ostream& os, const T& element,
                    const Cont&, ...)
    -> decltype(os)
{
    os << element;
    return os;
}

template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& pr)
{
    os << '(' << pr.first << ", " << pr.second << ')';
    return os;
}

#endif // OUTPUT_CONTAINER_H
