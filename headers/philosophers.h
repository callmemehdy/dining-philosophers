/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akar <mel-akar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:45:40 by mel-akar          #+#    #+#             */
/*   Updated: 2024/07/18 11:51:14 by mel-akar         ###   ########.fr       */
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
# define MS 1000
typedef struct s_data t_data;
typedef pthread_mutex_t  t_mtx;

typedef	enum s_ops
{
	lock,
	unlock,
	destroy,
	init
}			t_ops;

typedef struct s_philo
{
	int			id;
	pthread_t 	thread_id;
	int			meals;
	int			meals_eaten;
	size_t 		lastmeal_time;
	int			isfull;
	int			isdead;
	// forks __________
	t_mtx		*rfork;
	t_mtx		*lfork;
	// forks __________
	t_data		*data;
}             t_philo;

struct s_data
{
	int				howmanyphilos;
	int				key;
	size_t        	dtime;
	size_t         	etime;
	size_t         	stime;
	int         	mealsnum;
	int				isend;
	int				allfull;
	size_t			simul_beg;
	t_mtx			*forks;
	t_philo			*philos;
	pthread_t		monitor;
	// mutexes ... 
	t_mtx			print;
	t_mtx			monilock;
	t_mtx			reading;
	t_mtx			lock;
};
// utils
void    ft_error(t_data *data, char *message);
int     ft_atoi(char *s);
size_t 	get_time(void);
void	ft_usleep(size_t micros);
// creating
t_data	*stuffing(char **av);
void	forking(t_philo *philo, t_mtx *forks, int pos);
int		creating_philosophers(t_data *data);
int		creating(t_data *data);
// simulation
int		simulation(t_data *data);
// seerbay

#endif