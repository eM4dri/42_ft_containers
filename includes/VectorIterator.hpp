#pragma once

#include "Log.hpp"
#include "Vector.hpp"

template<typename T>
class VectorIterator
{
public:
	typedef typename T::value_type 			ValueType;
	typedef ValueType*						PointerType;
	typedef ValueType&						ReferenceType;
private:
	PointerType m_Ptr;

public:
	VectorIterator(PointerType ptr)
		: m_Ptr(ptr) 
	{	
		LOG("VectorIterator constructor"); 
	}
	
	VectorIterator & operator ++ ()
	{
		m_Ptr++;
		return (*this);
	}

	VectorIterator & operator ++ (int)
	{
		VectorIterator &tmp = *this;
		++m_Ptr;
		return tmp;
	}

	VectorIterator & operator -- ()
	{
		m_Ptr--;
		return (*this);
	}

	VectorIterator & operator -- (int)
	{
		VectorIterator &tmp = *this;
		--m_Ptr;
		return tmp;
	}

	ReferenceType operator [] (int index)
	{
		return *(m_Ptr + index);
	}

	PointerType operator->()
	{
		return m_Ptr;
	}

	ReferenceType operator *()
	{
		return *m_Ptr;
	}

	bool operator == ( const VectorIterator & other ) const
	{
		return m_Ptr == other.m_Ptr;	
	}
	
	bool operator != ( const VectorIterator & other ) const
	{
		return !(*this == other);	
	}
};
