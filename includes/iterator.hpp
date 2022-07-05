/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:55:32 by emadriga          #+#    #+#             */
/*   Updated: 2022/07/05 18:08:21 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Log.hpp"
#include "vector.hpp"
#include <cstddef>

namespace ft
{

	struct input_iterator_tag {}; // LegacyInputIterator .
	struct output_iterator_tag {}; // LegacyOutputIterator 
	struct forward_iterator_tag			: public input_iterator_tag {};  // LegacyForwardIterator
	struct bidirectional_iterator_tag	: public forward_iterator_tag {};  //  LegacyBidirectionalIterator
	struct random_access_iterator_tag	: public bidirectional_iterator_tag {}; // LegacyRandomAccessIterator

		/*  Check iterator_tag*/

	template <bool is_valid, typename T>
		struct check_iterator_tag
		{
			typedef T type;
			const static bool value = is_valid;
		};
	

	template< typename T >
		struct is_input_it_tag : public check_iterator_tag <false , T> {};
		
	template<>
		struct is_input_it_tag<ft::input_iterator_tag> : public check_iterator_tag<true, ft::input_iterator_tag> {};
		
	template<>
		struct is_input_it_tag<ft::output_iterator_tag> : public check_iterator_tag<true, ft::output_iterator_tag> {};

	template<>
		struct is_input_it_tag<ft::forward_iterator_tag> : public check_iterator_tag<true, ft::forward_iterator_tag> {};
		
	template<>
		struct is_input_it_tag<ft::bidirectional_iterator_tag> : public check_iterator_tag<true, ft::bidirectional_iterator_tag> {};
		
	template<>
		struct is_input_it_tag<ft::random_access_iterator_tag> : public check_iterator_tag<true, ft::random_access_iterator_tag> {};


	template< typename T >
		struct __is_forward_iterator: public check_iterator_tag <false , T> {};
	template<>
		struct __is_forward_iterator <ft::forward_iterator_tag> : public check_iterator_tag<true, ft::forward_iterator_tag> {};
	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator {
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;
	};

	template<class Iter>
	struct iterator_traits 
	{
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::iterator_category	iterator_category;
	};

	template<class T>
	struct iterator_traits<T*> 
	{
		typedef T										value_type;
		typedef T*										pointer;
		typedef T&										reference;
		typedef ptrdiff_t								difference_type;
		typedef std::random_access_iterator_tag			iterator_category;
	};

	template<class T>
	struct iterator_traits<const T*> 
	{
		typedef T										value_type;
		typedef T*										pointer;
		typedef T&										reference;
		typedef ptrdiff_t								difference_type;
		typedef std::random_access_iterator_tag			iterator_category;
	};

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

		public:
			random_access_iterator()
				:	m_Ptr(nullptr) { }
				
			random_access_iterator(pointer ptr)
				:	m_Ptr(ptr) {}
				
			random_access_iterator( const random_access_iterator & copy )
				{	*this = copy;	}

			~random_access_iterator(){}
			

			random_access_iterator & operator= ( const random_access_iterator & assign )
			{
				if (*this != assign)
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

			random_access_iterator & operator++ (int)
			{
				random_access_iterator &tmp = *this;
				++m_Ptr;
				return tmp;
			}

			random_access_iterator & operator-- ()
			{
				m_Ptr--;
				return (*this);
			}

			random_access_iterator & operator-- (int)
			{
				random_access_iterator &tmp = *this;
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

	template <class T>
	bool operator== (const random_access_iterator<T>& a, const random_access_iterator<T>& b)
		{	a.getPtr() == b.getPtr();	}
		
	template <class T>
	bool operator!= (const random_access_iterator<T>& a,	const random_access_iterator<T>& b)
		{	return !(a == b);	}

	template <class T>
	bool operator<  (const random_access_iterator<T>& a,	const random_access_iterator<T>& b)
		{	return a.getPtr() > b.getPtr();	}
				   
	template <class T>
	bool operator>  (const random_access_iterator<T>& a,	const random_access_iterator<T>& b)
		{	return b < a;	}
		
	template <class T>
	bool operator>=  (const random_access_iterator<T>& a,	const random_access_iterator<T>& b)
		{	return !(a < b);	}
		
	template <class T>
	bool operator<=  (const random_access_iterator<T>& a,	const random_access_iterator<T>& b)
		{	return !(a > b);	}

	template <class T>
	random_access_iterator<T> operator+ (typename random_access_iterator<T>::difference_type n, const random_access_iterator<T>& b)
		{	return random_access_iterator<T>(b.getPtr() + n);	}

	template <class T>
	typename random_access_iterator<T>::difference_type operator- (const random_access_iterator<T>& a, const random_access_iterator<T>& b)
		{	return b.getPtr() - a.getPtr();	}
	
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
				{ return m_Base; }

			reference operator* () const 
			{	
				iterator_type	copy = m_Base;	
				return *--copy;	
			}

			pointer operator-> () const 
				{	return &(operator*());	}

			reference operator[] (difference_type n) const
				{	return m_Base( -n -1);	}
			
			reverse_iterator & operator ++ ()
			{
				m_Base--;
				return (*this);
			}

			reverse_iterator & operator++ (int)
			{
				reverse_iterator &tmp = *this;
				--m_Base;
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

			reverse_iterator & operator-- (int)
			{
				reverse_iterator &tmp = *this;
				++m_Base;
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
	
	template <class Iter>
	bool operator== (const reverse_iterator<Iter>& a, const reverse_iterator<Iter>& b)
		{	return (a.base() == b.base());	}
		
	template <class Iter>
	bool operator!= (const reverse_iterator<Iter>& a,	const reverse_iterator<Iter>& b)
		{	return	(a.base() != b.base());	}

	template <class Iter>
	bool operator<  (const reverse_iterator<Iter>& a,	const reverse_iterator<Iter>& b)
		{	return (a.base() > b.base());	}

	template <class Iter>
	bool operator<=  (const reverse_iterator<Iter>& a,	const reverse_iterator<Iter>& b)
		{	return (a.base() >= b.base());	}

				   
	template <class Iter>
	bool operator>  (const reverse_iterator<Iter>& a,	const reverse_iterator<Iter>& b)
		{	return (a.base() < b.base());	}
	
	template <class Iter>
	bool operator>=  (const reverse_iterator<Iter>& a,	const reverse_iterator<Iter>& b)
		{	return (a.base() <= b.base());	}

	template <class Iter>
	reverse_iterator<Iter> operator+ (typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it)
		{	return reverse_iterator<Iter>(it.base() - n);	}
	
	template <class Iter>
	typename reverse_iterator<Iter>::difference_type operator- (const reverse_iterator<Iter>& a, const reverse_iterator<Iter>& b)
		{	return b.base() - a.base();	}


}//namespace ft
