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

void init_semaphore(t_glob *glob)
{
	sem_t *sem;
	
	sem_unlink("died");
	sem_unlink("forks");

	sem = sem_open("died", O_CREAT, 0777, 0);
	if (sem == SEM_FAILED)
		error_exit(glob);
	sem_close(sem);
	sem = sem_open("forks", O_CREAT, 0777, glob->philo_num);
	if (sem == SEM_FAILED)
		error_exit(glob);
	sem_close(sem);
}

int	born_philo(t_philo philo)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		philo.last_meal = -1;
		philo.eaten_time = 0;
		philo.status = 0;
		// printf("Philosopher %d is born at %ld\n", philo.id, philo.start_time);
		calcul_philo(philo);
		exit(0);
	}
	return (pid);
}

void init_philos(t_glob *glob)
{
	int	i;
	t_philo	philo;
	u_int64_t	start_time;

	glob->pids = malloc(sizeof(int) * (glob->philo_num + 1));
	if (!glob->pids)
		error_exit(glob);
	glob->pids[glob->philo_num] = 0;
	i = 0;
	start_time = get_time();
	while (i < glob->philo_num)
	{
		philo.id = i + 1;
		philo.start_time = start_time;
		philo.time_to_eat = glob->time_to_eat;
		philo.time_to_die = glob->time_to_die;
		philo.time_to_sleep = glob->time_to_sleep;
		glob->pids[i] = born_philo(philo);
		if (glob->pids[i] == -1)
		{
			glob->pids[i] = 0;
			error_exit(glob);
		}
		ft_usleep(1);
		i++;
	}
}

t_glob *init_glob(char **argv, int argc)
{
	t_glob *glob;

	glob = malloc(sizeof(t_glob));
	if (!glob)
		exit(EXIT_FAILURE);
	glob->philo_num = ft_atoi(argv[1]);
	glob->time_to_die = ft_atoi(argv[2]);
	glob->time_to_eat = ft_atoi(argv[3]);
	glob->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		glob->must_eat = ft_atoi(argv[5]);
	else
		glob->must_eat = -1;
	init_semaphore(glob);
	init_philos(glob);
	return (glob);
}