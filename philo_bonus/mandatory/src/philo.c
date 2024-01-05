/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:53:05 by ycontre           #+#    #+#             */
/*   Updated: 2024/01/05 20:02:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_message(t_philo *philo, char *message, int dead)
{
	sem_t	*sem;

	sem = sem_open("print", O_RDWR);
	sem_wait(sem);
	printf("%ld %d %s\n", get_time() - philo->start_time, philo->id, message);
	if (dead != 1)
		sem_post(sem);
	sem_close(sem);
}

void	try_cycle(t_philo *philo)
{
	sem_t	*sem;
	sem_t	*sem_eat;

	sem = sem_open("forks", O_RDWR);
	sem_wait(sem);
	print_message(philo, "has taken a fork", 0);
	sem_wait(sem);
	print_message(philo, "has taken a fork", 0);
	if (philo->eaten_time++ && philo->eaten_time == philo->must_eat)
	{
		sem_eat = sem_open("meal", O_RDWR);
		sem_post(sem_eat);
		sem_close(sem_eat);
	}
	philo->last_meal = get_time();
	philo->status = 1;
	print_message(philo, "is eating", 0);
	ft_usleep(philo->time_to_eat);
	philo->status = 0;
	sem_post(sem);
	sem_post(sem);
	print_message(philo, "is sleeping", 0);
	ft_usleep(philo->time_to_sleep);
	print_message(philo, "is thinking", 0);
	sem_close(sem);
}

void	*verify_philo_dead(void *philo_ptr)
{
	sem_t	*sem;
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	while (1)
	{
		if (get_time() >= philo->last_meal + philo->time_to_die \
			&& philo->status != 1)
		{
			print_message(philo, "died", 1);
			sem = sem_open("died", O_RDWR);
			sem_post(sem);
			sem_close(sem);
			return (NULL);
		}
	}
	return (NULL);
}

void	calcul_philo(t_philo philo)
{
	int			i;
	pthread_t	death;

	pthread_create(&death, NULL, &verify_philo_dead, (void *)&philo);
	pthread_detach(death);
	i = 0;
	while (1)
	{
		try_cycle(&philo);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_glob	*glob;

	if (ft_handle_errors(argc, argv) == 0)
		return (0);
	glob = init_glob(argv, argc);
	wait_end_condition(glob);
	clear_data(glob);
	return (0);
}
