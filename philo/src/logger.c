#include <philo.h>

void	*logger(void *param)
{
	char		*string;
	t_philo		*philo;

	philo = (t_philo *) param;
	if (philo->state == TAKEN_FORK)
		string = CYAN"has taken a fork"RESET"\n";
	else if (philo->state == EATING)
		string = WHITE"is eating"RESET"\n";
	else if (philo->state == SLEEPING)
		string = BLUE"is sleeping"RESET"\n";
	else if (philo->state == THINKING)
		string = YELLOW"is thinking"RESET"\n";
	else if (philo->state == DIED)
		string = RED"died"RESET"\n";
	else
		return (NULL);
	write(1, string, ft_strlen(string));
	return (NULL);
}

int	ft_strlen(char *s)
{
	char *start;

	start = s;
	while (*s)
		s++;
	return (s - start);
}
