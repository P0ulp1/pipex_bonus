# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phautena <phautena@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/26 12:24:27 by phautena          #+#    #+#              #
#    Updated: 2024/09/12 12:18:32 by phautena         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = ./srcs/pipex.c ./srcs/pipex_build.c ./srcs/pipex_utils.c

CC = cc -Wall -Werror -Wextra -ggdb -g -I./includes/

OBJ = ${SRC:.c=.o}

LIBFT_ARCHIVE = ./Libft/libft.a

PRINTF_ARCHIVE = ./ft_printf/libftprintf.a

.c.o:
	${CC} -c $< -o $@

all: ${NAME}

${NAME}: ${LIBFT_ARCHIVE} ${PRINTF_ARCHIVE} ${OBJ}
	${CC} ${OBJ} ${LIBFT_ARCHIVE} ${PRINTF_ARCHIVE} -o ${NAME}

${LIBFT_ARCHIVE}:
	make -sC ./Libft

${PRINTF_ARCHIVE}:
	make -sC ./ft_printf

clean:
	make clean -sC ./Libft
	make clean -sC ./ft_printf
	rm -f ${OBJ}

fclean: clean
	make fclean -sC ./Libft
	make fclean -sC ./ft_printf
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
