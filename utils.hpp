#ifndef UTILS_HPP
# define UTILS_HPP



namespace ft{

	//pair
	template <typename T1, typename T2>
	struct Pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		T1 first;
		T2 second;

		Pair() : first(), second(
		{
		}

		~Pair()
		{
		};

		Pair(const T1 &x, const T2 &y) : first(x), second(y)
		{
		}

		template <typename U1, typename U2>
		Pair(const Pair<U1, U2> &c) : first(c.first), second(c.second)
		{
		}

		Pair(const Pair<T1, T2> &c) : first(c.first), second(c.second)
		{
		}

		template <typename U1, typename U2>
		Pair<T1, T2> &operator=(const Pair<U1, U2> &c)
		{
			first = c.first;
			second = c.second;
			return *this;
		}

		Pair<T1, T2> &operator=(const Pair<T1, T2> &c)
		{
			first = c.first;
			second = c.second;
			return *this;
		}
	};

	//make_pair
	template <typename T1, typename T2>
	Pair<T1, T2> make_pair(T1 t, T2 u)
	{
		return Pair<T1, T2>(t, u);
	}

	template <typename T1, typename T2>
	bool operator==(const Pair<T1, T2> &lhs, const Pair<T1, T2> &rhs)
	{
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template <typename T1, typename T2>
	bool operator<(const Pair<T1, T2> &lhs, const Pair<T1, T2> &rhs)
	{
		return lhs.first < rhs.first && lhs.second < rhs.second;
	}

	template <typename T1, typename T2>
	bool operator!=(const Pair<T1, T2> &lhs, const Pair<T1, T2> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T1, typename T2>
	bool operator<=(const Pair<T1, T2> &lhs, const Pair<T1, T2> &rhs)
	{
		return !(lhs > rhs);
	}

	template <typename T1, typename T2>
	bool operator>(const Pair<T1, T2> &lhs, const Pair<T1, T2> &rhs)
	{
		return rhs < lhs;
	}

	template <typename T1, typename T2>
	bool operator>=(const Pair<T1, T2> &lhs, const Pair<T1, T2> &rhs)
	{
		return !(lhs < rhs);
	}


	template<bool B, class T = void>
    struct enable_if {};

    template<class T>
    struct enable_if<true, T> { typedef T type; };
    
    template <class T, T v>
    struct integral_constant
    {
        static const T value = v;
    };

	template <class T> struct is_integral : public ft::integral_constant<bool, false>{};
    //아무것도 해당하지 않으면 false 하게 만들어놓고 타입 있는것들은 true로 만들기
    template <> struct is_integral<bool> : public ft::integral_constant<bool, true>{};
    template <> struct is_integral<char> : public ft::integral_constant<bool, true>{};
    template <> struct is_integral<wchar_t> : public ft::integral_constant<bool, true>{};
    template <> struct is_integral<signed char> : public ft::integral_constant<bool, true>{};
    template <> struct is_integral<short int> : public ft::integral_constant<bool, true>{};
    template <> struct is_integral<int> : public ft::integral_constant<bool, true>{};
    template <> struct is_integral<long int> : public ft::integral_constant<bool, true>{};
    template <> struct is_integral<long long int> : public ft::integral_constant<bool, true>{};
    template <> struct is_integral<unsigned char> : public ft::integral_constant<bool, true>{};
    template <> struct is_integral<unsigned short int> : public ft::integral_constant<bool, true>{};
    template <> struct is_integral<unsigned int> : public ft::integral_constant<bool, true>{};
    template <> struct is_integral<unsigned long int> : public ft::integral_constant<bool, true>{};
    template <> struct is_integral<unsigned long long int> : public ft::integral_constant<bool, true>{};


	template <class InputIterator1, class InputIterator2>
    bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2){
        while (first1 != last1)
        {
            if (!(*first1 == *first2))
                return false;
            ++first1;
            ++first2;
        }
        return true;
    };

    template <class InputIterator1, class InputIterator2, class BinaryPredicate>
    bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred){
        while (first1 != last1)
        {
            if (!pred(*first1, *first2))
                return false;
            ++first1;
            ++first2;
        }
        return true;
    };

	template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                                 InputIterator2 first2, InputIterator2 last2)
    {
        while (first1 != last1)
        {
            if (*first1 < *first2)
                return true;
            else if (first2 == last2 || *first1 > *first2)
                return false;
            ++first1;
            ++first2;
        }
        return (first2 != last2);
    };

    template <class InputIterator1, class InputIterator2, class Compare>
    bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                                 InputIterator2 first2, InputIterator2 last2,
                                 Compare comp){
        while (first1 != last1)
        {
            if (comp(*first1, *first2))
                return true;
            else if (first2 == last2 || comp(*first2, *first1))
                return false;
            ++first1;
            ++first2;
        }
        return (first2 != last2);
    };

	template<class T> struct remove_const { typedef T type; };

	template<class T> struct remove_const <const T> { typedef T type; };
}


#endif