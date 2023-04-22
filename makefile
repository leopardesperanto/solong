NOM = solong

SRC = solong.c solong_utils.c solong_utils2.c solong_utils3.c solong_utils4.c solong_utils5.c \
libft/get_next_line.c libft/get_next_line_utils.c

SRC_BONUS = solong_bonus.c solong_utils_bonus.c solong_utils2_bonus.c solong_utils3_bonus.c \
solong_utils4_bonus.c solong_utils5_bonus.c \
libft/get_next_line.c libft/get_next_line_utils.c

CC = clang
INCLIB = minilibx
CDRAPEAU = -Wall -Wextra -Werror
LDRAPEAU = -lmlx -lX11 -lXext -lm -lz

tout: $(NOM)

$(NOM):libft/libft.a $(SRC) solong.h
	$(CC) $(SRC) libft/libft.a -I$(INCLIB) -Lminilibx-linux $(CDRAPEAU) $(LDRAPEAU) -o $(NOM)

libft/libft.a:
	cd libft && make && cd ..

clean:
	cd libft && make clean && cd ..
fclean:
	cd libft && make fclean && cd ..
	rm -f $(NOM)
	rm -f $(NOM)_bonus

re: fclean $(NOM)

clear:
	clear

.PHONY: re tout clean fclean

test:
	norminette s*.c
	norminette s*.h
#	valgrind ./solong
#	valgrind ./solong yuweyfv
#	valgrind ./solong yuweyfv.ber
#	valgrind ./solong ewyufyi ojoojo
#	valgrind ./solong carte_valide.ber carte_valide2.ber
#	valgrind ./solong pas_rectangle.ber
#	valgrind ./solong carte_vide.ber
#	valgrind ./solong un_un.ber
#	valgrind ./solong erreur_mur.ber
#	valgrind ./solong rien_a_recolter.ber
#	valgrind ./solong element_non_prevu.ber
#	valgrind ./solong doublon.ber
#	valgrind ./solong sortie_innacessible.ber
	valgrind ./solong carte_valide.ber
	valgrind ./solong_bonus carte_valide.ber
	valgrind ./solong carte_valide2.ber
	valgrind ./solong_bonus carte_valide2.ber
	valgrind ./solong carte_valide_spirale.ber
	valgrind ./solong_bonus carte_valide_spirale.ber

solong_bonus:libft/libft.a $(SRC_BONUS)
	$(CC) $(SRC_BONUS) libft/libft.a -I$(INCLIB) -Lminilibx-linux $(CDRAPEAU) $(LDRAPEAU) -o $(NOM)_bonus

bonus: solong_bonus
