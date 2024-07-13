/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akar <mel-akar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:45:40 by mel-akar          #+#    #+#             */
/*   Updated: 2024/07/01 16:50:07 by mel-akar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include  <stdio.h>
# include <sys/time.h>
# define RED "\033[0;31m"
# define YLW "\033[0;33m"

typedef struct s_data t_data;
typedef pthread_mutex_t  t_mtx;

typedef	enum s_ops
{
	lock = 1,
	unlock = 2,
	destroy = 3,
	init = 4
}			t_ops;


typedef struct s_fork
{
	t_mtx fork;
	int				fork_id;
}			t_fork;

typedef struct s_philo
{
	int			id;
	pthread_t 	thread_id;
	int			meals;
	int			meals_eaten;
	size_t 		lastmeal_time;
	int			isfull;
	int			isdead;
	t_fork		*rfork;
	t_fork		*lfork;
	t_data		*data;
	t_mtx		setting;
	t_mtx		sleeping;
}             t_philo;

struct s_data
{
	int				howmanyphilos;
	size_t        	dtime;
	size_t         	etime;
	size_t         	stime;
	int         	mealsnum;
	size_t			simul_beg;
	int				isend;
	t_fork			*forks;
	t_philo			*philos;
	t_mtx			print;
	pthread_t		monitor;
	t_mtx			thinking;
};
// utils
void    ft_error(t_data *data, int status, char *message);
int     ft_atoi(char *s);
size_t 	get_time(void);
void	ft_usleep(size_t micros);
// creating
t_data	*stuffing(char **av);
void	forking(t_philo *philo, t_fork *forks, int pos);
void	creating_philosophers(t_data *data);
void	creating(t_data *data);
// simulation
void	printing(t_philo *philo);
void	eating(t_philo *philo);
void	*sum_func(void *p);
void	simulation(t_data *data);
//
void	*monitoring_threads(void *dt);
#endif