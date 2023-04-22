/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phebert <emploi.hebert@laposte.net>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 10:42:16 by phebert           #+#    #+#             */
/*   Updated: 2022/11/25 10:42:26 by phebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*termine_ligne(char *ligne, char *buf)
{
	char	*ligne_finie;
	int		verif;
	size_t	k;
	int		j;

	k = 0;
	j = 0;
	verif = verif_retour_ligne(buf);
	if (verif != -1)
	{
		ligne_finie = malloc(sizeof(char) * (str_longueur(ligne) + verif + 2));
		if (!ligne_finie)
			return (NULL);
		while (k++ < str_longueur(ligne) + 1)
			ligne_finie[k - 1] = ligne[k - 1];
		while (k < str_longueur(ligne) + verif + 3)
		{
			ligne_finie[k - 2] = buf[j];
			j++;
			k++;
		}
		return (ligne_finie[k - 2] = '\0', free(ligne), ligne_finie);
	}
	return (ligne);
}

int	verif_retour_ligne(char *str)
{
	int	k;
	int	retour;

	retour = -1;
	k = 0;
	if (!str)
		return (retour);
	while (str[k])
	{
		if (str[k] == '\n')
			return (k);
		k++;
	}
	return (retour);
}

char	*obtient_ligne(int fd, char *buf, char *var_statique)
{
	char	*ligne;
	char	*l;
	ssize_t	nbr;

	ligne = malloc(1);
	if (!ligne)
		return (NULL);
	ligne[0] = '\0';
	ligne = ajoute_var_statique(ligne, var_statique);
	var_statique = reduit_statique(var_statique);
	if (verif_retour_ligne(ligne) != -1)
		return (ligne);
	nbr = read(fd, (void *)buf, BUFFER_SIZE);
	if (nbr == -1)
		return (ligne);
	buf[nbr] = '\0';
	while (verif_retour_ligne(buf) == -1 && nbr > 0)
	{
		l = ligne;
		ligne = str_attache(ligne, buf);
		free(l);
		nbr = read(fd, (void *)buf, BUFFER_SIZE);
		buf[nbr] = '\0';
	}
	return (termine_ligne(ligne, buf));
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*ligne;
	static char	*var_statique;
	char		*pointeur;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 4095)
		return (NULL);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	buf[0] = '\0';
	ligne = obtient_ligne(fd, buf, var_statique);
	pointeur = var_statique;
	buf = reduit_statique(buf);
	var_statique = str_attache(var_statique, buf);
	free (pointeur);
	free(buf);
	if (ligne[0] == '\0')
		return (free(ligne), free(var_statique), var_statique = NULL, NULL);
	return (ligne);
}
/*
#include <fcntl.h>

static int	ouvrirfichier(const char *nom)
{
	int	fd;

	fd = open(nom, O_RDONLY);
	printf("%i\n", fd);
	return (fd);
}

int	main(void)
{
	int		filedescripteur;
	char	*ligne;

	filedescripteur = ouvrirfichier((const char *)"test");
	ligne = get_next_line(filedescripteur);
	printf("ligne1\n%s\n", ligne);
	free(ligne);
	ligne = get_next_line(filedescripteur);
	printf("ligne2\n%s\n", ligne);
	free(ligne);
	ligne = get_next_line(filedescripteur);
	printf("ligne3\n%s\n", ligne);
	free(ligne);
	ligne = get_next_line(filedescripteur);
	printf("ligne4\n%s\n", ligne);
	free(ligne);
	ligne = get_next_line(filedescripteur);
	printf("ligne5\n%s\n", ligne);
	free(ligne);
	ligne = get_next_line(filedescripteur);
	printf("ligne6\n%s\n", ligne);
	free(ligne);
	close(filedescripteur);
}*/
