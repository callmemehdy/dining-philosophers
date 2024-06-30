#include "../headers/philosophers.h"

int ft_atoi(char *s)
{
  long res;
  int sign;
  int i;
  long tmp;

  1337 && (sign = 1, tmp = 0, res = 0, i = -1);
  if (s[i] == '+' || s[i] == '-')
  {
    if (s[i] == '-')
      sign *= -1;
  }
  while (s[++i] >= '0' && s[i] <= '9')
  {
    tmp = res;
    res = (res * 10) + (s[i] - 48);
    if ((res / 10) != tmp)
      return (-1);
  }
  return (sign * (int)res);
}

t_data  *stuffing(char **av)
{
  t_data *data;

  data = malloc(sizeof(t_data));
  if (!data)
    return (NULL);
  data->philon = ft_atoi(av[1]);
  data->dtime  = ft_atoi(av[2]);
  data->etime  = ft_atoi(av[3]);
  data->stime  = ft_atoi(av[4]);
  data->eatn   = ft_atoi(av[5]);
  return (data);
}

void *routine(void *dt)
{
  t_data *data;
  static int count;

  data = (t_data *)dt;
  count = 1;
  pthread_mutex_lock(&data->mutex);
  printf("%d is eating\n", count);
  usleep(data->eatn * 1000);
  printf("%d is sleeping\n", count);
  usleep(data->stime * 1000);
  printf("%d is thinking\n", count);
  usleep(data->dtime * 1000);
  count++;
  pthread_mutex_unlock(&data->mutex);
  return NULL;
}
void	ft_error(t_data *data, int status, char *message)
{
	if (data->philos)
		free(data->philos);
	if (data)
		free(data);
	printf("%s\n", message);
	exit(status);
}
void	creating_philosophers(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->philon)
	{
		if (pthread_create(&data->philos[i], NULL, &routine, data))
			ft_error(data, EXIT_FAILURE, "Error while creating");
	}
	i = -1;
	while (++i < data->philon)
	{
		if (pthread_join(data->philos[i],NULL))
			ft_error(data, EXIT_FAILURE, "Error while joining");
	}
}

int main(int ac, char **av)
{
	t_data *data;

	if (ac != 6)
		return (1);
	data = stuffing(av);
	data->philos = NULL;
	if (!data)
		ft_error(NULL, EXIT_FAILURE, "Error 001");
	pthread_mutex_init(&data->mutex, NULL);
	data->philos = malloc(sizeof(pthread_t) * data->philon);
	if (!data->philos)
		ft_error(data, EXIT_FAILURE, "Error 002");
	creating_philosophers(data);
}
