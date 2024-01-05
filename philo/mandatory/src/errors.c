/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 14:44:36 by marvin            #+#    #+#             */
/*   Updated: 2023/12/16 14:44:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_handle_errors(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		ft_putstr(2, "Error: wrong number of arguments\n");
		return (0);
	}
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 200)
	{
		ft_putstr(2, "Error: wrong number of philosophers\n");
		return (0);
	}
	if (ft_atoi(argv[2]) <= 0 || ft_atoi(argv[3]) <= 0 || ft_atoi(argv[4]) <= 0)
	{
		ft_putstr(2, "Error: wrong time to die/eat/sleep\n");
		return (0);
	}
	if (argc == 6 && ft_atoi(argv[5]) < 1)
	{
		ft_putstr(2, "Error: wrong number of times each \
			philosopher must eat\n");
		return (0);
	}
	return (1);
}
