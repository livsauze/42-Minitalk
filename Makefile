# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: livsauze <livsauze@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/29 20:25:44 by livsauze          #+#    #+#              #
#    Updated: 2024/02/14 19:02:38 by livsauze         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UTILS_SRC = utils/utils_server.c utils/utils_common.c utils/printf/ft_printf.c utils/printf/ft_utils.c utils/printf/ft_utils2.c
SERVER_SRC = ${UTILS_SRC} server.c
CLIENT_SRC = ${UTILS_SRC} client.c
HEADER = include/minitalk.h

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

server : ${HEADER} ${SERVER_SRC}
	${CC} ${CFLAGS} ${SERVER_SRC} -o server
	
client : ${HEADER} ${CLIENT_SRC}
	${CC} ${CFLAGS} ${CLIENT_SRC} -o client

all : server client

clean : fclean

fclean :
	rm -f server client

re : fclean all

.PHONY : all clean fclen re 

.DEFAULT_GOAL := all
