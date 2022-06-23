#pragma once

#include <unistd.h>
#include "Log.hpp"
#include "VectorIterator.hpp"

template< typename T>
class Vector
{
public:
	typedef T 												value_type;
	typedef VectorIterator< Vector <T> >					iterator;
	typedef const iterator									const_iterator;
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
	Vector() 
		:	m_Data(nullptr), m_Size(0), m_Capacity(0)
	{ 
		Realloc(2);
		LOG("Vector constructor");
	}

	~Vector()
	{
		LOG("Vector destructor");
		Clear();
	}
	
	size_t Size() const
	{
		return m_Size;
	}

	void PushBack(const T & value)
	{
		if (m_Size >= m_Capacity)
			Realloc(m_Capacity + m_Capacity / 2);
		m_Data[m_Size] = value;
		m_Size++;
	}

	void PopBack()
	{
		if (m_Size > 0)
		{
			m_Size--;
			m_Data[m_Size].~T();
		}
	}

	void Clear()
	{
		for (size_t i = 0; i < m_Size; i++)
			m_Data[i].~T();
		m_Size = 0;
		m_Capacity = 0;
		::operator  delete ( m_Data);
		// delete m_Data;
	}

	iterator begin()
	{
		return iterator(m_Data);
	}

	const_iterator begin() const
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


	const T& operator [] (size_t index) const
	{
		return m_Data[index];
	}

	T& operator [] (size_t index)
	{
		return m_Data[index];
	}

	void Print()
	{
		for (iterator it = begin(); it != end(); it++)
			std::cout << *it << std::endl;
		std::cout << "\t-------------\t" << std::endl;		
	}

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
