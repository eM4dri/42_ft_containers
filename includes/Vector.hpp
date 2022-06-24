#pragma once

#include <unistd.h>
#include "Log.hpp"
#include "iterator.hpp"
#include "reverse_iterator.hpp"


namespace ft
{

	template< typename T>
	class vector
	{
	public:
		typedef T 												value_type;
		typedef iterator< vector <T> >							iterator;
		typedef const iterator									const_iterator;
		typedef reverse_iterator< vector <T> >					reverse_iterator;
		typedef const reverse_iterator							const_reverse_iterator;
		// typedef T 											value_type;
		// typedef Allocator									allocator_type;
		// typedef typename size_t								size_type;
		// typedef typename std::ptrdiff_t						difference_type;
		// typedef value_type&							 		reference;
		// typedef const value_type&							const reference;
		// typedef typename Allocator::pointer  				pointer;
		// typedef typename Allocator::const_pointer			const_pointer;
		// typedef pointer                                  	iterator;
		// typedef const_pointer                            	const_iterator;

	private:
		T*			m_Data;
		size_t		m_Size;
		size_t		m_Capacity;

	public:
		vector() 
			:	m_Data(nullptr), m_Size(0), m_Capacity(0)
		{
			Realloc(2);
			// T initBlock;
			// T *newBlock = (T*)::operator new (newCapacity * sizeof(T));
			// T *initBlock = (T*)::operator new (sizeof(T));
			// initBlock = nullptr;
			// push_back(*initBlock);
			LOG("Vector constructor");
			// ::operator  delete ( m_Data);
		}

		~vector()
		{
			LOG("Vector destructor");
			clear();
		}
		
		size_t size() const
		{
			return m_Size;
		}

		size_t capacity() const
		{
			return m_Capacity;
		}

		void push_back(const T & value)
		{
			if (m_Size >= m_Capacity)
				Realloc(m_Capacity + m_Capacity / 2);
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
			for (size_t i = 0; i < m_Size; i++)
				m_Data[i].~T();
			m_Size = 0;
			m_Capacity = 0;
			::operator  delete ( m_Data);
			// delete m_Data;
		}

		iterator insert( iterator pos, const T& value ){
			if (m_Size >= m_Capacity)
				Realloc(m_Capacity + m_Capacity / 2);
			size_t index = 0;
			while (m_Data[index] != *pos)
				index++;
			for (size_t i = m_Size - 1; i != index; i--)
				m_Data[i] = std::move(m_Data[i - 1]);
			m_Data[index] = std::move(value);
			m_Size++;
			return (m_Data + index);
		}

		// void insert( iterator pos, size_type count, const T& value );

		// template< class InputIt >
		// void insert( iterator pos, InputIt first, InputIt last );

		iterator begin()
		{
			return iterator(m_Data);
		}

		const_iterator begin() const
		{
			return const_iterator(m_Data);
		}

		const_iterator cbegin() const
		{
			return const_iterator(m_Data);
		}

		iterator end()
		{
			return iterator(m_Data + m_Size);
		}

		const_iterator end() const
		{
			return const_iterator(m_Data + m_Size);
		}

		const_iterator cend() const
		{
			return const_iterator(m_Data + m_Size);
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(m_Data + m_Size - 1);
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(m_Data + m_Size - 1);
		}

		const_reverse_iterator crbegin() const
		{
			return const_reverse_iterator(m_Data + m_Size - 1);
		}

		reverse_iterator rend()
		{
			return reverse_iterator(m_Data - 1);
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(m_Data - 1);
		}

		const_reverse_iterator crend() const
		{
			return const_reverse_iterator(m_Data - 1);
		}


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

	private:
		void Realloc(size_t newCapacity)
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

	};

}//namespace ft
