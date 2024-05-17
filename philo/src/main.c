#include <philo.h>

int main(void)
{
	pthread_t t1;

	pthread_create(&t1, NULL, logger, &(t_philo) {.state = SLEEPING});
	pthread_join(t1, NULL);
	return 0;
}
