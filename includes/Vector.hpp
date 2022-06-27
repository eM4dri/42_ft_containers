#pragma once

#include <unistd.h>
#include "Log.hpp"
#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"
#include <memory>
#include <iostream>
#include <type_traits>

// #include <iosfwd>


namespace ft
{
	template< typename T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
			typedef T												value_type;
			typedef iterator< vector <T> >							iterator;
			typedef const iterator									const_iterator;
			typedef reverse_iterator< vector <T> >					reverse_iterator;
			typedef const reverse_iterator							const_reverse_iterator;
			typedef T*                                            	pointer;
			typedef const T*                                      	const_pointer;
			typedef T&                                            	reference;
			typedef const T&                                      	const_reference;
			typedef Allocator										allocator_type;
			typedef size_t											size_type;


		private:
			Allocator		m_Allocate;
			T*				m_Data;
			size_t			m_Size;
			size_t			m_Capacity;


		public:
			explicit vector ( const allocator_type& alloc = allocator_type() )
				:	m_Allocate(alloc), m_Data(nullptr), m_Size(0), m_Capacity(0)
			{
				reserve(2);
				LOG("Vector constructor");
			}

			explicit vector (	size_type n, 
								const value_type& val = value_type(),
								const allocator_type& alloc = allocator_type())
				:	m_Allocate(alloc), m_Data(nullptr), m_Size(n), m_Capacity(n)
			{
				m_Data = m_Allocate.allocate(n);
				for (size_type i = 0; i < n; i++)
					m_Allocate.construct(&m_Data[i], val);
				LOG("Vector constructor");
			}

			template <class InputIt>
         	vector ( 	
				 		InputIt first,
			 			InputIt last,
						const allocator_type& alloc = allocator_type(),
						typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL
					)
				:	m_Allocate(alloc), m_Data(nullptr), m_Size(0), m_Capacity(0)
			{
				m_Capacity = _getRange(first, last);
				m_Size = m_Capacity;
				m_Data = m_Allocate.allocate(m_Capacity);
				for (size_t i = 0; i < m_Size; i++)
				{
					m_Allocate.construct(&m_Data[i], *first);
					first++;
				}
				LOG("Vector constructor");
			}


			vector( const vector & copy )
			{ 
				*this = copy;
				LOG("Vector constructor"); 
			}

			vector & operator = (const vector & assign )
			{
				if (*this != assign)
				{
					if (m_Capacity > 0)
						clear();

					m_Allocate = assign.get_allocator();
					m_Capacity = assign.capacity();
					m_Size = assign.size();
					m_Data = m_Allocate.allocate(m_Capacity);
					for (size_t i = 0; i < m_Size; i++)
						m_Allocate.construct( &m_Data[i], assign.m_Data[i] );
				}
				return *this;
			}

			~vector()
			{
				clear();
				LOG("Vector destructor");
			}
			
			size_t size() const	{ return m_Size; }

			size_t capacity() const	{ return m_Capacity; }
			allocator_type get_allocator() const { return m_Allocate; }

			void push_back(const T & value)
			{
				if (m_Size >= m_Capacity)
					reserve(m_Capacity + m_Capacity / 2);
				m_Data[m_Size] = value;
				m_Size++;
			}

			void pop_back()
			{
				if (m_Size > 0)
				{
					m_Size--;
					m_Data[m_Size].~T();
				}
			}

			void clear()
			{
				_clearData();
				m_Size = 0;
				m_Capacity = 0;
			}

			iterator insert( iterator pos, const T& value )
			{
				size_t posIndex = _getIndex(pos);

				if (m_Size >= m_Capacity)
					reserve(m_Capacity + m_Capacity / 2);
				for (size_t i = m_Size; i != posIndex; i--)
					m_Data[i] = std::move(m_Data[i - 1]);
				m_Data[posIndex] = std::move(value);

				m_Size++;
				return (m_Data + posIndex);
			}

			// void insert( iterator pos, size_type count, const T& value ){
			// 	size_t posIndex = _getIndex(pos);

			// 	if (m_Size + count >= m_Capacity)
			// 	{
			// 		size_t newCapacity = m_Size + count;
			// 		// size_t newCapacity = m_Capacity;
			// 		// while ( m_Size + count >= newCapacity )
			// 		newCapacity += newCapacity>>1;
			// 		T *newBlock = m_Allocate.allocate(newCapacity);
			// 		for (size_t i = 0; i < posIndex; i++)
			// 			new (&newBlock[i]) T(std::move(m_Data[i]));
			// 		for (size_t i = posIndex; i < m_Size + count; i++)
			// 			new (&newBlock[i + count]) T(std::move(m_Data[i]));
			// 		for (size_t i = posIndex; i < posIndex + count; i++)
			// 			newBlock[i] =  value;
			// 			// newBlock[i] =  std::move(value);
			// 			//m_Allocate.construct( &newBlock[i], value );
			// 		_clearData();		
			// 		m_Data = newBlock;
			// 	}
			// 	else
			// 	{
			// 		for (size_t i = m_Size; i != posIndex; i--)
			// 			m_Data[i] = std::move(m_Data[i - 1]);
					
			// 		for (size_t i = posIndex; i < posIndex + count; i++)
			// 			m_Data[i] =  value;
			// 			// m_Data[i] =  std::move(value);
			// 			// m_Allocate.construct( &m_Data[i], value );
			// 	}
			// 	m_Size += count;
			// }
			
			void insert( iterator pos, size_type count, const T& value ){
				size_t posIndex = _getIndex(pos);
								
				if (m_Size + count >= m_Capacity)
				{
					size_t newCapacity = m_Size + count;
					// size_t newCapacity = m_Capacity;
					// while ( m_Size + count >= newCapacity )
					newCapacity += newCapacity>>1;
					T *newBlock = m_Allocate.allocate(newCapacity);
					for (size_t i = 0; i < posIndex; i++)
						m_Allocate.construct( &newBlock[i], m_Data[i] );
					for (size_t i = posIndex; i < m_Size + count; i++)
						m_Allocate.construct( &newBlock[i + count], m_Data[i] );
					for (size_t i = posIndex; i < posIndex + count; i++)
						m_Allocate.construct( &newBlock[i], value );
					_clearData();		
					m_Data = newBlock;
				}
				else
				{
					for (size_t i = m_Size; i != posIndex; i--)
						m_Data[i] = std::move(m_Data[i - 1]);
					
					for (size_t i = posIndex; i < posIndex + count; i++)
						m_Allocate.construct( &m_Data[i], value );
				}
				m_Size += count;
			}

			// template< class InputIt >
			// void insert( iterator pos, InputIt first, InputIt last )
			// {
			// 	size_t posIndex = _getIndex(pos);
			// 	size_t totalInserts = _getRange(first, last);
				
			// 	if (m_Size + totalInserts >= m_Capacity)
			// 	{
			// 		size_t newCapacity = m_Size + totalInserts;
			// 		// size_t newCapacity = m_Capacity;
			// 		// while ( m_Size + totalInserts >= newCapacity )
			// 		newCapacity += newCapacity>>1;
			// 		T *newBlock = m_Allocate.allocate(newCapacity);
			// 		for (size_t i = 0; i < posIndex; i++)
			// 			new (&newBlock[i]) T(std::move(m_Data[i]));
			// 		for (size_t i = posIndex; i < m_Size + totalInserts; i++)
			// 			new (&newBlock[i + totalInserts]) T(std::move(m_Data[i]));
			// 		for (size_t i = posIndex; i < posIndex + totalInserts; i++)
			// 			new (&newBlock[i]) T(std::move(*first++));
			// 			// m_Allocate.construct( &newBlock[i], *first++ );
			// 		_clearData();		
			// 		m_Data = newBlock;
			// 	}
			// 	else
			// 	{
			// 		for (size_t i = m_Size; i != posIndex; i--)
			// 			m_Data[i] = std::move(m_Data[i - 1]);
					
			// 		for (size_t i = posIndex; i < posIndex + totalInserts; i++)
			// 			m_Allocate.construct( &m_Data[i], *first++ );
			// 	}
			// 	m_Size += totalInserts;
			// }
			
			template< class InputIt >
			void insert( 
							iterator pos,
							InputIt first,
							InputIt last,
							typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL)
			{
				size_t posIndex = _getIndex(pos);
				size_t totalInserts = _getRange(first, last);
				
				if (m_Size + totalInserts >= m_Capacity)
				{
					size_t newCapacity = m_Size + totalInserts;
					// size_t newCapacity = m_Capacity;
					// while ( m_Size + totalInserts >= newCapacity )
					newCapacity += newCapacity>>1;
					T *newBlock = m_Allocate.allocate(newCapacity);
					for (size_t i = 0; i < posIndex; i++)
						m_Allocate.construct( &newBlock[i], m_Data[i] );
					for (size_t i = posIndex; i < m_Size + totalInserts; i++)
						m_Allocate.construct( &newBlock[i + totalInserts], m_Data[i] );
					for (size_t i = posIndex; i < posIndex + totalInserts; i++)
					{
						m_Allocate.construct( &newBlock[i], first );
						first++;
					}
					_clearData();		
					m_Data = newBlock;
				}
				else
				{
					for (size_t i = m_Size; i != posIndex; i--)
						m_Data[i] = std::move(m_Data[i - 1]);
					
					for (size_t i = posIndex; i < posIndex + totalInserts; i++)
					{
						m_Allocate.construct( &m_Data[i], first );
						first++;
					}
				}
				m_Size += totalInserts;
			}

			iterator begin()
			{
				return iterator(m_Data);
			}

			const_iterator begin() const
			{
				return const_iterator(m_Data);
			}

			// const_iterator cbegin() const
			// {
			// 	return const_iterator(m_Data);
			// }

			iterator end()
			{
				return iterator(m_Data + m_Size);
			}

			const_iterator end() const
			{
				return const_iterator(m_Data + m_Size);
			}

			// const_iterator cend() const
			// {
			// 	return const_iterator(m_Data + m_Size);
			// }

			reverse_iterator rbegin()
			{
				return reverse_iterator(m_Data + m_Size - 1);
			}

			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(m_Data + m_Size - 1);
			}

			// const_reverse_iterator crbegin() const
			// {
			// 	return const_reverse_iterator(m_Data + m_Size - 1);
			// }

			reverse_iterator rend()
			{
				return reverse_iterator(m_Data - 1);
			}

			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(m_Data - 1);
			}

			// const_reverse_iterator crend() const
			// {
			// 	return const_reverse_iterator(m_Data - 1);
			// }


			const T& operator [] (size_t index) const
			{
				return m_Data[index];
			}

			T& operator [] (size_t index)
			{
				return m_Data[index];
			}

			// void Print()
			// {
			// 	for (iterator it = begin(); it != end(); it++)
			// 		std::cout << *it << std::endl;
			// 	std::cout << "\t-------------\t" << std::endl;		
			// }
			
			void reserve(size_type newCapacity)
			{
				if (m_Capacity < newCapacity)
				{
					T *newBlock = m_Allocate.allocate(newCapacity);

					if (newCapacity < m_Size)
						m_Size = newCapacity;

					for (size_t i = 0; i < m_Size; i++)
						m_Allocate.construct(&newBlock[i], m_Data[i]);

					_clearData();
									
					m_Data = newBlock;
					m_Capacity = newCapacity;
				}
			}

		private:
			void _realloc(size_t newCapacity)
			{
				//T *newBlock = new T[newCapacity];
				T *newBlock = (T*)::operator new (newCapacity * sizeof(T));

				if (newCapacity < m_Size)
					m_Size = newCapacity;

				for (size_t i = 0; i < m_Size; i++)
					//newBlock[i] = std::move(m_Data[i]);
					new (&newBlock[i]) T(std::move(m_Data[i]));
				
				for (size_t i = 0; i < m_Size; i++)
					m_Data[i].~T();
				::operator  delete ( m_Data);
				//delete m_Data;

				m_Data = newBlock;
				m_Capacity = newCapacity;
			}

			size_t _getIndex( iterator position )
			{
				size_t index = 0;
				while (&m_Data[index] != &(*position))
					index++;
				return index;
			}

			template< class InputIt >
			size_t _getRange(InputIt first, InputIt last)
			{
				size_t range = 0;

				while (first++ != last)
					range++;
				return range;
			}

			void _clearData()
			{
				// for (size_t i = 0; i < m_Size; i++)
				// 	m_Data[i].~T();
				// ::operator  delete ( m_Data);
				for (size_t i = 0; i < m_Size; i++)
					m_Allocate.destroy(&m_Data[i]);
				m_Allocate.deallocate(m_Data, m_Capacity);
			}


	};

}//namespace ft
