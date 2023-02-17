/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   map.hpp											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: emadriga <emadriga@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/09/22 16:12:32 by emadriga		  #+#	#+#			 */
/*   Updated: 2023/02/14 11:58:41 by emadriga		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#pragma once
#include <map>
#include "tree_iterator.hpp"
#include "red_black_tree.hpp"
#include "reverse_iterator.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"
#include "lexicographical_compare.hpp"
#include "equal.hpp"
#include "pair.hpp"

namespace ft{
	template < class Key,										   // map::key_type
		   class T,												 // map::mapped_type
		   class Compare = std::less<Key>,						  // map::key_compare
		   class Alloc = std::allocator<std::pair<const Key,T> >	// map::allocator_type
		   >
	class map
	{
		public:
			typedef Key												key_type;
			typedef T												mapped_type;
			typedef ft::pair<const key_type,mapped_type>			value_type;
			typedef Compare 										key_compare;
			typedef Alloc											allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef typename allocator_type::size_type				size_type;

		private:
			// template <class Key, class T, class Compare, class Alloc>
			typedef struct valueCompare
			{   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
			// friend class map;
			// protected:
				key_compare comp;
				valueCompare (key_compare c) : comp(c) {}  // constructed with map's comparison object
			public:
				// typedef bool result_type;
				// typedef value_type first_argument_type;
				// typedef value_type second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			}value_compare;



			typedef ft::red_black_tree<	key_type,
										value_type,
										key_compare,
										allocator_type
										>							tree_type;
			typedef typename tree_type::node_ptr					node_ptr;

			allocator_type			m_Allocate;
			tree_type				m_Tree;
			value_compare			m_Compare;

		public:
			typedef typename tree_type::iterator					iterator;
			typedef typename tree_type::const_iterator				const_iterator;
			typedef typename tree_type::reverse_iterator			reverse_iterator;
			typedef typename tree_type::const_reverse_iterator		const_reverse_iterator;

		public:
		///*	Member functions
			explicit map (  const key_compare& comp = key_compare(),
							const allocator_type& alloc = allocator_type())
				:	m_Allocate(alloc), m_Tree(), m_Compare(comp) {};

			template <class InputIterator>
			map (   InputIterator first,
					InputIterator last,
					const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type())
				:   m_Allocate(alloc), m_Tree(), m_Compare(comp)
				{   insert(first, last);	};

			map (const map& copy)
				{	operator=(copy);	}

			~map()	{	clear();	}

			map& operator= (const map & assign )
			{
				if (this != &assign)
				{
					if (empty() != 0)
						clear();
					m_Allocate = assign.get_allocator();
					insert(assign.begin(), assign.end());
					m_Compare = assign.m_Compare;
				}
				return *this;
			}

		///*	Iterators
			iterator begin()	{	return m_Tree.begin();	}
			const_iterator begin() const	{	return m_Tree.begin();	}

			iterator end()	{	return m_Tree.end();	}
			const_iterator end() const	{	return m_Tree.end();	}

			reverse_iterator rbegin()	{	return reverse_iterator(end());	}
			const_reverse_iterator rbegin() const	{	return const_reverse_iterator(end());	}

			reverse_iterator rend()	{	return reverse_iterator(begin());	}
			const_reverse_iterator rend() const	{	return const_reverse_iterator(begin());	}


		///*	Capacity
			bool empty() const  {   return m_Tree.empty();   }

			size_type size() const  {   return m_Tree.size();   }

			size_type max_size() const {	return m_Tree.max_size();   }

		///*	Element access
			mapped_type& operator[] (const key_type& k)
			{
				iterator _node = m_Tree.find(k);
				if (!_node)
				{
					return  (*((this->insert(ft::make_pair(k, mapped_type()))).first)).second;
				}
				return _node->val.second;
			}

		///*	Modifiers
			ft::pair<iterator,bool> insert (const value_type& val)
			{
				// iterator it = find(val.first);
				node_ptr node = m_Tree.find(val);

				if (node != NULL)
					return (ft::make_pair(node, false));
				m_Tree.insert(val);
				iterator it = find(val.first);
				return (ft::make_pair(it, true));
			}
			iterator insert (iterator position, const value_type& val)
			{
				(void)position;
				m_Tree.insert(val);
				return (find(val.first));
			}
			template <class InputIterator>  void insert (InputIterator first, InputIterator last)
			{
				while (first != last)
				{
					m_Tree.insert(*first);
					first++;
				}
			}

			void erase (iterator position)
			{
				m_Tree.deleteNode(*position);
			}
			size_type erase (const key_type& k)
			{
				m_Tree.deleteByVal(k);
			}
			void erase (iterator first, iterator last)
			{
				while (first != last)
				{
					m_Tree.deleteNode(*first);
					first++;
				}
			}

			void swap (map& other)
			{
				if ((this != &other))
				{
					ft::swap(get_allocator(), other.get_allocator());
					m_Tree.swap(other.m_Tree);
				}
			}

			void clear()	{	m_Tree.clear();	}

		///* Observers
			key_compare key_comp() const {	return m_Tree.key_comp();	}

			value_compare value_comp() const	{	return m_Compare;	}

		///* Operations
			iterator find (const key_type& k)
			{
				return  m_Tree.search(ft::make_pair(k, mapped_type()));
			}
			const_iterator find (const key_type& k) const
			{
				return  m_Tree.search(ft::make_pair(k, mapped_type()));
			}

			size_type count (const key_type& k) const
			{
				iterator it = m_Tree.find(k);
				return ( it != NULL );
			}

			iterator lower_bound (const key_type& k)
			{
				return m_Tree.lower_bound(k);
			}
			const_iterator lower_bound (const key_type& k) const
			{
				return m_Tree.lower_bound(k);
			}

			iterator upper_bound (const key_type& k)
			{
				return m_Tree.upper_bound(k);
			}
			const_iterator upper_bound (const key_type& k) const
			{
				return m_Tree.upper_bound(k);
			}

			ft::pair<iterator,iterator> equal_range (const key_type& k)
			{
				return ft::pair<iterator, iterator>(lower_bound(k), upper_bound(k));
			}
			ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const
			{
				return ft::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
			}

		///* Allocator
			allocator_type get_allocator() const	{ return m_Allocate; }
	};

	template< class Key, class T, class Compare, class Alloc >
	bool operator==	( 	const std::map<Key, T, Compare, Alloc>& a,
						const std::map<Key, T, Compare, Alloc>& b )
	{
		return a.size() == b.size() && ft::equal(a.begin(), a.end(), b.begin());
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const std::map<Key, T, Compare, Alloc>& a,
					const std::map<Key, T, Compare, Alloc>& b )
		{	return !(a == b);	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const std::map<Key, T, Compare, Alloc>& a,
					const std::map<Key, T, Compare, Alloc>& b )
	{
		return ft::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const std::map<Key, T, Compare, Alloc>& a,
					const std::map<Key, T, Compare, Alloc>& b )
		{	return !(b < a);	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const std::map<Key, T, Compare, Alloc>& a,
					const std::map<Key, T, Compare, Alloc>& b )
		{	return (b < a);		}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const std::map<Key, T, Compare, Alloc>& a,
					const std::map<Key, T, Compare, Alloc>& b )
		{	return !(a < b);	}

}//namespace ft

