/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:53:05 by ycontre           #+#    #+#             */
/*   Updated: 2023/12/16 16:02:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void calcul_philo(t_glob glob)
{
	(void) glob;	
}

int main(int argc, char **argv)
{
	t_glob glob;

	if (ft_handle_errors(argc, argv) == 0)
		return (0);
	glob = init_glob(argv, argc);

	calcul_philo(glob);

	clear_data(&glob);

	return (0);
}