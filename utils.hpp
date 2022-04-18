#ifndef UTILS_HPP
# define UTILS_HPP



namespace ft{

	template <class Iterator>
    class iterator_traits{
        public :
        typedef typename Iterator::difference_type difference_type;
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
    };

    template <class T>
    class iterator_traits<T *>{
        public :
        typedef std::ptrdiff_t difference_type;
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
        typedef std::random_access_iterator_tag iterator_category;
    };

    template <class T>
    class iterator_traits<const T *>{
        public :
        typedef std::ptrdiff_t difference_type;
        typedef T value_type;
        typedef const T* pointer;
        typedef const T& reference;
        typedef std::random_access_iterator_tag iterator_category;
    };

	template <class Iterator>
	class reverse_iterator
	{
		public :
			typedef Iterator iterator_type;
			typedef typename iterator_traits<Iterator>::difference_type difference_type;
			typedef typename iterator_traits<Iterator>::value_type value_type;
			typedef typename iterator_traits<Iterator>::pointer pointer;
			typedef typename iterator_traits<Iterator>::reference reference;
			typedef typename iterator_traits<Iterator>::iterator_category iterator_category;

			reverse_iterator() : current(){};
			explicit reverse_iterator(iterator_type it) : current(it){};
			template <class Iter>
			reverse_iterator(const reverse_iterator<Iter> &rev_it) : current(rev_it.base()){};
			iterator_type base() const {return current;}

            template<class U>
            reverse_iterator &operator=(const reverse_iterator<U> &rit)
            {
                current = rit.base();
                return (*this);
            }
			reverse_iterator operator+(difference_type n) const {return reverse_iterator(current - n);};
			reverse_iterator &operator++() {--current; return *this;};
			reverse_iterator operator++(int) {
                reverse_iterator tmp(current);
                --current;
                return (tmp);
            };
            reverse_iterator &operator+=(difference_type n){
                current -= n;
                return (*this);
            };
			reverse_iterator operator-(difference_type n) const {return reverse_iterator(current + n);};
			reverse_iterator &operator--(){++current; return *this;};
			reverse_iterator operator--(int) {
                reverse_iterator tmp(current);
                ++current;
                return (tmp);
            };
			reverse_iterator &operator-=(difference_type n){
                current += n;
                return (*this);
            };
            reference operator*() const {
                iterator_type tmp(current);
                tmp--;
                return *tmp;
            };
            pointer operator->() const
            {
			    return &(operator*());
            };
            reference operator[](difference_type n) const
            {
                return (*(*this + n));
            };

        private :
			iterator_type current;
	};
    template <class Iterator>
    bool operator==(const reverse_iterator<Iterator> &lhs,
                    const reverse_iterator<Iterator> &rhs)
    {
        return (lhs.base() == rhs.base());
    };
    template <class Iterator>
    bool operator!=(const reverse_iterator<Iterator> &lhs,
                    const reverse_iterator<Iterator> &rhs)
    {
        return (lhs.base() != rhs.base());
    };
    template <class Iterator>
	bool operator<(const reverse_iterator<Iterator> &lhs,
				   const reverse_iterator<Iterator> &rhs)
    {
        return (lhs.base() > rhs.base());
    };
	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
    {
        return (lhs.base() >= rhs.base());
    };
	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator> &lhs,
				   const reverse_iterator<Iterator> &rhs)
    {
        return (lhs.base() < rhs.base());
    };
	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
    {
        return (lhs.base() <= rhs.base());
    };

	template <class Iterator>
	reverse_iterator<Iterator> operator+(
		typename reverse_iterator<Iterator>::difference_type n,
		const reverse_iterator<Iterator> &rev_it){
            			return (rev_it + n);
    };

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(
		const reverse_iterator<Iterator> &lhs,
		const reverse_iterator<Iterator> &rhs){
            			return (rhs.base() - lhs.base());
    };


	//pair
	template <typename T1, typename T2>
	struct Pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		T1 first;
		T2 second;

		Pair() : first(), second()
		{
		}

		~Pair()
		{
		}

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