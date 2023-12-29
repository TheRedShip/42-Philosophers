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
    clear_data(glob);
    exit(0);
    return (NULL);
}