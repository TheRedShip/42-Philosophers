/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:19:19 by ycontre           #+#    #+#             */
/*   Updated: 2023/12/18 16:07:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void ft_putstr(int fd, char *str)
{
	int i;

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

void clear_data(t_glob *glob)
{
	int	i;

	i = -1;
	while (++i < glob->philo_num)
	{
		// pthread_mutex_destroy(&(glob->forks[i]));
		// pthread_mutex_destroy(&(glob->philo[i].lock));
	}
	// pthread_mutex_destroy(&(glob->lock));

	if (glob && glob->philo)
		free(glob->philo);
	if (glob && glob->forks)
		free(glob->forks);
	if (glob)
		free(glob);
}

void error_exit(t_glob *glob)
{
	pthread_mutex_lock(&(glob->lock)); 
	clear_data(glob);
	ft_putstr(2, "An error happenned.\n");
	exit(EXIT_FAILURE);
}