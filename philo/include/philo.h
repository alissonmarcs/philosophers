#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

# define YELLOW "\001\033[1;33m\002"
# define GREEN "\001\033[1;32m\002"
# define RED "\001\033[1;31m\002"
# define BLUE "\001\033[1;94m\002"
# define PURPLE "\001\033[1;35m\002"
# define CYAN "\001\033[1;36m\002"
# define WHITE "\001\033[1;37m\002"
# define RESET "\001\033[0m\002"

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
	bool			action_done;
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
