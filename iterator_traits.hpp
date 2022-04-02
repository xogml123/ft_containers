#ifndef ITERATOR_HPP
# define ITERATOR_HPP

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
                //return *current;
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


}

#endif
