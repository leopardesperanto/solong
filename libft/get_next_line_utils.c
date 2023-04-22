/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phebert <emploi.hebert@laposte.net>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:08:43 by phebert           #+#    #+#             */
/*   Updated: 2022/11/30 10:08:48 by phebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <stddef.h>

char	*reduit_statique(char *var_statique)
{
	int	verif;
	int	k;

	k = 0;
	if (!var_statique)
		return (var_statique);
	verif = verif_retour_ligne(var_statique);
	if (verif >= 0)
	{
		while (var_statique[k + 1 + verif])
		{
			var_statique[k] = var_statique[k + 1 + verif];
			k++;
		}
		var_statique[k] = '\0';
	}
	else
		var_statique[0] = '\0';
	return (var_statique);
}

size_t	str_longueur(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (*(str + i) != '\0')
		i++;
	return (i);
}

char	*str_attache(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	s = malloc((sizeof(char)) * (str_longueur(s1) + str_longueur(s2) + 1));
	if (s == NULL)
		return (NULL);
	if (!s1)
		s1 = "";
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	j = 0;
	if (!s2)
		s2 = "";
	while (s2[j])
	{
		s[i + j] = s2[j];
		j++;
	}
	s[i + j] = '\0';
	return (s);
}

char	*ajoute_var_statique(char *ligne, char *var_statique)
{
	char	*pointeur;
	int		verif;

	if (!var_statique)
		return (ligne);
	verif = verif_retour_ligne(var_statique);
	if (verif == -1)
	{
		pointeur = ligne;
		ligne = str_attache(ligne, var_statique);
		free(pointeur);
		return (ligne);
	}
	return (termine_ligne(ligne, var_statique));
}
