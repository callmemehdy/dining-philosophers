
#include "../headers/philosophers_bonus.h"

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
		if (get_time() - philo->last_meal_t > philo->data->dtime)
		{
			printing(philo, DIED, AH);
			philo -> isdead = 1;
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

	free(data -> pids);
	free(data -> philos);
	free(data);
	exit(SAMAM_LAMAN);
}
