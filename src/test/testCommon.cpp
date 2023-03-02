/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testCommon.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:49:56 by emadriga          #+#    #+#             */
/*   Updated: 2023/03/02 14:49:30 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



# include "test/testCommon.hpp"

void performTest(std::string title, void (*f)())
{
    {
        std::cout << std::endl << "\tTest " << title << std::endl;
        std::cout << "###############################################" << std::endl;
    }
    {
        f();
    }
}

