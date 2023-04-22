/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phebert <emploi.hebert@laposte.net>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:07:03 by phebert           #+#    #+#             */
/*   Updated: 2022/11/30 10:07:07 by phebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

// 4 dans le get next line

int				verif_retour_ligne(char *str);
char			*get_next_line(int fd);
char			*obtient_ligne(int fd, char *buf, char *var_statique);
char			*termine_ligne(char *ligne, char *buf);

// 4 dans le get next line utils

char			*str_attache(char const *s1, char const *s2);
char			*ajoute_var_statique(char *ligne, char *var_statique);
char			*reduit_statique(char *var_statique);
size_t			str_longueur(const char *str);

#endif
