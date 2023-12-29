/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:53:05 by ycontre           #+#    #+#             */
/*   Updated: 2023/12/29 14:39:06 by ycontre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void print_message(t_philo *philo, char *message, int dead)
{
	sem_t *sem;

	sem = sem_open("print", O_RDWR);
	sem_wait(sem);
	printf("%ld %d %s\n", get_time() - philo->start_time, philo->id, message);
	if (dead != 1)
		sem_post(sem);
	sem_close(sem);
}

void try_cycle(t_philo *philo)
{
	int	i;
	sem_t *sem;
	sem_t *sem_eat;

	sem = sem_open("forks", O_RDWR);
	i = 0;
	philo->status = 0;
	while (i < 2)
	{
		sem_wait(sem);
		print_message(philo, "has taken a fork", 0);
		i++;
	}
	philo->eaten_time++;
	if (philo->eaten_time == philo->must_eat)
	{
		sem_eat = sem_open("meal", O_RDWR);
		sem_post(sem_eat);
		sem_close(sem_eat);
	}
	philo->last_meal = get_time();
	philo->status = 1;
	print_message(philo, "is eating", 0);
	ft_usleep(philo->time_to_eat);
	philo->status = 2;
	sem_post(sem);
	sem_post(sem);
	print_message(philo, "is sleeping", 0);
	ft_usleep(philo->time_to_sleep);
	print_message(philo, "is thinking", 0);
	sem_close(sem);
}

void *verify_philo_dead(void *philo_ptr)
{
	sem_t *sem;
	t_philo *philo;

	philo = (t_philo *)philo_ptr;
	while (1)
	{
		if (get_time() >= philo->last_meal + philo->time_to_die && philo->status != 1)
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

void calcul_philo(t_philo philo)
{
	pthread_t death;
	int	i;

	pthread_create(&death, NULL, &verify_philo_dead, (void *)&philo);
	pthread_detach(death);
	i = 0;
	while (1)
	{
		try_cycle(&philo);
		i++;
	}
}

void wait_end_condition(t_glob *glob)
{
	int	i;
	sem_t *sem;
	sem_t *sem_death;
	pthread_t waitdeath;
	pthread_t eat_enough;

	pthread_create(&waitdeath, NULL, &wait_any_death, (void *)glob);
	pthread_create(&eat_enough, NULL, &waitate, (void *)glob);

	i = 0;
	while (glob->pids[i] != 0)
	{
		waitpid(glob->pids[i], NULL, 0);
		i++;
	}
	i = 0;
	sem_death = sem_open("died", O_RDWR);
	sem_post(sem_death);
	sem_close(sem_death);
	
	sem = sem_open("meal", O_RDWR);
	while (glob->pids[i] != 0)
	{
		sem_post(sem);
		i++;
	}
	sem_close(sem);
	pthread_join(waitdeath, NULL);
	pthread_join(eat_enough, NULL);
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