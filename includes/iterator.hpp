#pragma once

#include "Log.hpp"
#include "vector.hpp"

namespace ft
{
	template<typename T>
	class iterator
	{
		public:
			typedef typename T::value_type 			ValueType;
			typedef ValueType*						PointerType;
			typedef ValueType&						ReferenceType;
		private:
			PointerType m_Ptr;

		public:
			iterator(PointerType ptr)
				: m_Ptr(ptr) 
			{	
				LOG("iterator constructor"); 
			}
			
			iterator & operator ++ ()
			{
				m_Ptr++;
				return (*this);
			}

			iterator & operator ++ (int)
			{
				iterator &tmp = *this;
				++m_Ptr;
				return tmp;
			}

			iterator & operator -- ()
			{
				m_Ptr--;
				return (*this);
			}

			iterator & operator -- (int)
			{
				iterator &tmp = *this;
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

			bool operator == ( const iterator & other ) const
			{
				return m_Ptr == other.m_Ptr;	
			}
			
			bool operator != ( const iterator & other ) const
			{
				return !(*this == other);	
			}
	};

}//namespace ft
