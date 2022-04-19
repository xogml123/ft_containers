#ifndef STACK
#define STACK

#include "vector.hpp"
#include <list>
#include <deque>
#include <vector>

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
	public:
		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;

		explicit stack (const container_type& ctnr = container_type()) : c(ctnr)
		{}

		bool empty() const
		{
			return this->c.empty();
		}

		size_type size() const
		{
			return this->c.size();
		}

		value_type& top()
		{
			return this->c.back();
		}

		const value_type& top() const
		{
			return this->c.back();
		}

		void push(const value_type& val)
		{
			this->c.push_back(val);
		}

		void pop()
		{
			this->c.pop_back();
		}

		friend bool
		operator==(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
		{
			return lhs.c == rhs.c;
		}

		friend bool
		operator!=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
		{
			return !(lhs.c == rhs.c);
		}

		friend bool
		operator<(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
		{
			return lhs.c < rhs.c;
		}

		friend bool
		operator<=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
		{
			return !(rhs.c < lhs.c);
		}

		friend bool
		operator>(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
		{
			return (rhs.c < lhs.c);
		}

		friend bool
		operator>=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
		{
			return !(lhs.c < rhs.c);
		}

	protected:

		container_type c;
	};
}

#endif