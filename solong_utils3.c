/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phebert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:50:41 by phebert           #+#    #+#             */
/*   Updated: 2023/02/10 12:50:44 by phebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"
#include "minilibx-linux/mlx.h"
#include "minilibx-linux/mlx_int.h"
#include "libft/libft.h"

void	verif_doublon(t_vars *vars)
{
	int		ligne;
	int		colonne;
	int		p;
	int		e;

	p = 0;
	e = 0;
	ligne = 0;
	while (ligne < vars->ber.hauteur)
	{
		colonne = 0;
		while (colonne < vars->ber.largeur)
		{
			if (vars->ber.tabulo[colonne][ligne] == 'P')
				p++;
			if (vars->ber.tabulo[colonne][ligne] == 'E')
				e++;
			colonne++;
		}
		ligne++;
	}
	if (p != 1 || e != 1)
		vars->ber.erreur = 5;
	message_erreur(vars);
}

void	verif2345678(t_vars *v)
{
	verif_pourtour(v);
	v->ber.collectible = compte_collectibles(v);
	caractere_invalide(v);
	verif_doublon(v);
	verif_chemin(v);
}

void	tableau_clone(t_vars *vars)
{
	int	k;

	k = 0;
	vars->ber.tabulo_clone = malloc(sizeof(char *) * vars->ber.largeur);
	if (!vars->ber.tabulo_clone)
	{
		perror ("Error\nEchec du malloc clone");
		exit(0);
	}
	while (k < vars->ber.largeur)
	{
		(vars->ber.tabulo_clone)[k] = malloc(sizeof(char)
				* vars->ber.hauteur + 1);
		if (!vars->ber.tabulo_clone[k])
		{
			perror ("Error\nEchec du malloc clone");
			libere_memoire(vars, k, 2);
			exit(0);
		}
		k++;
	}
}

void	autorise_sortie(t_vars *vars)
{
	int	x;
	int	y;

	vars->ber.tabulo[vars->ber.x_sortie][vars->ber.y_sortie] = 'S';
	y = 0;
	while (y < 100)
	{
		x = 0;
		while (x < 100)
		{
			put_color(&vars->canvas[3], x, y, 0x00FFFF00);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->canvas[3].img,
		100 * vars->ber.x_sortie, 100 * vars->ber.y_sortie);
}

void	canvas_img_addr(t_vars *v)
{
	v->canvas[0].img = mlx_new_image(v->mlx, 100, 100);
	v->canvas[1].img = mlx_new_image(v->mlx, 100, 100);
	v->canvas[2].img = mlx_new_image(v->mlx, 100, 100);
	v->canvas[3].img = mlx_new_image(v->mlx, 100, 100);
	v->canvas[4].img = mlx_new_image(v->mlx, 100, 100);
	v->canvas[0].addr = mlx_get_data_addr(v->canvas[0].img,
			&v->canvas[0].bpp, &v->canvas[0].line_len, &v->canvas[0].endian);
	v->canvas[1].addr = mlx_get_data_addr(v->canvas[1].img,
			&v->canvas[1].bpp, &v->canvas[1].line_len, &v->canvas[1].endian);
	v->canvas[2].addr = mlx_get_data_addr(v->canvas[2].img,
			&v->canvas[2].bpp, &v->canvas[2].line_len, &v->canvas[2].endian);
	v->canvas[3].addr = mlx_get_data_addr(v->canvas[3].img,
			&v->canvas[3].bpp, &v->canvas[3].line_len, &v->canvas[3].endian);
	v->canvas[4].addr = mlx_get_data_addr(v->canvas[4].img,
			&v->canvas[4].bpp, &v->canvas[4].line_len, &v->canvas[4].endian);
}
