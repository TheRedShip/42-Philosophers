/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 14:38:46 by marvin            #+#    #+#             */
/*   Updated: 2023/12/16 14:38:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_forks(t_glob *glob)
{
	int	i;

	glob->forks = malloc(sizeof(pthread_mutex_t) * glob->fork_num);
	if (!glob->forks)
		error_exit(glob);
	i = -1;
	while (++i < glob->philo_num)
		pthread_mutex_init(&(glob->forks[i]), NULL);
	i = 0;
	glob->philo[0].left_fork = &glob->forks[0];
	glob->philo[0].right_fork = &glob->forks[glob->philo_num - 1];
	i = 1;
	while (i < glob->philo_num)
	{
		glob->philo[i].left_fork = &glob->forks[i];
		glob->philo[i].right_fork = &glob->forks[i - 1];
		i++;
	}
	return (0);
}

void	init_philo(t_glob *glob)
{
	int	i;

	glob->philo = malloc(sizeof(t_philo) * glob->philo_num);
	if (!glob->philo)
		error_exit(glob);
	i = 0;
	while (i < glob->philo_num)
	{
		glob->philo[i].glob = glob;
		glob->philo[i].id = i;
		glob->philo[i].time_to_die = glob->time_to_die;
		glob->philo[i].eaten_time = 0;
		glob->philo[i].status = 0;

		pthread_mutex_init(&(glob->philo[i].lock), NULL);
		i++;
	}
}

t_glob init_glob(char **argv, int argc)
{
	t_glob glob;

	glob.philo_num = ft_atoi(argv[1]);
	glob.time_to_die = ft_atoi(argv[2]);
	glob.time_to_eat = ft_atoi(argv[3]);
	glob.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		glob.must_eat = ft_atoi(argv[5]);
	else
		glob.must_eat = -1;
	glob.fork_num = glob.philo_num;
	glob.dead = 0;
	init_philo(&glob);
	init_forks(&glob);
	return (glob);

}