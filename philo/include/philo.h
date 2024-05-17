#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

typedef struct s_data t_data;
typedef struct s_fork t_fork;
typedef struct s_philo t_philo;
typedef enum e_states t_states;

enum e_states
{
	TAKEN_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED
};

struct s_data
{
	int				philo_nbr;
	int				fork_nbr;
	t_philo 		*philos;
	t_fork			*forks;
};

struct s_philo
{
	int				id;
	t_states		state;
	t_data			*data;
};

struct s_fork
{
	int				id;
};


int				ft_strlen(char *s);
void			*logger(void *param);

#endif
