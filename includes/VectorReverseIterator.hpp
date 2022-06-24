#pragma once

#include "Log.hpp"
#include "Vector.hpp"

template<typename T>
class VectorReverseIterator
{
public:
	typedef typename T::value_type 			ValueType;
	typedef ValueType*						PointerType;
	typedef ValueType&						ReferenceType;
private:
	PointerType m_Ptr;

public:
	VectorReverseIterator(PointerType ptr)
		: m_Ptr(ptr) 
	{	
		LOG("VectorReverseIterator constructor"); 
	}
	
	VectorReverseIterator & operator ++ ()
	{
		m_Ptr--;
		return (*this);
	}

	VectorReverseIterator & operator ++ (int)
	{
		VectorReverseIterator &tmp = *this;
		--m_Ptr;
		return tmp;
	}

	VectorReverseIterator & operator -- ()
	{
		m_Ptr++;
		return (*this);
	}

	VectorReverseIterator & operator -- (int)
	{
		VectorReverseIterator &tmp = *this;
		++m_Ptr;
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

	bool operator == ( const VectorReverseIterator & other ) const
	{
		return m_Ptr == other.m_Ptr;	
	}
	
	bool operator != ( const VectorReverseIterator & other ) const
	{
		return !(*this == other);	
	}
};
