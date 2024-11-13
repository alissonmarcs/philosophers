<div align="center">
	<h1>Philosophers</h1>
	<img src="https://i.imgur.com/LMdXWVp.png" alt="42 badge for philosophers project"/>
	<p align="center"> Resolution for the Dining philosophers problem </p>
</div>

<div align="center">
	<h2>Final score</h2>
	<img src="https://i.imgur.com/wGxDHM0.png" alt="Project scored with 100">
</div>

## How compile and use

```shell
git clone https://github.com/alissonmarcs/philosophers
cd philo
make
./philo [number_of_philos] [time_to_die] [time_to_eat] [time_to_sleep]
```

The philosophers are sit arround a table. At the middle of the table, exists an bowl of spaghetti, and between
each philosophers exists an fork. The numbers of forks are equal to the number of philosophers. The
philosophers must eat, sleep and think. When eating, they will use the two side forks, so if the philosopher 2
is eating, the philosopers 1 and 3 must wait for the forks.

When a philosopher finish eat, it will sleep. When it wake up, it will start thinking (it will try to get the
two side forks).

- Every philosopher will be an thread
- Every fork will be an mutex

If an philosopher take more than `[time_to_die]` to eat (because its neighbors are eating), it will die and
the program stop.

## Examples


```shell
./philo 5 400 100 100
```

If any philosopher wait more than 400 ms to eat, it will die. But every philosopher will take only 100 ms to eat.
In the above example, the philosophers will not die.

```shell
./philo 5 400 300 100
```

Every philosopher will take 300 ms to eat, but if any philosopher wait more than 400 ms to eat, it will die. In
the above example, the philosophers will die.
