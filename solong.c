/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phebert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:48:50 by phebert           #+#    #+#             */
/*   Updated: 2023/02/10 12:49:01 by phebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "norminou.xpm"
#include "solong.h"
#include "minilibx-linux/mlx.h"
#include "minilibx-linux/mlx_int.h"
#include "libft/libft.h"

void	dessine_perso(t_vars *vars, int mvt)
{
	int		x;
	int		y;

	x = 100 * vars->x_perso;
	y = 100 * vars->y_perso;
	if (mvt != vars->mouvement)
		ecrit_nbr(vars);
	if (vars->ber.tabulo[vars->x_perso][vars->y_perso] == 'C')
	{
		vars->ber.collectible--;
		if (vars->ber.collectible == 0)
			autorise_sortie(vars);
		vars->ber.tabulo[vars->x_perso][vars->y_perso] = '0';
	}
	mlx_string_put(vars->mlx, vars->win, x + 48, y + 50, 0x000000, "O");
	mlx_string_put(vars->mlx, vars->win, x + 42, y + 60, 0x000000, "-|-");
	mlx_string_put(vars->mlx, vars->win, x + 45, y + 70, 0x000000, "/\\");
	if (vars->ber.x_sortie == x / 100 && vars->ber.y_sortie == y / 100)
		victoire(vars);
}

void	bouge_personnage(int touche, t_vars *vars)
{
	int		mvt;
	int		x;
	int		y;
	char	**t;

	t = vars->ber.tabulo;
	x = vars->x_perso;
	y = vars->y_perso;
	mvt = vars->mouvement;
	vars->mouvement++;
	mlx_put_image_to_window(vars->mlx, vars->win,
		vars->canvas[1].img, 100 * x, 100 * y);
	if (touche == 'w' && (t[x][y - 1] != '1') && (t[x][y - 1] != 'E'))
		vars->y_perso--;
	else if (touche == 's' && (t[x][y + 1] != '1') && (t[x][y + 1] != 'E'))
		vars->y_perso++;
	else if (touche == 'a' && (t[x - 1][y] != '1') && (t[x - 1][y] != 'E'))
		vars->x_perso--;
	else if (touche == 'd' && (t[x + 1][y] != '1') && (t[x + 1][y] != 'E'))
		vars->x_perso++;
	else
		vars->mouvement--;
	dessine_perso(vars, mvt);
}

void	dessine_couleur(t_vars *vars, int couleur, int nbr)
{
	int	x;
	int	y;
	int	r2;
	int	coul;

	y = 0;
	while (y < 100)
	{
		x = 0;
		while (x < 100)
		{
			r2 = (x - 50) * (x - 50) + (y - 50) * (y - 50);
			coul = (couleur - r2 / 10 * 65793) % 16777216;
			put_color(&vars->canvas[nbr], x, y, coul);
			x++;
		}
		y++;
	}
}

int	draw_background(t_vars *vars, char *carte_ber)
{
	int		fd;
	int		ligne;
	int		colonne;
	char	*linio;
	int	*haut=malloc(sizeof(int));*haut=10;
	int	*large=malloc(sizeof(int));*large=10;

	fd = open(carte_ber, O_RDONLY);
//	vars->canvas[0].img = mlx_xpm_file_to_image(vars->mlx, "norminou.xpm", large, haut);
//	vars->canvas[0].addr = mlx_get_data_addr(vars->canvas[0].img, &vars->canvas[0].bpp, &vars->canvas[0].line_len, &vars->canvas[0].endian);
	dessine_couleur(vars, 0x00808000, 0);
	dessine_couleur(vars, 0x00ff8000, 1);
	dessine_couleur(vars, 0x00ffff00, 2);
	ligne = 0;
	while (ligne < vars->ber.hauteur)
	{
		colonne = 0;
		linio = get_next_line(fd);
		while (colonne < vars->ber.largeur)
		{
			vars->ber.tabulo_clone[colonne][ligne] = linio[colonne];
			vars->ber.tabulo[colonne][ligne] = linio[colonne];
			dessine_case(vars, ligne, colonne, linio);
			colonne++;
		}
		free (linio);
		ligne++;
	}
	return (linio = get_next_line(fd), close(fd), 0);
}

int	main(int ac, char **av)
{
	t_vars	v;

	if (ac != 2)
		return (write(1, "entrez une seule carte au format .ber\n", 38), 1);
	if (!format_ber(av[1]))
		return (write(1, "la fichier n'est pas au format .ber\n", 36), 1);
	v.mouvement = 0;
	v.ber = taille_ber(av[1]);
	message_erreur(&v);
	tableau_ber(&v);
	tableau_clone(&v);
	v.ber.x_sortie = 0;
	v.ber.y_sortie = 0;
	v.mlx = mlx_init();
	v.win = mlx_new_window(v.mlx, v.ber.largeur * 100,
			v.ber.hauteur * 100, "testMLX");
	canvas_img_addr(&v);
	draw_background(&v, av[1]);
	verif2345678(&v);
	mlx_hook(v.win, DestroyNotify, StructureNotifyMask, ferme_fenetre, &v);
	mlx_hook(v.win, 2, 1L << 0, reagit_clavier, &v);
	return (mlx_loop(v.mlx), 0);
}
