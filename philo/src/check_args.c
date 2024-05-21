#include <philo.h>

static void	print_helper(void);
static bool	validate_times(char **argv);

bool	check_argv(int argc, char **argv)
{
	if ((argc == 5 || argc == 6) && validate_times(argv))
		return (true);
	print_helper();
	return (false);
}

static bool	validate_times(char **argv)
{
	long	philo_nbr;

	philo_nbr = ft_atol(argv[1]);
	if (philo_nbr <= 0 || philo_nbr > 200)
		return (false);
	else if (ft_atol(argv[2]) < 60)
		return (false);
	else if (ft_atol(argv[3]) < 60)
		return (false);
	else if (ft_atol(argv[4]) < 60)
		return (false);
	return (true);
}

static void	print_helper(void)
{
	printf("%sInvalid arguments.\n", RED);
	printf("%sExample of usage: ", CYAN);
	printf("%s./philo ", WHITE);
	printf("%s[number_of_philosophers] [time_to_die] [time_to_eat]"
		" [time_to_sleep] [number_of_times_each_philosopher_must_eat]", BLUE);
	printf(" %s(optional)\n", WHITE);
	printf("%sValue for %s[number_of_philosophers]%s must be between 1 and 200"
		".\n", YELLOW, BLUE, YELLOW);
	printf("Values for %s[time_to_die] [time_to_eat] %sand %s[time_to_sleep] "
		"%swill be considered in milliseconds and minimum value for them "
		"are 60.\n%s", BLUE, YELLOW, BLUE, YELLOW, RESET);
}
