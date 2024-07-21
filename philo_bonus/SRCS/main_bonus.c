/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akar <mel-akar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 06:31:01 by mel-akar          #+#    #+#             */
/*   Updated: 2024/07/21 11:25:50 by mel-akar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers_bonus.h"

int	p_error(char *message, int status)
{
	printf(YLW"%s\n", message);
	return (exit(status), status);
}

t_data	*making_philos(t_data *data, int ac, char **av)
{
	if (ac != 6 && ac != 5)
		return ((void)p_error(ARG_ERR, ERR_NO), NULL);
	(ac == 6) && (data->mealsnum = ft_atoi(av[5]));
	(ac == 5) && (data->mealsnum = 0);
	data -> stime = ft_atoi(av[4]);
	data -> etime = ft_atoi(av[3]);
	data -> dtime = ft_atoi(av[2]);
	data -> howmanyphilos = ft_atoi(av[1]);
	data -> isend = 0;
	return (data);
}

int	main(int ac, char **av)
{
	t_data		*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (p_error(ALLO_ERROR, ERR_NO));
	data = making_philos(data, ac, av);
	if (!data)
		return (p_error(INIT_ERR, ERR_NO));
}
