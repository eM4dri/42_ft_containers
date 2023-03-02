# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/22 10:53:31 by emadriga          #+#    #+#              #
#    Updated: 2023/03/02 14:50:22 by emadriga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program's name
NAME	= containers

# compiler
GCC		= clang++

# compiling flags
FLAGS	= -Wall -Wextra -Werror $(VERSION) $(SANITIZE) -g -O3 -pedantic  $(SHOW_CONS_DEST)

# sanitize
SANITIZE =
# SANITIZE = -fsanitize=address

# version
VERSION = -std=c++98

# Print constructor & destructor
SHOW_CONS_DEST =
# SHOW_CONS_DEST = -D SHOW_CONS_DEST

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
					utils/is_integral.hpp					\
					utils/enable_if.hpp						\
					utils/equal.hpp							\
					utils/pair.hpp							\
					utils/swap.hpp							\
					utils/lexicographical_compare.hpp		\
					test/testCompare.hpp					\
					test/testVector.hpp						\
					test/testMap.hpp						\
					test/testSet.hpp						\
					test/testCommon.hpp						\
					test/testStack.hpp						\
					test/Fixed.hpp							\
					utils/Log.hpp

# Source and object files
SRC_FILES	= 	main.cpp							\
				test/testCompare.cpp				\
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
