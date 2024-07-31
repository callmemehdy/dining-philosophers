/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akar <mel-akar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 02:41:28 by mel-akar          #+#    #+#             */
/*   Updated: 2024/07/30 16:04:49 by mel-akar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers_bonus.h"

static int	dead(t_philo *philo)
{
	if ((get_time() - philo->last_meal_t > philo->data->dtime))
		return (AH);
	return (LA);
}

static int	full(t_philo *philo)
{
	int		n_meal;

	n_meal = philo -> data -> mealsnum;
	if (philo -> meals_eaten == n_meal)
		return (AH);
	return (LA);
}

void	*monitoring_stuff(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (AH)
	{
		if (dead(philo))
		{
			philo -> isdead = 1;
			printing(philo, DIED, AH);
			exit(42);
		}
		if (full(philo))
		{
			philo -> isfull = 1;
			return (NULL);
		}
	}
	return (NULL);
}

int	p_error(char *message, int status)
{
	printf(YLW"%s", message);
	return (exit(status), status);
}

void	destroying_sem(t_data *data)
{
	sem_unlink("/sem");
	sem_unlink("/stop");
	free(data -> philos);
	free(data ->pids);
	free(data);
	exit(SAMAM_LAMAN);
}
