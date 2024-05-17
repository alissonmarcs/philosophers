#include <philo.h>

int main(void)
{
	pthread_t t1;

	pthread_create(&t1, NULL, logger, &(t_philo) {.state = THINKING});
	pthread_create(&t1, NULL, logger, &(t_philo) {.state = SLEEPING});
	pthread_create(&t1, NULL, logger, &(t_philo) {.state = DIED});
	pthread_create(&t1, NULL, logger, &(t_philo) {.state = EATING});
	pthread_create(&t1, NULL, logger, &(t_philo) {.state = TAKEN_FORK});
	pthread_join(t1, NULL);

	return 0;
}
