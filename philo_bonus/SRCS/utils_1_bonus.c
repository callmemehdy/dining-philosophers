
#include "../headers/philosophers_bonus.h"

int	validity(char *s)
{
	int		i;

	i = -1;
	while (s[++i])
		if (s[i] != ' ')
			return (1337);
	return (0);
}

int	ft_atoi(char *s)
{
	long		res;
	int			i;
	long		tmp;

	tmp = 0;
	res = 0;
	i = 0;
	if (!s[i] || !s)
		p_error("Invalid input", EXIT_FAILURE);
	while (s[i] == ' ')
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			p_error("Invalid input", EXIT_FAILURE);
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		tmp = res;
		res = (res * 10) + (s[i] - 48);
		if ((res / 10) != tmp)
			p_error("Invalid input", EXIT_FAILURE);
		i++;
	}
	if (s[i] && validity(s + i))
		p_error("Invalid input", EXIT_FAILURE);
	return ((int)res);
}

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		p_error("gettimeofday failed\n", EXIT_FAILURE);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long milliseconds)
{
	long	start;

	start = get_time();
	while (get_time() - start < milliseconds)
		usleep(200);
}

void	printing(t_philo *philo, char *message, int died)
{
	int		id;

	if (philo -> isfull)
		return ;
	sem_wait(philo -> data -> stop);
	id = philo -> id;
	printf("%zu %d %s", get_time() - philo -> data -> simul_beg, id, message);
	if (!died)
		sem_post(philo -> data -> stop);
}
