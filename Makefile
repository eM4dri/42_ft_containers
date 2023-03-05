# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/22 10:53:31 by emadriga          #+#    #+#              #
#    Updated: 2023/03/05 14:32:26 by emadriga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program's name
NAME	= containers

# compiler
GCC		= clang++

FLAGS	= -Wall -Wextra -Werror $(VERSION) $(SANITIZE) -g -O3 -pedantic $(NAMESPACE) $(SHOW_CONS_DEST)

# compiling flags

# sanitize
SANITIZE =
# SANITIZE = -fsanitize=address

# version
VERSION = -std=c++98

# Namespace in use
NAMESPACE =

FT			= -D NS=ft  -D COMPARE
STD			= -D NS=std -D COMPARE
MORE		= -D PLUS
DEFAULT		=

# Print constructor & destructor
# SHOW_CONS_DEST =
SHOW_CONS_DEST =  -D SHOW_CONS_DEST

# Header files
INCLUDES_FILES =	vector.hpp								\
					map.hpp									\
					set.hpp									\
					stack.hpp								\
					iterators/iterator.hpp					\
					iterators/iterator_traits.hpp			\
					iterators/reverse_iterator.hpp			\
					iterators/random_access_iterator.hpp	\
					iterators/tree_iterator.hpp				\
					tree/red_black_tree.hpp					\
					tree/node.hpp							\
					utility/is_integral.hpp					\
					utility/enable_if.hpp					\
					utility/equal.hpp						\
					utility/pair.hpp						\
					utility/swap.hpp						\
					utility/copy.hpp						\
					utility/distance.hpp					\
					utility/lexicographical_compare.hpp		\
					test/testUtility.hpp					\
					test/testVector.hpp						\
					test/testMap.hpp						\
					test/testSet.hpp						\
					test/testCommon.hpp						\
					test/testStack.hpp						\
					test/Fixed.hpp							\
					utility/Log.hpp

# Source and object files
SRC_FILES	= 	main.cpp							\
				test/testUtility.cpp				\
				test/testVector.cpp					\
				test/testMap.cpp					\
				test/testSet.cpp					\
				test/testCommon.cpp					\
				test/testStack.cpp					\
				test/Fixed.cpp

OBJ_FILES	= $(SRC_FILES:.cpp=.o)

# Folders
INC_DIR = ./includes/
SRC_DIR = ./src/
OBJ_DIR = ./obj/

# Paths
INCLUDES = $(addprefix $(INC_DIR), $(INCLUDES_FILES))
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

# all rule
all: obj $(NAME)

std:	NAMESPACE += $(STD)
std:	re

ft:		NAMESPACE += $(FT)
ft:		re

default:		NAMESPACE += $(DEFAULT)
default:		SHOW_CONS_DEST += $(DEFAULT)
default:		re

more:			SHOW_CONS_DEST += $(MORE)
more:			re

obj:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)test/
$(OBJ_DIR)%.o:$(SRC_DIR)%.cpp $(INCLUDES)
	@$(GCC) $(FLAGS) -I $(INC_DIR) -o $@ -c $<

# Compiling
$(NAME): $(OBJ)
	@echo "\033[0;33mCompiling... Wait a sec.\033[0;39m"
	@$(GCC) $(OBJ) $(FLAGS) -lm -o $(NAME)
	@echo "\033[0;32m$(NAME) generated!\033[0;37m"

# clean rule
clean:
			@rm -Rf $(OBJ_DIR)
			@echo "\033[1;34m[INFO]\033[0m Objects removed!"

# fclean rule
fclean:		clean
			@rm -f $(NAME)
			@rm -f *_shrubbery
			@echo "$(NAME) removed!"

# re rule
re:			fclean all

# phony
.PHONY:		all clean fclean re
