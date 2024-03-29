#ifndef MAP_ITERATOR
#define MAP_ITERATOR

#include "iterator.hpp"
#include "type_traits.hpp"
#include <iostream>

namespace ft
{
    template<class T, class N, bool isConst>
    class map_iterator
    {
        public:

        typedef std::ptrdiff_t difference_type;
		typedef typename ft::is_const<isConst, T, const T>::value value_type;
		typedef typename ft::is_const<isConst, N, const N>::value node_type;
		typedef value_type* pointer;
		typedef value_type& reference;
        typedef node_type*  node_pointer;
		typedef bidirectional_iterator_tag iterator_category;

        private:

        node_pointer _ptr;

        void successor(void)
        {
            
            if (_ptr->right->is_nil() == false)
            {
                _ptr = _ptr->right;
                while (_ptr->left->is_nil() == false) {
                    _ptr = _ptr->left;
                }
            }
            else
            {
				while (_ptr == _ptr->parent->right && _ptr->is_nil() == false) {
                    _ptr = _ptr->parent;
                }
				_ptr = _ptr->parent;
            }
        }

        void predecessor(void)
        {

            if (_ptr->is_nil())
            {
                _ptr = _ptr->right;
                while (_ptr->right->is_nil() == false)
                    _ptr = _ptr->right;

            }
            else if (_ptr->left->is_nil() == false)
            {
                _ptr = _ptr->left;
                while (_ptr->right->is_nil() == false)
                    _ptr = _ptr->right;
            }
            else
            {
                while (_ptr == _ptr->parent->left && _ptr->is_nil() == false)
                    _ptr = _ptr->parent;
                _ptr = _ptr->parent;
            }
        }

        public:

        map_iterator(void) : _ptr(NULL)
        { }

        map_iterator(node_pointer ptr) : _ptr(ptr)
        { }

        template<bool B>
		map_iterator(map_iterator<T, N, B> const &src, typename ft::enable_if<B>::type* = 0)
		{
			this->_ptr = src.base();
		}

        map_iterator &
        operator=(map_iterator const &src)
        {
            this->_ptr = src._ptr;
            return *this;
        }

        template<bool B>
		bool
		operator==(map_iterator<T, N, B> const &src) const
		{
			return this->_ptr == src.base();
		}

		template<bool B>
		bool
		operator!=(map_iterator<T, N, B> const &src) const
		{
			return !(this->_ptr == src.base());
		}

        node_pointer
        base(void) const
        {
            return this->_ptr;
        }

        reference
        operator*(void) const
        {
            return this->_ptr->item;
        }

        pointer
        operator->(void) const
        {
            return &(this->_ptr->item);
        }

        map_iterator &
        operator++(void)
        {
            successor();
            return *this;
        }

        map_iterator
        operator++(int)
        {
            map_iterator<T, N, isConst> tmp(*this);
            operator++();
            return tmp;
        }

        map_iterator &
        operator--(void)
        {
            predecessor();
            return *this;
        }

        map_iterator
        operator--(int)
        {
            map_iterator<T, N, isConst> tmp(*this);
            operator--();
            return tmp;
        }
    };
}

#endif