/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:55:26 by emadriga          #+#    #+#             */
/*   Updated: 2023/03/08 11:25:06 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>									//	std::allocator
#include <stdexcept>								//	std::out_of_range & std::length_error
// #include <utility>								//	std::move
#include "iterators/random_access_iterator.hpp"
#include "iterators/reverse_iterator.hpp"
#include "utility/enable_if.hpp"
#include "utility/is_integral.hpp"
#include "utility/lexicographical_compare.hpp"
#include "utility/swap.hpp"
#include "utility/copy.hpp"
#include "utility/distance.hpp"

namespace ft
{
	template <	typename T,
				typename Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef Alloc														allocator_type;
			typedef T															value_type;
			typedef typename allocator_type::reference  						reference;
			typedef typename allocator_type::const_reference					const_reference;
			typedef typename allocator_type::pointer							pointer;
			typedef typename allocator_type::const_pointer						const_pointer;
			typedef ft::random_access_iterator<pointer>							iterator;
			typedef ft::random_access_iterator<const_pointer>					const_iterator;
			typedef ft::reverse_iterator<iterator>								reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type 	difference_type;
			typedef typename allocator_type::size_type							size_type;

		private:
			allocator_type		m_Allocate;
			pointer				m_Data;
			size_type			m_Size;
			size_type			m_Capacity;


		public:

		///*	Member functions
			explicit vector ( const allocator_type& alloc = allocator_type() )
				:	m_Allocate(alloc), m_Data(NULL), m_Size(0), m_Capacity(0) {	}
			explicit vector (	size_type n,
								const value_type& val = value_type(),
								const allocator_type& alloc = allocator_type())
				:	m_Allocate(alloc), m_Data(NULL), m_Size(n), m_Capacity(n)
			{
				if (n > 0)
					m_Data = m_Allocate.allocate(n);
				for (size_type i = 0; i < n; i++)
					m_Allocate.construct(&m_Data[i], val);
			}
			template <typename InputIt>
         	vector ( 	InputIt first,
			 			InputIt last,
						const allocator_type& alloc = allocator_type(),
						typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL
					)
				:	m_Allocate(alloc), m_Data(NULL), m_Size(0), m_Capacity(0)
				{	insert(begin(), first, last);	}
			vector( const vector & copy )
				:	m_Data(NULL), m_Size(0), m_Capacity(0)
				{	operator=(copy);	}

			~vector()	{	clear();	}

			vector & operator = (const vector & assign )
			{
				if (this != &assign)
				{
					if (m_Capacity > 0)
						clear();
					m_Allocate = assign.get_allocator();
					m_Size = assign.size();
					m_Capacity = assign.capacity();
					if (m_Capacity > 0)
						m_Data = m_Allocate.allocate(m_Capacity);
					for (size_type i = 0; i < m_Size; i++)
						m_Allocate.construct( &m_Data[i], assign.m_Data[i] );
						// m_Data[i] = std::move(assign.m_Data[i]);
				}
				return *this;
			}

		///*	Iterators
			iterator begin()	{	return iterator(m_Data);	}
			const_iterator begin() const	{	return const_iterator(m_Data);	}

			iterator end()	{	return iterator(m_Data + m_Size);	}
			const_iterator end() const	{	return const_iterator(m_Data + m_Size);		}

			reverse_iterator rbegin()	{	return reverse_iterator(end());	}
			const_reverse_iterator rbegin() const	{	return const_reverse_iterator(end());	}

			reverse_iterator rend()	{	return reverse_iterator(begin());	}
			const_reverse_iterator rend() const	{	return const_reverse_iterator(begin());	}

		///*	Capacity
			size_t size() const	{ return m_Size; }

			size_type max_size() const 	{  return m_Allocate.max_size();   }

			void resize (size_type n, value_type val = value_type())
			{
				size_type oldSize = m_Size;
				for (size_type i = n; i < m_Size; i++)
					m_Allocate.destroy( &m_Data[i] );
				if (n > m_Capacity)
					reserve(n);
				for (size_type i = oldSize; i < n; i++)
					// m_Data[i] = std::move(val);
					m_Allocate.construct( &m_Data[i], val );
				m_Size = n;
			}

			size_t capacity() const	{ return m_Capacity; }

			bool empty() const	{ return m_Size == 0; }

			void reserve(size_type newCapacity)
			{
				if (newCapacity > max_size())
					throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
				if (m_Capacity < newCapacity)
				{
					pointer newBlock;
					newBlock = m_Allocate.allocate(newCapacity);
					for (size_type i = 0; i < m_Size; i++)
						// new (&newBlock[i]) T(std::move(m_Data[i]));
						m_Allocate.construct( &newBlock[i], m_Data[i] );
					_clearData();
					m_Data = newBlock;
					m_Capacity = newCapacity;
				}
			}

		///*	Element access
			reference operator [] (size_t index)	{	return m_Data[index];	}
			const_reference operator [] (size_t index) const	{	return m_Data[index];	}

			reference at (size_type n)
			{
				if (n >= size())
					throw std::out_of_range("vector");
				return m_Data[n];
			}
			const_reference at (size_type n) const
			{
				if (n >= size())
					throw std::out_of_range("vector");
				return m_Data[n];
			}

			reference front()	{	return m_Data[0];	}
			const_reference front() const	{	return m_Data[0];	}

			reference back()	{	return m_Data[m_Size == 0 ? 0 : m_Size - 1];	}
			const_reference back() const	{	return m_Data[m_Size == 0 ? 0 : m_Size - 1];	}

		///*	Modifiers
			template < typename InputIt >
			void	assign(	InputIt first, InputIt last,
							typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL
						)
			{
				size_type newSize = static_cast<size_type>(ft::distance(first, last));
				for (size_type i = newSize; i < m_Size; i++)
					m_Allocate.destroy(&m_Data[i]);
				if (newSize > m_Capacity)
					reserve(newSize);
				for (size_type i = 0; first != last; i++)
				{
					// m_Data[i] = std::move( *first);
					m_Allocate.construct( &m_Data[i], *first );
					first++;
				}
				m_Size = newSize;
			}
			void assign (size_type n, const value_type& val)
			{
				for (size_type i = n; i < m_Size; i++)
					m_Allocate.destroy(&m_Data[i]);
				if (n > m_Capacity)
					reserve(n);
				for (size_type i = 0; i < n; i++)
					// m_Data[i] = std::move( val);
					m_Allocate.construct( &m_Data[i], val );
				m_Size = n;
			}

			void push_back (const value_type& val)
			{
				if (m_Capacity == 0)
					reserve(1);
				else if (m_Size >= m_Capacity)
					reserve(2 * m_Capacity);
				m_Allocate.construct( &m_Data[m_Size], val );
				// new (&m_Data[m_Size]) T(std::move(val));
				m_Size++;
			}

			void pop_back()
			{
				if (m_Size > 0)
				{
					m_Size--;
					m_Allocate.destroy(&m_Data[m_Size]);
					//m_Data[m_Size].~T();
				}
			}

			iterator insert( iterator position, const T& value )
			{
				size_type posIndex = _getIndex(position);
				if (m_Capacity == 0)
					reserve(1);
				else if (m_Size + 1 >= m_Capacity)
					reserve(m_Size + 1);
				// for (size_type i = m_Size; i != posIndex; i--)
				// 	m_Data[i] = std::move(m_Data[i - 1]);
				// m_Data[posIndex] = std::move(value);
				for (size_type i = m_Size; i != posIndex; i--)
					m_Allocate.construct( &m_Data[i], m_Data[i - 1] );
				m_Allocate.construct( &m_Data[posIndex], value );
				m_Size++;
				return (m_Data + posIndex);
			}
			void insert( iterator position, size_type count, const T& value )
			{
				size_type posIndex = _getIndex(position);

				if (m_Size + count >= m_Capacity)
				{
					m_Capacity = m_Size + count;
					T *newBlock = m_Allocate.allocate(m_Capacity);
					for (size_type i = 0; i < posIndex; i++)
						// newBlock[i] = std::move(m_Data[i]);
						m_Allocate.construct( &newBlock[i], m_Data[i] );
					for (size_type i = posIndex; i < m_Size; i++)
						// newBlock[i + count] = std::move(m_Data[i]);
						m_Allocate.construct( &newBlock[i + count], m_Data[i] );
					for (size_type i = posIndex; i < posIndex + count; i++)
						// newBlock[i] = std::move(value);
						m_Allocate.construct( &newBlock[i], value );
					_clearData();
					m_Data = newBlock;
				}
				else
				{
					ft::copy(position, end(), position + count);

					for (size_type i = posIndex; i < posIndex + count; i++)
						// m_Data[i] = std::move(value);
						m_Allocate.construct( &m_Data[i], value );
				}
				m_Size += count;
			}
			template< typename InputIt >
			void insert(	iterator pos,
							InputIt first,
							InputIt last,
							typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL )
			{
				size_type posIndex = _getIndex(pos);
				difference_type totalInserts = ft::distance(first, last);
				if (totalInserts != 0)
				{
					if (m_Size + totalInserts >= m_Capacity)
					{
						m_Capacity = m_Size + totalInserts;
						T *newBlock = m_Allocate.allocate(m_Capacity);
						for (size_type i = 0; i < posIndex; i++)
							m_Allocate.construct( &newBlock[i], m_Data[i] );
							// newBlock[i] = std::move(m_Data[i]);
						for (size_type i = posIndex; i < m_Size; i++)
							m_Allocate.construct( &newBlock[i + totalInserts], m_Data[i] );
							// newBlock[i + totalInserts] = std::move(m_Data[i]);
						for (size_type i = posIndex; i < posIndex + totalInserts; i++)
						{
							// newBlock[i] = std::move(*first);
							m_Allocate.construct( &newBlock[i], *first );
							first++;
						}
						_clearData();
						m_Data = newBlock;
					}
					else
					{
						ft::copy(pos, end(), pos + totalInserts);

						for (size_type i = posIndex; i < posIndex + totalInserts; i++)
						{
							// m_Data[i] = std::move(*first);
							m_Allocate.construct( &m_Data[i], *first );
							first++;
						}
					}
					m_Size += totalInserts;
				}
			}

			iterator erase (iterator position)
			{
				return erase(position, position + 1);
			}
			iterator erase (iterator first, iterator last)
			{
				ft::copy(last, end(), first);
				for (iterator it = last; it != first; it--)
					pop_back();
				return first;
			}

			void swap( vector& other )
			{
				ft::swap(m_Data, other.m_Data);
				ft::swap(m_Size, other.m_Size);
				ft::swap(m_Capacity, other.m_Capacity);
			}

			void clear()
			{
				_clearData();
				m_Size = 0;
				m_Capacity = 0;
			}

		///* Allocator
			allocator_type get_allocator() const	{ return m_Allocate; }

		private:
			template< typename InputIt >
			size_type _getIndex( InputIt position )
			{
				size_type index = 0;
				for (InputIt it= begin(); it != position; it++ )
					index++;
				return index;
			}

			void _clearData()
			{
				if (m_Size > 0)
				{
					// for (size_t i = 0; i < m_Size; i++)
					// 	m_Data[i].~T();
					for (size_t i = 0; i < m_Size; i++)
						m_Allocate.destroy(&m_Data[i]);
				}
				if (m_Capacity > 0)
					m_Allocate.deallocate(m_Data, m_Capacity);
					// ::operator  delete ( m_Data);
			}

	};

	template <typename T, typename Alloc>
	bool operator== (const vector<T,Alloc>& a, const vector<T,Alloc>& b)
	{
		typedef typename ft::vector<T>::const_iterator			const_iterator;

		if (a.size() != b.size())
			return false;
		const_iterator aIt = a.begin();
		const_iterator bIt= b.begin();
		while (aIt != a.end() && bIt != b.end())
		{
			if (*aIt != *bIt)
				return false;
			aIt++;
			bIt++;
		}
		if (aIt == a.end() && bIt == b.end())
			return true;
		return (false);
	}

	template <typename T, typename Alloc>
	bool operator!= (const vector<T,Alloc>& a, const vector<T,Alloc>& b)
		{	return !(a == b);	}

	template <typename T, typename Alloc>
	bool operator<  (const vector<T,Alloc>& a, const vector<T,Alloc>& b)
	{
		return ft::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
	}

	template <typename T, typename Alloc>
	bool operator>  (const vector<T,Alloc>& a, const vector<T,Alloc>& b)
		{	return (b < a);		}

	template <typename T, typename Alloc>
	bool operator<= (const vector<T,Alloc>& a, const vector<T,Alloc>& b)
		{	return !(b < a);	}

	template <typename T, typename Alloc>
	bool operator>= (const vector<T,Alloc>& a, const vector<T,Alloc>& b)
		{	return !(a < b);	}

	template <typename T, typename Alloc>
  	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
		{	x.swap(y);	}

}//namespace ft
