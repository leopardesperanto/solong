/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong_utils5_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phebert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:52:17 by phebert           #+#    #+#             */
/*   Updated: 2023/02/10 12:53:05 by phebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"
#include "minilibx-linux/mlx.h"
#include "minilibx-linux/mlx_int.h"
#include "libft/libft.h"

void	ecrit_nbr(t_vars *vars)
{
	char	*nbr1;
	char	*nbr2;

	nbr1 = ft_itoa(vars->mouvement);
	nbr2 = ft_itoa(vars->ber.collectible);
	mlx_put_image_to_window(vars->mlx, vars->win,
		vars->canvas[4].img, 0, 0);
	mlx_string_put(vars->mlx, vars->win, 0, 40, 0x00FF00,
		"Mouvement: ");
	mlx_string_put(vars->mlx, vars->win, 50, 50, 0xFFFFFF, nbr1);
	mlx_string_put(vars->mlx, vars->win, 0, 60, 0x00FF00,
		"Objets restant: ");
	mlx_string_put(vars->mlx, vars->win, 50, 70, 0xFFFFFF, nbr2);
	free(nbr1);
	free(nbr2);
}

void	libere_memoire(t_vars *vars, int n, int t_tc)
{
	int	k;

	k = 0;
	while (k < n)
	{
		if (t_tc == 1)
			free(vars->ber.tabulo[k]);
		if (t_tc == 2)
			free(vars->ber.tabulo_clone[k]);
		k++;
	}
	if (t_tc == 1)
		free(vars->ber.tabulo);
	if (t_tc == 2)
	{
		free(vars->ber.tabulo_clone);
		libere_memoire(vars, vars->ber.largeur, 1);
	}
}
