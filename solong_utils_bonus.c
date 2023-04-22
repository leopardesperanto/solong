/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phebert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:54:28 by phebert           #+#    #+#             */
/*   Updated: 2023/02/10 12:54:32 by phebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"
#include "minilibx-linux/mlx.h"
#include "minilibx-linux/mlx_int.h"
#include "libft/libft.h"

void	put_color(t_data *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)pixel = color;
}

void	tableau_ber(t_vars *vars)
{
	int	k;

	k = 0;
	vars->ber.tabulo = malloc(sizeof(char *) * vars->ber.largeur);
	if (!vars->ber.tabulo)
	{
		perror ("Error\nEchec du malloc");
		exit(0);
	}
	while (k < vars->ber.largeur)
	{
		(vars->ber.tabulo)[k] = malloc(sizeof(char) * vars->ber.hauteur + 1);
		if (!vars->ber.tabulo[k])
		{
			perror ("Error\nEchec du malloc");
			libere_memoire(vars, k, 1);
			exit(0);
		}
		k++;
	}
}

t_ber	taille_ber(char *carte_ber)
{
	int		fd;
	t_ber	ber;
	char	*ligne;

	ber.erreur = 0;
	fd = open(carte_ber, O_RDONLY);
	if (fd < 0)
	{
		perror("Error\nErreur0 carte illisible");
		exit(0);
	}
	ligne = get_next_line(fd);
	ber.largeur = ft_strlen(ligne) - 1;
	ber.hauteur = 0;
	while (ligne)
	{
		ber.hauteur++;
		free (ligne);
		ligne = get_next_line(fd);
		if (ligne && (size_t)ber.largeur != ft_strlen(ligne) - 1)
			ber.erreur = 1;
	}
	close(fd);
	return (ber);
}

int	ferme_fenetre(t_vars *vars)
{
	libere_memoire(vars, vars->ber.largeur, 2);
	mlx_destroy_image(vars->mlx, vars->canvas[0].img);
	mlx_destroy_image(vars->mlx, vars->canvas[1].img);
	mlx_destroy_image(vars->mlx, vars->canvas[2].img);
	mlx_destroy_image(vars->mlx, vars->canvas[3].img);
	mlx_destroy_image(vars->mlx, vars->canvas[4].img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit (0);
}

int	reagit_clavier(int keycode, t_vars *vars)
{
	bouge_personnage(keycode, vars);
	if (keycode != 65307)
		return (0);
	ferme_fenetre(vars);
	exit (0);
}
