# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eel-moun <eel-moun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/21 16:03:09 by eel-moun          #+#    #+#              #
#    Updated: 2022/04/21 16:06:56 by eel-moun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra

all:
	${CC} ${CFLAGS} server.c -o server
	${CC} ${CFLAGS} client.c -o client

bonus:
	${CC} ${CFLAGS} server_bonus.c -o server_bonus
	${CC} ${CFLAGS} client_bonus.c -o client_bonus

clean:
	rm -rf server server_bonus
	rm -rf client client_bonus

fclean: clean

re: clean all

.PHONY: all bonus clean fclean re
