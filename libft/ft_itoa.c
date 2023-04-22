/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phebert <emploi.hebert@laposte.net>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:53:34 by phebert           #+#    #+#             */
/*   Updated: 2022/11/15 14:53:55 by phebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	comptememoire(int n)
{
	int	memoire;

	if (n == 0)
		return (2);
	memoire = 1;
	if (n < 0)
		memoire++;
	while (n != 0)
	{
		memoire++;
		n = n / 10;
	}
	return (memoire);
}

/*
char	*racourcinombre(char *nbr)
{
	int	k;

	k = 1;
	while (nbr[k] == '0' && nbr[k + 1] != '\0')
		k++;
	if (nbr[0] == '+')
		ft_memmove(nbr, nbr + k, 12 - k);
	if (nbr[0] == '-')
		ft_memmove(nbr + 1, nbr + k, 12 - k);
	return (nbr);
}
*/
char	*ft_itoa(int n)
{
	int		k;
	long	nbr;
	char	*nbrenchiffre;

	nbr = n;
	k = comptememoire(n);
	nbrenchiffre = malloc(sizeof(char) * k);
	if (nbrenchiffre == NULL)
		return (NULL);
	k--;
	nbrenchiffre[k] = '\0';
	if (nbr < 0)
	{
		nbr = 0 - nbr;
		nbrenchiffre[0] = '-';
	}
	if (nbr == 0)
		nbrenchiffre[0] = '0';
	while (nbr != 0)
	{
		k--;
		nbrenchiffre[k] = nbr % 10 + 48;
		nbr = nbr / 10;
	}
	return (nbrenchiffre);
}
