/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phebert <emploi.hebert@laposte.net>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:51:29 by phebert           #+#    #+#             */
/*   Updated: 2023/02/10 12:51:33 by phebert          ###   ########.fr       */
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
	write (1, "Nombre de mouvement: ", 21);
	write (1, nbr1, ft_strlen(nbr1));
	write (1, "\n", 1);
	write (1, "Nombre d'objets restant: ", 25);
	write (1, nbr2, ft_strlen(nbr2));
	write (1, "\n", 1);
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
