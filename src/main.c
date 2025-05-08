/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:12:22 by dderny            #+#    #+#             */
/*   Updated: 2025/05/08 15:16:34 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	main(void)
{
	char	*str;

	str = ft_xalloc(10, 0);
	if (!str)
	{
		ft_putstr_fd("Allocation failed\n", 2);
		return (1);
	}
	ft_strlcpy(str, "Hello", 10);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("\n", 1);
	//ft_free(str);

	str = ft_xalloc(20, 0);
	if (!str)
	{
		ft_putstr_fd("Allocation failed\n", 2);
		return (1);
	}
	ft_strlcpy(str, "World", 20);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("\n", 1);
	//ft_free(str);
	return (0);
}
