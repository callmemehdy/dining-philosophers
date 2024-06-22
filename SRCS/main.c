#include "../headers/philosophers.h"

int ft_atoi(char *s)
{
  long res;
  int sign;
  int i;
  int tmp;

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

int main(int ac, char **av)
{
  t_data *data;

  // *data = (t_data){0};
  if (ac != 6)
    return (1);
  data = malloc(sizeof(t_data));
  if (!data)
    return (2);
  data->philon = ft_atoi(av[1]);
  data->dtime  = ft_atoi(av[2]);
  data->etime  = ft_atoi(av[3]);
  data->stime  = ft_atoi(av[4]);
  data->eatn   = ft_atoi(av[5]);
  printf("philo number:\t%d\n", data->philon);
  printf("philo number:\t%d\n",data->dtime);
  printf("philo number:\t%d\n",data->etime);
  printf("philo number:\t%d\n",data->stime);
  printf("philo number:\t%d\n", data->eatn);
}
