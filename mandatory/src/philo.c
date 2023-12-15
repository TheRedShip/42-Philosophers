/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:53:05 by ycontre           #+#    #+#             */
/*   Updated: 2023/12/15 15:56:40 by ycontre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void init_philo(t_philoglob *glob)
{
	int	i;
	
	glob->philo = malloc(sizeof(t_philo) * glob->philo_num);
	i = 0;
	while (i < glob->philo_num)
	{
		glob->philo[i].id = i;
		glob->philo[i].glob = glob;
		i++;
	}
}

t_philoglob init_glob(char **argv, int argc)
{
	t_philoglob glob;

	glob.philo_num = ft_atoi(argv[1]);
	glob.fork_num = glob.philo_num;
	glob.time_to_die = ft_atoi(argv[2]);
	glob.time_to_eat = ft_atoi(argv[3]);
	glob.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		glob.must_eat = ft_atoi(argv[5]);
	else
		glob.must_eat = -1;
	init_philo(&glob);
	return (glob);

}

void calcul_philo()
{
	
}

int main(int argc, char **argv)
{
	t_philoglob glob;
	
	if (argc < 5 || argc > 6)
	{
		ft_putstr(2, "Error: wrong number of arguments\n");
		return (0);
	}
	glob = init_glob(argv, argc);
	for(int i = 0; i < glob.philo_num; i++)
	{
		
	}
	printf("%d\n", glob.philo_num);
	return (0);
}