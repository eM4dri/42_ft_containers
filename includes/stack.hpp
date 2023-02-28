/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 09:47:33 by emadriga          #+#    #+#             */
/*   Updated: 2023/02/28 15:00:20 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "vector.hpp"

namespace ft
{

	template <typename T, typename Container = ft::vector<T> >
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
				if (this != &assign)
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

		///*	Friends (grants a function or another class access to private and protected members)
			template <typename U, typename Cntr>
			friend bool operator==(const stack<U, Cntr>& a, const stack<U, Cntr>& b);
			template <typename U, typename Cntr>
			friend bool operator<(const stack<U, Cntr>& a, const stack<U, Cntr>& b);

		private:	
			container_type _getStack() const {	return m_Container; }
	};

	template <typename T, typename Container>
	bool operator== (const stack<T,Container>& a, const stack<T,Container>& b)
		{	return	a._getStack() == b._getStack();	}

	template <typename T, typename Container>
	bool operator!= (const stack<T,Container>& a, const stack<T,Container>& b)
		{	return	!(a == b);	}

	template <typename T, typename Container>
	bool operator<  (const stack<T,Container>& a, const stack<T,Container>& b)
		{	return	a._getStack() < b._getStack();	}

	template <typename T, typename Container>
	bool operator<= (const stack<T,Container>& a, const stack<T,Container>& b)
		{	return	!(b < a);	}

	template <typename T, typename Container>
	bool operator>  (const stack<T,Container>& a, const stack<T,Container>& b)
		{	return	(b < a);	}

	template <typename T, typename Container>
	bool operator>= (const stack<T,Container>& a, const stack<T,Container>& b)
		{	return	!(a < b);	}


}//namespace ft
