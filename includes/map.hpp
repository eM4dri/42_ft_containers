/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:11:15 by emadriga          #+#    #+#             */
/*   Updated: 2023/03/07 18:01:14 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "tree/red_black_tree.hpp"
#include "utility/equal.hpp"

namespace ft{
	template <	typename Key,												// map::key_type
				typename T,													// map::mapped_type
				typename Compare = std::less<Key>,							// map::key_compare
				typename Alloc = std::allocator<std::pair<const Key,T> >	// map::allocator_type
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
			typedef struct valueCompare
			{   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
				// friend class map;
				key_compare comp;
				valueCompare (key_compare c) : comp(c) {}  // constructed with map's comparison object
			public:
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			}value_compare;



			typedef ft::red_black_tree<	key_type,
										value_type,
										map_get_key<key_type, value_type>,
										key_compare,
										allocator_type
										>							tree_type;
			typedef typename tree_type::node_ptr					node_ptr;

			allocator_type			m_Allocate;
			value_compare			m_Compare;
#ifdef LOGTREE // log red_black_tree
		public:
#endif
			tree_type				m_Tree;

		public:
			typedef typename tree_type::iterator					iterator;
			typedef typename tree_type::const_iterator				const_iterator;
			typedef typename tree_type::reverse_iterator			reverse_iterator;
			typedef typename tree_type::const_reverse_iterator		const_reverse_iterator;

		public:
		///*	Member functions
			explicit map (  const key_compare& comp = key_compare(),
							const allocator_type& alloc = allocator_type())
				:	m_Allocate(alloc), m_Compare(comp), m_Tree() {};

			template <typename InputIterator>
			map (   InputIterator first,
					InputIterator last,
					const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type())
				:	m_Allocate(alloc), m_Compare(comp), m_Tree()
				{	insert(first, last);	};

			map (const map& copy)
				:	m_Allocate(copy.m_Allocate), m_Compare(copy.m_Compare)
				{	operator=(copy);	}

			~map()	{ }

			map& operator= (const map & assign )
			{
				if (this != &assign)
				{
					if (empty() == false)
						m_Tree.clear();
					insert(assign.begin(), assign.end());
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
				node_ptr _node = m_Tree.find(ft::make_pair(k, mapped_type()));

				if (!_node)
				{
					return  (*((this->insert(ft::make_pair(k, mapped_type()))).first)).second;
				}
				return _node->val.second;
			}

		///*	Modifiers
			ft::pair<iterator,bool> insert (const value_type& val)
			{
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
			template <typename InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				while (first != last)
				{
					m_Tree.insert(*first);
					first++;
				}
			}

			void erase (iterator position)
			{
				m_Tree.deleteByVal(*position);
			}
			size_type erase (const key_type& k)
			{
				iterator it = find(k);
				if (it == end())
					return 0;
				erase(it);
				return 1;
			}
			void erase (iterator first, iterator last)
			{
				m_Tree.eraseMapRange(first, last);
			}

			void swap (map& other)
			{
				if ((this != &other))
				{
					ft::swap(m_Allocate, other.m_Allocate);
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
				node_ptr node = m_Tree.find(ft::make_pair(k, mapped_type()));
				if (node != NULL)
					return iterator(node);
				return  end();
			}
			const_iterator find (const key_type& k) const
			{
				node_ptr node = m_Tree.find(ft::make_pair(k, mapped_type()));
				if (node != NULL)
					return iterator(node);
				return  end();
			}

			size_type count (const key_type& k) const
			{
				return ( m_Tree.find(value_type(k, mapped_type())) != NULL );
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

	template< typename Key, typename T, typename Compare, typename Alloc >
	bool operator==	( 	const ft::map<Key, T, Compare, Alloc>& a,
						const ft::map<Key, T, Compare, Alloc>& b )
	{
		return a.size() == b.size() && ft::equal(a.begin(), a.end(), b.begin());
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	bool operator!=( const ft::map<Key, T, Compare, Alloc>& a,
					const ft::map<Key, T, Compare, Alloc>& b )
		{	return !(a == b);	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	bool operator<( const ft::map<Key, T, Compare, Alloc>& a,
					const ft::map<Key, T, Compare, Alloc>& b )
	{
		return ft::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	bool operator<=( const ft::map<Key, T, Compare, Alloc>& a,
					const ft::map<Key, T, Compare, Alloc>& b )
		{	return !(b < a);	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	bool operator>( const ft::map<Key, T, Compare, Alloc>& a,
					const ft::map<Key, T, Compare, Alloc>& b )
		{	return (b < a);		}

	template< typename Key, typename T, typename Compare, typename Alloc >
	bool operator>=( const ft::map<Key, T, Compare, Alloc>& a,
					const ft::map<Key, T, Compare, Alloc>& b )
		{	return !(a < b);	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	void swap( ft::map<Key,T,Compare,Alloc>& a,
			ft::map<Key,T,Compare,Alloc>& b )
		{	return a.swap(b);	}

}//namespace ft

