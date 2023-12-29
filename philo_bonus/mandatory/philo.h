/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:52:45 by ycontre           #+#    #+#             */
/*   Updated: 2023/12/22 19:08:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <semaphore.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <stdlib.h>
# include <signal.h>
# include <pthread.h>

typedef struct s_glob {
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				total_eaten;
	int				fork_num;
	int				*pids;
}	t_glob;

typedef struct s_philo {
	int				id;
	int				status;
	u_int64_t		last_meal;
	int				eaten_time;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	u_int64_t		start_time;
}	t_philo;

void	ft_putstr(int fd, char *str);
int		ft_atoi(char *str);
void	error_exit(t_glob *glob);
void	clear_data(t_glob *glob);

u_int64_t	get_time();
int	ft_usleep(useconds_t time);

t_glob	*init_glob(char **argv, int argc);

int		ft_handle_errors(int argc, char **argv);

void calcul_philo(t_philo philo);

void *wait_any_death(void *glob);

#endif