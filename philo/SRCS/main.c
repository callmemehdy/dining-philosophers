/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akar <mel-akar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:25:58 by mel-akar          #+#    #+#             */
/*   Updated: 2024/07/30 18:14:00 by mel-akar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers.h"

int	main(int ac, char **av)
{
	t_data		*data;

	if (ac != 6 && ac != 5)
		return (ft_error(NULL, "Usage: ./program [] [] [] [] []"), 1);
	7 && (data = NULL);
	data = stuffing(av, ac);
	if (!data)
		return (ft_error(NULL, "Error 001"), 2);
	7 && (data->philos = NULL, data->forks = NULL);
	if (preventing_headache(data))
		return (f_a_r(data), ft_error(data, "not a valid test!"), 404);
	if (init_m(data))
		return (free(data), ft_error(data, "...while initializing..."), 3);
	if (creating(data))
		return (ft_error(data, "..Error in creating.."), 4);
	if (simulation(data))
		return (f_a_r(data), 5);
	if (monitoring(data))
		return (f_a_r(data), ft_error(data, "monitor failed soldier--"), 6);
	if (waiting(data))
		return (f_a_r(data), 1);
	if (destroying(data))
		return (f_a_r(data), ft_error(data, "some issues while destroying!"),
			7);
	f_a_r(data);
}
