/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:53:05 by ycontre           #+#    #+#             */
/*   Updated: 2023/12/16 16:31:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void *routine(void *philo_pointer)
{
	t_philo *philo;

	philo = (t_philo *)philo_pointer;
	while (philo->glob->dead == 0)
	{
		do_eat(philo);
		do_sleep(philo);
	}
	return ((void *)0);
}

void calcul_philo(t_glob *glob)
{
	int	i;

	i = 0;
	while (i < glob->philo_num)
	{
		if (pthread_create(&(glob->philo[i].thread), NULL, &routine, &glob->philo[i]))
			error_exit(glob);
		i++;
	}
	i = 0;
	while (i < glob->philo_num)
	{
		if(pthread_join(glob->philo[i].thread, NULL))
			error_exit(glob);
		i++;
	}
}

int main(int argc, char **argv)
{
	t_glob glob;

	if (ft_handle_errors(argc, argv) == 0)
		return (0);
	glob = init_glob(argv, argc);
	calcul_philo(&glob);
	clear_data(&glob);
	return (0);
}