#pragma once

#include "Log.hpp"
#include "vector.hpp"

namespace ft
{

	template<typename T>
	class reverse_iterator
	{
		public:
			typedef typename T::value_type 			ValueType;
			typedef ValueType*						PointerType;
			typedef ValueType&						ReferenceType;
		private:
			PointerType m_Ptr;

		public:
			reverse_iterator(PointerType ptr)
				: m_Ptr(ptr) 
			{	
				LOG("reverse_iterator constructor"); 
			}
			
			reverse_iterator & operator ++ ()
			{
				m_Ptr--;
				return (*this);
			}

			reverse_iterator & operator ++ (int)
			{
				reverse_iterator &tmp = *this;
				--m_Ptr;
				return tmp;
			}

			reverse_iterator & operator -- ()
			{
				m_Ptr++;
				return (*this);
			}

			reverse_iterator & operator -- (int)
			{
				reverse_iterator &tmp = *this;
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

			bool operator == ( const reverse_iterator & other ) const
			{
				return m_Ptr == other.m_Ptr;	
			}
			
			bool operator != ( const reverse_iterator & other ) const
			{
				return !(*this == other);	
			}
	};
}//namespace ft
