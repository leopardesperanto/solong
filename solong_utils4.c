/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phebert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:50:55 by phebert           #+#    #+#             */
/*   Updated: 2023/02/10 12:51:05 by phebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"
#include "minilibx-linux/mlx.h"
#include "minilibx-linux/mlx_int.h"
#include "libft/libft.h"

void	victoire(t_vars *vars)
{
	write(1, "La partie est finie tu as gagne ", 32);
	write(1, "appuie sur esc ou sur la croix\n", 31);
	vars->ber.tabulo[vars->x_perso - 1][vars->y_perso] = '1';
	vars->ber.tabulo[vars->x_perso + 1][vars->y_perso] = '1';
	vars->ber.tabulo[vars->x_perso][vars->y_perso - 1] = '1';
	vars->ber.tabulo[vars->x_perso][vars->y_perso + 1] = '1';
	mlx_put_image_to_window(vars->mlx, vars->win, vars->canvas[3].img,
		100 * vars->x_perso, 100 * vars->y_perso);
	mlx_string_put(vars->mlx, vars->win, 100 * vars->x_perso + 20,
		100 * vars->y_perso + 30, 0x000000, "VICTOIRE");
	mlx_string_put(vars->mlx, vars->win, 100 * vars->x_perso + 20,
		100 * vars->y_perso + 50, 0x000000, "Appuie ESC");
	mlx_string_put(vars->mlx, vars->win, 100 * vars->x_perso + 20,
		100 * vars->y_perso + 70, 0x000000, "pour QUITTER");
}

int	format_ber(char *str)
{
	int	format_valide;

	format_valide = 0;
	if (ft_strlen(str) >= 5)
	{
		if (ft_strrchr(str, '.') == &str[ft_strlen(str) - 4]
			&& ft_strrchr(str, 'b') == &str[ft_strlen(str) - 3]
			&& ft_strrchr(str, 'e') == &str[ft_strlen(str) - 2]
			&& ft_strrchr(str, 'r') == &str[ft_strlen(str) - 1])
			format_valide = 1;
	}
	return (format_valide);
}

void	modifie_clone(t_vars *vars)
{
	int	x;
	int	y;
	int	s;

	s = 0;
	while (s < (vars->ber.largeur - 2) * (vars->ber.hauteur - 2))
	{
		x = 1;
		while (x < vars->ber.largeur - 1)
		{
			y = 1;
			while (y < vars->ber.hauteur -1)
			{
				if (voisin_accessible(vars, x, y)
					&& (vars->ber.tabulo_clone[x][y] == '0'
					|| vars->ber.tabulo_clone[x][y] == 'C'))
					vars->ber.tabulo_clone[x][y] = 'X';
				y++;
			}
			x++;
		}
		s++;
	}
}

int	voisin_accessible(t_vars *vars, int x, int y)
{
	int	accessible;

	accessible = 0;
	if (vars->ber.tabulo_clone[x - 1][y] == 'X'
		|| vars->ber.tabulo_clone[x - 1][y] == 'P')
		accessible = 1;
	if (vars->ber.tabulo_clone[x + 1][y] == 'X'
		|| vars->ber.tabulo_clone[x + 1][y] == 'P')
		accessible = 1;
	if (vars->ber.tabulo_clone[x][y - 1] == 'X'
		|| vars->ber.tabulo_clone[x][y - 1] == 'P')
		accessible = 1;
	if (vars->ber.tabulo_clone[x][y + 1] == 'X'
		|| vars->ber.tabulo_clone[x][y + 1] == 'P')
		accessible = 1;
	return (accessible);
}

void	verif_chemin(t_vars *vars)
{
	int	x;
	int	y;

	modifie_clone(vars);
	x = 1;
	while (x < vars->ber.largeur - 1)
	{
		y = 1;
		while (y < vars->ber.hauteur -1)
		{
			if (vars->ber.tabulo_clone[x][y] == 'C')
				vars->ber.erreur = 6;
			if (vars->ber.tabulo_clone[x][y] == 'E'
					&& !voisin_accessible(vars, x, y)
					&& vars->ber.erreur != 6)
				vars->ber.erreur = 7;
			if (vars->ber.tabulo_clone[x][y] == 'E'
					&& !voisin_accessible(vars, x, y)
					&& vars->ber.erreur == 6)
				vars->ber.erreur = 8;
			y++;
		}
		x++;
	}
	message_erreur(vars);
}
