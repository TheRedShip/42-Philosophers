/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:53:05 by ycontre           #+#    #+#             */
/*   Updated: 2023/12/18 16:06:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

u_int64_t	get_time(t_glob *glob)
{
	struct timeval	tv;
	
	if (gettimeofday(&tv, NULL))
		error_exit(glob);
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

void print_message(t_philo *philo, char *message)
{
	pthread_mutex_lock(&(philo->glob->lock));
	if (philo->glob->dead == 0)
		printf("%ld %d %s\n", get_time(philo->glob) - philo->glob->start_time, philo->id, message);
	pthread_mutex_unlock(&(philo->glob->lock));
}

int	ft_usleep(useconds_t time, t_glob *glob)
{
	u_int64_t	start;
	start = get_time(glob);
	while ((get_time(glob) - start) < time)
		usleep(time / 10);
	return(0);
}

void do_eat(t_philo *philo)
{
	philo->status = 0;
	pthread_mutex_lock(philo->right_fork);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(&philo->lock);
	philo->status = 1;
	philo->time_to_die = get_time(philo->glob) + philo->glob->time_to_die;
	print_message(philo, "is eating");
	philo->eaten_time++;
	ft_usleep(philo->glob->time_to_eat, philo->glob);
	philo->status = 2;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}


// void	*monitor(void *glob_pointer)
// {
// 	t_glob	*glob;

// 	glob = (t_glob *) glob_pointer;
// 	pthread_mutex_lock(&glob->lock);
// 	printf("glob val: %d", glob->dead);
// 	while (glob->dead == 0)
// 	{
// 		pthread_mutex_unlock(&glob->lock);
// 		pthread_mutex_lock(&glob->lock);
// 		if (glob->total_eaten >= glob->philo_num)
// 			glob->dead = 1;
// 		pthread_mutex_lock(&glob->lock);
// 	}
// 	pthread_mutex_unlock(&glob->lock);
// 	return ((void *)0);
// }

void	*supervisor(void *philo_pointer)
{
	t_philo *philo;

	philo = (t_philo *)philo_pointer;
	pthread_mutex_lock(&(philo->glob->lock)); 
	while (philo->glob->dead == 0)
	{
		pthread_mutex_unlock(&(philo->glob->lock));
		pthread_mutex_lock(&(philo->lock));

		if (get_time(philo->glob) >= philo->time_to_die && philo->status != 1)
		{
			pthread_mutex_lock(&(philo->glob->lock));
			if (philo->glob->dead == 0)
				printf("%ld %d %s\n", get_time(philo->glob) - philo->glob->start_time, philo->id, "died");
			philo->glob->dead = 1;
			pthread_mutex_unlock(&(philo->glob->lock));
		}
		pthread_mutex_unlock(&(philo->lock));
		pthread_mutex_lock(&(philo->glob->lock)); 
	}
	pthread_mutex_unlock(&(philo->glob->lock)); 
	return ((void *)0);
}

void *routine(void *philo_pointer)
{
	t_philo *philo;

	philo = (t_philo *)philo_pointer;
	philo->time_to_die = philo->glob->time_to_die + get_time(philo->glob);
	if (pthread_create(&(philo->supervisor), NULL, &supervisor, (void *)philo))
		error_exit(philo->glob);
	pthread_mutex_lock(&(philo->glob->lock)); 
	while (philo->glob->dead == 0)
	{
		pthread_mutex_unlock(&(philo->glob->lock));
		do_eat(philo);
		philo->status = 3;
		print_message(philo, "is sleeping");
		ft_usleep(philo->glob->time_to_sleep, philo->glob);
		philo->status = 4;
		print_message(philo, "is thinking");
		ft_usleep(2, philo->glob);
		pthread_mutex_lock(&(philo->glob->lock));
	}
	pthread_mutex_unlock(&(philo->glob->lock));

	if (pthread_join(philo->supervisor, NULL))
		error_exit(philo->glob);
	return ((void *)0);
}

void calcul_philo(t_glob *glob)
{
	int	i;
	
	glob->start_time = get_time(glob);
	i = 0;
	while (i < glob->philo_num)
	{
		pthread_mutex_lock(&(glob->lock));
		pthread_mutex_lock(&(glob->philo[i].lock));
		if (pthread_create(&(glob->philo[i].routine), NULL, &routine, &glob->philo[i]))
			error_exit(glob);
		pthread_mutex_unlock(&(glob->lock));
		pthread_mutex_unlock(&(glob->philo[i].lock));

		
		ft_usleep(1, glob);
		i++;
	}
	i = 0;
	while (i < glob->philo_num)
	{
		if(pthread_join(glob->philo[i].routine, NULL))
			error_exit(glob);
		i++;
	}
}

void	one_philo(t_glob *glob)
{
	glob->start_time = get_time(glob);
	if (pthread_create(&(glob->philo[0].routine), NULL, &routine, &glob->philo[0]))
			error_exit(glob);
	pthread_detach(glob->philo[0].routine);
	pthread_mutex_lock(&(glob->lock));
	while (glob->dead == 0)
	{
		pthread_mutex_unlock(&(glob->lock));
		ft_usleep(1, glob);
		pthread_mutex_lock(&(glob->lock));
	}
	pthread_mutex_unlock(&(glob->lock));

	clear_data(glob);
	exit(EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
	t_glob *glob;

	if (ft_handle_errors(argc, argv) == 0)
		return (0);
	glob = init_glob(argv, argc);
	if (glob->philo_num == 1)
		one_philo(glob);
	calcul_philo(glob);
	clear_data(glob);
	return (0);
}