/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phebert <emploi.hebert@laposte.net>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:50:28 by phebert           #+#    #+#             */
/*   Updated: 2023/02/10 12:50:34 by phebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"
#include "minilibx-linux/mlx.h"
#include "minilibx-linux/mlx_int.h"
#include "libft/libft.h"

void	dessine_case(t_vars *v, int ligne, int colonne, char *linio)
{
	int		c;
	int		l;

	c = 100 * colonne;
	l = 100 * ligne;
	if (linio[colonne] == '1')
		mlx_put_image_to_window(v->mlx, v->win, v->canvas[0].img, c, l);
	if (linio[colonne] == '0' || linio[colonne] == 'P' || linio[colonne] == 'C')
		mlx_put_image_to_window(v->mlx, v->win, v->canvas[1].img, c, l);
	if (linio[colonne] == 'E')
		mlx_put_image_to_window(v->mlx, v->win, v->canvas[2].img, c, l);
	if (linio[colonne] == 'P')
	{
		v->x_perso = colonne;
		v->y_perso = ligne;
		dessine_perso(v, v->mouvement);
	}
	if (linio[colonne] == 'C')
	{
		mlx_string_put(v->mlx, v->win, c + 42, l + 50, 0xFFFFFF, "***");
		mlx_string_put(v->mlx, v->win, c + 42, l + 55, 0xFFFFFF, "***");
		mlx_string_put(v->mlx, v->win, c + 42, l + 60, 0xFFFFFF, "***");
	}
}

int	message_erreur(t_vars *v)
{
	if (v->ber.erreur == 0)
		return (0);
	if (v->ber.erreur == 1)
	{
		perror ("Error\nErreur1 la carte n'est pas rectangle");
		exit (1);
	}
	if (v->ber.erreur == 2)
		perror ("Error\nErreur2 Le contour n'est pas fait de murs");
	if (v->ber.erreur == 3)
		perror ("Error\nErreur3 Il n'y a pas d'objets a recolter");
	if (v->ber.erreur == 4)
		perror ("Error\nErreur4 Il y a un type de case non prevu");
	if (v->ber.erreur == 5)
		perror ("Error\nEreur5 Nombre invalide de depart et/ou d'arrivee");
	if (v->ber.erreur == 6)
		perror ("Error\nEreur6 Il y a un objet innacessible");
	if (v->ber.erreur == 7)
		perror ("Error\nEreur7 La sortie est innacessible");
	if (v->ber.erreur == 8)
		perror ("Error\nEreur8 sortie + objet innacessibles");
	ferme_fenetre(v);
	return (v->ber.erreur);
}

void	verif_pourtour(t_vars *vars)
{
	int	i;
	int	j;
	int	h;
	int	l;

	i = 0;
	while (i < vars->ber.largeur)
	{
		j = 0;
		while (j < vars->ber.hauteur)
		{
			h = vars->ber.hauteur - 1;
			l = vars->ber.largeur - 1;
			if (h && l && !((i % l) * (j % h)) && vars->ber.tabulo[i][j] != '1')
			{
				vars->ber.erreur = 2;
				message_erreur(vars);
			}
			j++;
		}
		i++;
	}
}

int	compte_collectibles(t_vars *vars)
{
	int	c;
	int	ligne;
	int	colonne;

	c = 0;
	ligne = 0;
	while (ligne < vars->ber.hauteur)
	{
		colonne = 0;
		while (colonne < vars->ber.largeur)
		{
			if (vars->ber.tabulo[colonne][ligne] == 'C')
				c++;
			colonne++;
		}
		ligne++;
	}
	if (!c)
	{
		vars->ber.erreur = 3;
		message_erreur(vars);
	}
	return (c);
}

void	caractere_invalide(t_vars *vars)
{
	int		ligne;
	int		colonne;
	char	c;

	ligne = 0;
	while (ligne < vars->ber.hauteur)
	{
		colonne = 0;
		while (colonne < vars->ber.largeur)
		{
			c = vars->ber.tabulo[colonne][ligne];
			if (c != 'C' && c != '1' && c != '0' && c != 'P' && c != 'E')
			{
				vars->ber.erreur = 4;
				message_erreur(vars);
			}
			if (c == 'E')
			{
				vars->ber.x_sortie = colonne;
				vars->ber.y_sortie = ligne;
			}
			colonne++;
		}
		ligne++;
	}
}
