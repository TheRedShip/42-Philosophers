/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_conditions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 18:49:55 by marvin            #+#    #+#             */
/*   Updated: 2023/12/22 18:49:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	wait_end_condition(t_glob *glob)
{
	int			i;
	sem_t		*sem;
	sem_t		*sem_death;
	pthread_t	waitdeath;
	pthread_t	eat_enough;

	pthread_create(&waitdeath, NULL, &wait_any_death, (void *)glob);
	pthread_create(&eat_enough, NULL, &waitate, (void *)glob);
	i = 0;
	while (glob->pids[i] != 0)
	{
		waitpid(glob->pids[i], NULL, 0);
		i++;
	}
	sem_death = sem_open("died", O_RDWR);
	sem_post(sem_death);
	sem_close(sem_death);
	sem = sem_open("meal", O_RDWR);
	i = -1;
	while (glob->pids[++i] != 0)
		sem_post(sem);
	sem_close(sem);
	pthread_join(waitdeath, NULL);
	pthread_join(eat_enough, NULL);
}

void	*wait_any_death(void *glob_ptr)
{
	sem_t		*sem;
	t_glob		*glob;

	glob = (t_glob *)glob_ptr;
	sem = sem_open("died", O_RDWR);
	sem_wait(sem);
	sem_close(sem);
	kill_pid(glob);
	return (NULL);
}

void	*waitate(void *glob_ptr)
{
	int			i;
	sem_t		*sem;
	t_glob		*glob;

	glob = (t_glob *)glob_ptr;
	sem = sem_open("meal", O_RDWR);
	i = 0;
	while (i < glob->philo_num)
	{
		sem_wait(sem);
		i++;
	}
	sem_close(sem);
	kill_pid(glob);
	return (NULL);
}
