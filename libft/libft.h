/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phebert <emploi.hebert@laposte.net>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 09:57:49 by phebert           #+#    #+#             */
/*   Updated: 2022/11/11 09:58:21 by phebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <stddef.h>
# include "get_next_line.h"

char	*ft_itoa(int n);
char	*ft_strrchr(const char *str, int atrouver);
size_t	ft_strlen(const char *str);

#endif
