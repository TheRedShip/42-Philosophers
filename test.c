/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:04:59 by ycontre           #+#    #+#             */
/*   Updated: 2023/12/15 15:49:42 by ycontre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>

int cont = 0;

void  *routine(void *mutex)
{
  int i;

  pthread_mutex_lock((pthread_mutex_t *)mutex);
  i = -1;
  while (++i < 1000000)
  	  cont++;
  pthread_mutex_unlock((pthread_mutex_t *)mutex);
  return (NULL);
}

int main()
{
  pthread_t tid1, tid2;
	pthread_mutex_t mutex;

  pthread_mutex_init(&mutex, NULL);
  pthread_create(&tid1, NULL, &routine, &mutex);
  pthread_create(&tid2, NULL, &routine, &mutex);

  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  pthread_mutex_destroy(&mutex);
  printf("cont: %d\n", cont);
}