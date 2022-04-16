#ifndef STACK_HPP
#define STACK_HPP
#include "vector.hpp"

namespace ft{

template<class T, class Container = ft::vector<T> >
	class stack{

	public:
	typedef T value_type;
	typedef Container container_type;
	typedef typename Container::size_type size_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;

	protected:
		container_type c;
	
	public:	
	
	explicit stack (const container_type& cont = container_type()) : c(cont){}
	
	stack(const stack& other): c(other.c) {}

	stack& operator=(const stack& other){
		c = other.c;
		return (*this);
	}

	bool empty() const{
		return (c.empty());
	}

	size_type size() const{
		return (c.size());
	}

	value_type& top(){
		return (c.back());
	}

	const value_type& top() const{
		return (c.back());
	}

	void push (const value_type& val){
		c.push_back(val);
	}

	void pop(){
		c.pop_back();
	}



	template <class A, class Cont>
		  friend bool operator== (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs){
				return(lhs.c == rhs.c);
			 }
	template <class A, class Cont>
		  friend bool operator!= (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs){
				return(lhs.c != rhs.c);
			 }
	template <class A, class Cont>
		  friend bool operator<  (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs){
				return(lhs.c < rhs.c);
			 }
	template <class A, class Cont>
		  friend bool operator<= (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs){
				return(lhs.c <= rhs.c);
		  }
	template <class A, class Cont>
		  friend bool operator>  (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs){
				return(lhs.c > rhs.c);
		  }
	template <class A, class Cont>
		  friend bool operator>= (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs){
				return(lhs.c >= rhs.c);
			}

};



}
#endif