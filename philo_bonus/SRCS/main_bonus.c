/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akar <mel-akar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 06:31:01 by mel-akar          #+#    #+#             */
/*   Updated: 2024/07/21 14:34:25 by mel-akar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers_bonus.h"

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
