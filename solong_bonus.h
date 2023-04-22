/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phebert <emploi.hebert@laposte.net>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:57:16 by phebert           #+#    #+#             */
/*   Updated: 2023/02/10 12:57:24 by phebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLONG_BONUS_H
# define SOLONG_BONUS_H

typedef struct s_ber
{
	int		collectible;
	int		largeur;
	int		hauteur;
	int		erreur;
	int		x_sortie;
	int		y_sortie;
	char	**tabulo;
	char	**tabulo_clone;
}	t_ber;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_data;

typedef struct s_var
{
	t_ber	ber;
	void	*mlx;
	void	*win;
	t_data	canvas[5];
	int		x_perso;
	int		y_perso;
	int		mouvement;
}	t_vars;
// Dans solong_utils5_bonus.c

void	ecrit_nbr(t_vars *vars);
void	libere_memoire(t_vars *vars, int n, int t_tc);

// Dans solong_utils4_bonus.c

int		format_ber(char *str);
int		voisin_accessible(t_vars *vars, int x, int y);
void	modifie_clone(t_vars *vars);
void	victoire(t_vars *vars);
void	verif_chemin(t_vars *vars);

// Dans solong_utils3_bonus.c

void	canvas_img_addr(t_vars *v);
void	autorise_sortie(t_vars *vars);
void	tableau_clone(t_vars *vars);
void	verif2345678(t_vars *v);
void	verif_doublon(t_vars *vars);

// Dans solong_utils2_bonus.c

void	caractere_invalide(t_vars *vars);
void	verif_pourtour(t_vars *vars);
void	dessine_case(t_vars *vars, int l, int c, char *linio);
int		message_erreur(t_vars *v);
int		compte_collectibles(t_vars *vars);

// Dans solong_utils_bonus.c

void	put_color(t_data *img, int x, int y, int color);
void	tableau_ber(t_vars *vars);
t_ber	taille_ber(char *carte_ber);
int		ferme_fenetre(t_vars *vars);
int		reagit_clavier(int keycode, t_vars *vars);

// Dans solong_bonus.c

void	dessine_perso(t_vars *vars, int mvt);
void	bouge_personnage(int touche, t_vars *vars);
void	dessine_couleur(t_vars *vars, int couleur, int nbr);
int		draw_background(t_vars *vars, char *carte_ber);
int		main(int ac, char **av);

#endif
