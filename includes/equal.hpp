/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   equal.hpp									  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: emadriga <emadriga@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/06/27 20:51:21 by emadriga		  #+#	#+#			 */
/*   Updated: 2023/02/06 18:15:44 by emadriga		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#pragma once

namespace ft
{
	template <class InputIterator1, class InputIterator2>
	bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
	{
		while (first1!=last1) {
			if (!(*first1 == *first2))   // or: if (!pred(*first1,*first2)), for version 2
				return false;
			++first1; ++first2;
		}
		return true;
	}

}//namespace ft
