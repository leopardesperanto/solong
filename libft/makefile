
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phebert <emploi.hebert@laposte.net>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/09 10:25:23 by phebert           #+#    #+#              #
#    Updated: 2022/11/09 10:25:36 by phebert          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NOM = libft.a

SRC = ft_strlen.c ft_strrchr.c ft_itoa.c \
get_next_line.c get_next_line_utils.c \

OBJ = $(SRC:.c=.o)

DRAPEAU = -Wall -Wextra -Werror

tout: $(NOM)

%.o: %.c
	cc $(DRAPEAU) -c $(SRC)

$(NOM): $(OBJ)
	 ar rcs $(NOM) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NOM)

re: fclean tout

.PHONY: re tout clean fclean

so:
	cc $(DRAPEAU) -c $(SRC)
	cc -shared -o libft.so $(OBJ)
