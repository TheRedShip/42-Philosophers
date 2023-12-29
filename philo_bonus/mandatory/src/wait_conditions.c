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

void *wait_any_death(void *glob_ptr)
{
    t_glob *glob;
    sem_t *sem;

    glob = (t_glob *)glob_ptr;
    sem = sem_open("died", O_RDWR);
    sem_wait(sem);
    sem_close(sem);
    kill_pid(glob);
    return (NULL);
}

void *waitate(void *glob_ptr)
{
    int i;
    t_glob *glob;
    sem_t *sem;

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