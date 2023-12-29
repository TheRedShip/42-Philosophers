/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:53:05 by ycontre           #+#    #+#             */
/*   Updated: 2023/12/22 19:25:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void print_message(t_philo *philo, char *message)
{
	printf("%ld %d %s\n", get_time() - philo->start_time, philo->id, message);
}

void try_cycle(t_philo *philo)
{
	int	i;
	sem_t *sem;

	sem = sem_open("forks", O_RDWR);
	i = 0;
	philo->status = 0;
	while (i < 2)
	{
		sem_wait(sem);
		print_message(philo, "has taken a fork");
		i++;
	}
	philo->last_meal = get_time();
	philo->status = 1;
	print_message(philo, "is eating");
	ft_usleep(philo->time_to_eat);
	philo->status = 2;
	sem_post(sem);
	sem_post(sem);
	print_message(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
	print_message(philo, "is thinking");
	sem_close(sem);
}

void *verify_philo_dead(void *philo_ptr)
{
	sem_t *sem;
	t_philo *philo;

	philo = (t_philo *)philo_ptr;
	while (1)
	{
		if (get_time() >= philo->last_meal + philo->time_to_die && philo->status != 1 && philo->last_meal != (u_int64_t)-1)
		{
			print_message(philo, "died");
			sem = sem_open("died", O_RDWR);
			sem_post(sem);
			sem_close(sem);
			return (NULL);
		}
	}
	return (NULL);
}

void calcul_philo(t_philo philo)
{
	pthread_t death;
	int	i;

	pthread_create(&death, NULL, &verify_philo_dead, (void *)&philo);
	i = 0;
	while (1)
	{
		try_cycle(&philo);
		i++;
	}
}

void wait_end_condition(t_glob *glob)
{
	pthread_t waitdeath;

	pthread_create(&waitdeath, NULL, &wait_any_death, (void *)glob);
	pthread_join(waitdeath, NULL);
}

int main(int argc, char **argv)
{
	t_glob *glob;

	if (ft_handle_errors(argc, argv) == 0)
		return (0);
	glob = init_glob(argv, argc);
	wait_end_condition(glob);
	
	clear_data(glob);
	return (0);
}