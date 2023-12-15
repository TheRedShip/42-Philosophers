/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:52:45 by ycontre           #+#    #+#             */
/*   Updated: 2023/12/15 15:59:57 by ycontre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_philoglob {
	int	philo_num;
	int	fork_num;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat;
	struct s_philo	*philo;
}	t_philoglob;

typedef struct s_philo {
	int	id;
	int	eaten_time;
	struct s_philoglob	*glob;
}	t_philo;

void	ft_putstr(int fd, char *str);
int		ft_atoi(char *str);

#endif