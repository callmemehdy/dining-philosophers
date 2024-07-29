#include "../headers/philosophers_bonus.h"

static int	dead(t_philo *philo)
{
	if (get_time() - philo -> last_meal_t > philo -> data -> dtime)
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
			printing(philo, DIED);
			sem_wait(philo -> data -> stop);
			exit(42);
		}
		if (full(philo))
		{
			philo -> isfull = 1;
			// sem_wait(philo -> data -> stop);
			return (NULL);
		}
	}
	return (NULL);
}

int	p_error(char *message, int status)
{
	printf(YLW"%s\n", message);
	return (exit(status), status);
}

void	destroying_sem(t_data *data)
{
	if (sem_destroy(data -> forks))
		p_error(FREE_ERR, EXIT_FAILURE);
	if (sem_destroy(data -> print))
		p_error(FREE_ERR, EXIT_FAILURE);
	if (sem_destroy(data -> stop))
		p_error(FREE_ERR, EXIT_FAILURE);
	sem_unlink("/sem");
	sem_unlink("/stop");
	sem_unlink("/print");
	exit(SAMAM_LAMAN);
}
