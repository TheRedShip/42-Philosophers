/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:19:19 by ycontre           #+#    #+#             */
/*   Updated: 2024/01/05 20:05:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_putstr(int fd, char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(fd, str, i);
}

int	ft_atoi(char *str)
{
	int	final_result;
	int	i;
	int	sign;

	if (!str)
		return (0);
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	final_result = 0;
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		final_result = final_result * 10 + (str[i] - 48);
		i++;
	}
	return (final_result * sign);
}

void	kill_pid(t_glob *glob)
{
	int	i;

	i = 0;
	while (glob->pids[i] > 0)
	{
		kill(glob->pids[i], SIGKILL);
		i++;
	}
}

void	clear_data(t_glob *glob)
{
	kill_pid(glob);
	if (glob && glob->pids)
		free(glob->pids);
	if (glob)
		free(glob);
}

void	error_exit(t_glob *glob)
{
	clear_data(glob);
	ft_putstr(2, "An error happenned.\n");
	exit(EXIT_FAILURE);
}
