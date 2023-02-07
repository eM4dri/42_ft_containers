/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:55:32 by emadriga          #+#    #+#             */
/*   Updated: 2023/02/07 14:39:43 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator_traits.hpp"

namespace ft
{
	template<typename Iter>
	class random_access_iterator
	{
		public:
			typedef	Iter															iterator_type;
			typedef typename ft::iterator_traits<iterator_type>::value_type 		value_type;
			typedef typename ft::iterator_traits<iterator_type>::pointer 			pointer;
			typedef typename ft::iterator_traits<iterator_type>::reference 			reference;
			typedef typename ft::iterator_traits<iterator_type>::difference_type 	difference_type;
			typedef typename ft::iterator_traits<iterator_type>::iterator_category 	iterator_category;

		private:
			pointer m_Ptr;
			// template <typename U, typename V>
			// friend bool operator==(const random_access_iterator<U>& a, const random_access_iterator<V>& b);

			// template <typename U, typename V>
			// friend bool operator<(const random_access_iterator<U>& a, const random_access_iterator<V>& b);

			// template <typename U, typename V>
			// friend typename random_access_iterator<U>::difference_type operator-(random_access_iterator<U> a, random_access_iterator<V> b);

		public:
			random_access_iterator()
				:	m_Ptr(NULL) { }

			template <typename U>
			random_access_iterator(const random_access_iterator<U> &src)
				: m_Ptr(src.getPtr()) {}

			random_access_iterator(pointer ptr)
				:	m_Ptr(ptr) {}

			random_access_iterator( const random_access_iterator & copy )
				:	m_Ptr(NULL)
				{	operator=(copy);	}

			~random_access_iterator(){}


			random_access_iterator & operator= ( const random_access_iterator & assign )
			{
				if (this != &assign)
					m_Ptr = assign.getPtr();
				return (*this);
			}

			pointer getPtr() const
				{ return m_Ptr; }

			random_access_iterator & operator++ ()
			{
				m_Ptr++;
				return (*this);
			}

			random_access_iterator  operator++ (int)
			{
				random_access_iterator tmp(*this);
				++m_Ptr;
				return tmp;
			}

			random_access_iterator & operator-- ()
			{
				m_Ptr--;
				return (*this);
			}

			random_access_iterator  operator-- (int)
			{
				random_access_iterator tmp(*this);
				--m_Ptr;
				return tmp;
			}

			reference operator[] (int index) const
				{	return *(m_Ptr + index);	}

			pointer operator-> () const
				{	return m_Ptr;	}

			reference operator* () const
				{	return *m_Ptr;	}

			bool operator== ( const random_access_iterator & other ) const
				{	return m_Ptr == other.m_Ptr;	}

			bool operator!= ( const random_access_iterator & other ) const
				{	return !(*this == other);	}

			random_access_iterator& operator+= (difference_type n)
				{ m_Ptr += n; return (*this); }

			random_access_iterator& operator-= (difference_type n)
				{ m_Ptr -= n; return (*this); }

			random_access_iterator operator+ (difference_type n) const
				{ return (m_Ptr + n); }

			random_access_iterator operator- (difference_type n) const
				{ return (m_Ptr - n); }

	};

	template <typename T, typename U>
	bool operator== (const random_access_iterator<T>& a, const random_access_iterator<U>& b)
		{	return a.getPtr() == b.getPtr();	}

	template <typename T, typename U>
	bool operator!= (const random_access_iterator<T>& a,	const random_access_iterator<U>& b)
		{	return !operator==(a, b);	}

	template <typename T, typename U>
	bool operator<  (const random_access_iterator<T>& a,	const random_access_iterator<U>& b)
		{	return a.getPtr() < b.getPtr();	}

	template <typename T, typename U>
	bool operator>  (const random_access_iterator<T>& a,	const random_access_iterator<U>& b)
		{	return operator<(b, a);	}

	template <typename T, typename U>
	bool operator>=  (const random_access_iterator<T>& a,	const random_access_iterator<U>& b)
		{	return !operator<(a, b);	}

	template <typename T, typename U>
	bool operator<=  (const random_access_iterator<T>& a,	const random_access_iterator<U>& b)
		{	return !operator>(a, b);	}

	template <typename T>
	random_access_iterator<T> operator+(random_access_iterator<T> it, typename random_access_iterator<T>::difference_type n)
	{
		it += n;
		return it;
	}

	template <typename T>
	random_access_iterator<T> operator+(typename random_access_iterator<T>::difference_type n, random_access_iterator<T> it)
	{
		it += n;
		return it;
	}

	template <typename T>
	random_access_iterator<T> operator-(random_access_iterator<T> it, typename random_access_iterator<T>::difference_type n)
	{
		it -= n;
		return it;
	}

	template <typename T>
	random_access_iterator<T> operator-(typename random_access_iterator<T>::difference_type n, random_access_iterator<T> it)
	{
		it -= n;
		return it;
	}

	template <typename T, typename U>
	typename random_access_iterator<T>::difference_type operator-(random_access_iterator<T> a, random_access_iterator<U> b)
	{
		return a.getPtr() - b.getPtr();
	}


}//namespace ft
