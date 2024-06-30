#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include  <stdio.h>
# include <sys/time.h>

typedef struct s_data
{
  pthread_t   *philos;
  int         philon;
  int         dtime;
  int         etime;
  int         stime;
  int         eatn;
}       t_data;

typedef struct s_philo
{
	pthread_t id;

}             t_philo;

#endif
