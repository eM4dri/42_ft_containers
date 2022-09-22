/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 09:47:33 by emadriga          #+#    #+#             */
/*   Updated: 2022/09/22 16:12:43 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

// #include "iterator.hpp"
// #include "random_access_iterator.hpp"
// #include "reverse_iterator.hpp"
// #include "enable_if.hpp"
// #include "is_integral.hpp"
// #include "lexicographical_compare.hpp"
#include "vector.hpp"

namespace ft
{

	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef	Container								container_type;
			typedef typename Container::value_type			value_type;
			typedef typename Container::size_type			size_type;
			typedef typename Container::reference  			reference;
			typedef typename Container::const_reference		const_reference;

		protected:
			container_type	m_Container;

		public:
	///*	Contructors & destructors
		explicit stack (const container_type& ctnr = container_type())
			:	m_Container(ctnr)	{}

		stack( const stack& copy )
			{	operator=(copy);	}

		~stack(){}

		stack& operator=( const stack& assign )
		{
			if (*this != assign)
				m_Container(assign.m_Container);
			return *this;
		}

	///*	Element access
		reference top()	{	return m_Container.back();	}
		const_reference top() const	{	return m_Container.back();	}

	///*	Capacity
		bool empty() const	{	return m_Container.empty();	}
		size_type size() const	{	return m_Container.size();	}

	///*	Modifiers
		void push( const value_type& value )	{	m_Container.push_back(value);	}
		void pop()	{	m_Container.pop_back();	}

		private:
			template <class U, class Cntr>
			friend bool operator==(const stack<U, Cntr>& a, const stack<U, Cntr>& b);

			template <class U, class Cntr>
			friend bool operator!=(const stack<U, Cntr>& a, const stack<U, Cntr>& b);

			template <class U, class Cntr>
			friend bool operator<(const stack<U, Cntr>& a, const stack<U, Cntr>& b);

			template <class U, class Cntr>
			friend bool operator<=(const stack<U, Cntr>& a, const stack<U, Cntr>& b);

			template <class U, class Cntr>
			friend bool operator>(const stack<U, Cntr>& a, const stack<U, Cntr>& b);

			template <class U, class Cntr>
			friend bool operator>=(const stack<U, Cntr>& a, const stack<U, Cntr>& b);
	};

	template <class T, class Container>
	bool operator== (const stack<T,Container>& a, const stack<T,Container>& b)
		{	return	a.m_Container == b.m_Container;	};

	template <class T, class Container>
	bool operator!= (const stack<T,Container>& a, const stack<T,Container>& b)
		{	return	a.m_Container != b.m_Container;	};

	template <class T, class Container>
	bool operator<  (const stack<T,Container>& a, const stack<T,Container>& b)
		{	return	a.m_Container < b.m_Container;	};

	template <class T, class Container>
	bool operator<= (const stack<T,Container>& a, const stack<T,Container>& b)
		{	return	a.m_Container <= b.m_Container;	};

	template <class T, class Container>
	bool operator>  (const stack<T,Container>& a, const stack<T,Container>& b)
		{	return	a.m_Container > b.m_Container;	};

	template <class T, class Container>
	bool operator>= (const stack<T,Container>& a, const stack<T,Container>& b)
		{	return	a.m_Container >= b.m_Container;	};


}//namespace ft
