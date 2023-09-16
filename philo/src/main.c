/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:20:16 by paulo             #+#    #+#             */
/*   Updated: 2023/09/16 15:47:57 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// atualizar cabeçalho

#include "../includes/philosophers.h"

// Função que define o ciclo de vida de um filósofo
void *philosopher_life(void *arg) 
{
	t_Philosopher *philo;

	philo = (t_Philosopher *)arg;
	while (philo->meals_left != 0) 
	{
//		eat(philo);
//		think(philo);
//		sleep(philo);
		printf("philosopher_life\n");
	}
	return (NULL);
}

// Função para criar e iniciar a simulação
void run_simulation(t_Simulation *sim, t_Philosopher *philosopher)
{
	int i;
	
	pthread_mutex_init(&sim->print_lock, NULL);
	// Inicialização dos garfos
	i = 0;
	while(i < sim->num_philosophers)
		pthread_mutex_init(&sim->forks[i++], NULL);

	gettimeofday(&sim->start_time, NULL);

    // Criação das threads para os filósofos
	i = 0;
	while(i < sim->num_philosophers)
	{
		pthread_create(&philosopher[i].thread, NULL, philosopher_life, &philosopher[i]);
		i++;
	}

    // Aguarda o término das threads
	i = 0;
	while(i < sim->num_philosophers)

		pthread_join(philosopher[i++].thread, NULL);
}

int	main(int argc, char *argv[])
{
	t_Simulation	sim;
	t_Philosopher	*philosophers;

	if (argc != 5 && argc != 6)
		quit("Sintax: ./philo nb_philos t_die t_eat t_sleep <nb_t_eat>\n", 1);
	init_var_sim(&sim, argc, argv);
	
	printf("Philosophers: %d\n", sim.num_philosophers);
	printf("Time to die: %d miliseconds\n", sim.time_to_die);
	printf("Time to eat: %d miliseconds\n", sim.time_to_eat);
	printf("Time to sleep: %d miliseconds\n", sim.time_to_sleep);
	printf("Number of meals: %d \n\n", sim.eat_count);

	// Criação dos filósofos
	philosophers = malloc(sizeof(t_Philosopher) * (sim.num_philosophers + 1));
	create_philisophers(&sim, philosophers);
	
	// Lista os filósofos
	for (int i = 0; i < sim.num_philosophers; i++) 
	{
		printf("philosopher id : %d\n", philosophers[i].id);
		printf("meals left : %d\n", philosophers[i].meals_left);
		printf("state id : %u\n", philosophers[i].state);
		printf("last meal time : %ld\n", philosophers[i].last_meal_time);
		printf("philosopher sim : %p\n\n", philosophers[i].sim);
	}

	// Executa a simulação
	run_simulation(&sim, philosophers);
	
	return (0);
}
