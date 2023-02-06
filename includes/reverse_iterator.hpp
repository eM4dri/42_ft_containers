/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:55:32 by emadriga          #+#    #+#             */
/*   Updated: 2023/02/06 18:16:52 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator_traits.hpp"

namespace ft
{
	template< typename Iter>
	class reverse_iterator
	{
		public:
			typedef	Iter															iterator_type;
			typedef typename ft::iterator_traits<iterator_type>::value_type 		value_type;
			typedef typename ft::iterator_traits<iterator_type>::pointer 			pointer;
			typedef typename ft::iterator_traits<iterator_type>::reference 			reference;
			typedef typename ft::iterator_traits<iterator_type>::difference_type 	difference_type;
			typedef typename ft::iterator_traits<iterator_type>::iterator_category 	iterator_category;
		private:
			iterator_type m_Base;

		public:
			reverse_iterator()
				:	m_Base()	{ }

			explicit reverse_iterator (iterator_type it)
				:	m_Base(it)	{ }

			template <class _Iter>
			reverse_iterator (const reverse_iterator<_Iter>& copy)
				:	m_Base( copy.base() )	{ }

			iterator_type base() const
				{ return iterator_type(m_Base); }

			reference operator* () const
			{
				iterator_type	copy(m_Base);
				return *--copy;
			}

			pointer operator-> () const
				{	return &(operator*());	}

			reference operator[] (difference_type n) const
				{	return m_Base[-n -1];	}

			reverse_iterator & operator ++ ()
			{
				m_Base--;
				return (*this);
			}

			reverse_iterator operator++ (int)
			{
				reverse_iterator tmp(*this);
				m_Base--;
				return tmp;
			}

			reverse_iterator operator+= (difference_type n)
			{
				m_Base -= n;
				return (*this);
			}

			reverse_iterator & operator-- ()
			{
				m_Base++;
				return (*this);
			}

			reverse_iterator operator-- (int)
			{
				reverse_iterator tmp = *this;
				m_Base++;
				return tmp;
			}

			reverse_iterator operator-= (difference_type n)
			{
				m_Base += n;
				return (*this);
			}

			reverse_iterator operator+ (difference_type n) const
				{	return reverse_iterator(m_Base - n); 	}

			reverse_iterator operator- (difference_type n) const
				{	return reverse_iterator(m_Base + n); 	}

	};

	template <typename Iter1, typename Iter2>
	bool operator== (const reverse_iterator<Iter1>& a, const reverse_iterator<Iter2>& b)
		{	return (a.base() == b.base());	}

	template <typename Iter1, typename Iter2>
	bool operator!= (const reverse_iterator<Iter1>& a,	const reverse_iterator<Iter2>& b)
		{	return	(a.base() != b.base());	}

	template <typename Iter1, typename Iter2>
	bool operator<  (const reverse_iterator<Iter1>& a,	const reverse_iterator<Iter2>& b)
		{	return (a.base() > b.base());	}

	template <typename Iter1, typename Iter2>
	bool operator<=  (const reverse_iterator<Iter1>& a,	const reverse_iterator<Iter2>& b)
		{	return (a.base() >= b.base());	}

	template <typename Iter1, typename Iter2>
	bool operator>  (const reverse_iterator<Iter1>& a,	const reverse_iterator<Iter2>& b)
		{	return (a.base() < b.base());	}

	template <typename Iter1, typename Iter2>
	bool operator>=  (const reverse_iterator<Iter1>& a,	const reverse_iterator<Iter2>& b)
		{	return (a.base() <= b.base());	}

	template <typename Iter>
	reverse_iterator<Iter> operator+ (typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it)
		{	return reverse_iterator<Iter>(it.base() - n);	}

	template <typename Iter1, typename Iter2>
	typename reverse_iterator<Iter1>::difference_type operator- (const reverse_iterator<Iter1>& a, const reverse_iterator<Iter2>& b)
		{	return b.base() - a.base();	}


}//namespace ft
