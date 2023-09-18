/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:20:16 by paulo             #+#    #+#             */
/*   Updated: 2023/09/18 16:26:20 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// atualizar cabeçalho

#include "../includes/philosophers.h"

/**
 * Runs the simulation with the given philosophers and settings.
 * Initializes forks and creates threads for each philosopher.
 * Waits for the threads to finish.
 *
 * @param sim The simulation settings.
 * @param philosopher The array of philosophers.
 */
void run_simulation(t_Simulation *sim, t_Philosopher *philosopher)
{
	int i;
	
	pthread_mutex_init(&sim->print_lock, NULL);
	// Inicialização dos garfos
	sim->forks = malloc(sizeof(t_Fork) * (sim->num_philosophers + 1));
	i = 0;
	while(i < sim->num_philosophers)
	{	
		pthread_mutex_init(&sim->forks[i].lock, NULL);
		sim->forks[i].is_available = 1;
		i++;
	}

	// Criação das threads para os filósofos
	i = 0;
	while(i < sim->num_philosophers)
	{
		pthread_create(&philosopher[i].thread, NULL, philosopher_life, &philosopher[i]);
		i++;
	}

	// Aguarda o fim das threads
	i = 0;
	while(i < sim->num_philosophers)
		pthread_join(philosopher[i++].thread, NULL);
}

/**
 * @file main.c
 * @brief Entry point of the program. 
 * Initializes the simulation variables, creates philosophers and runs the simulation.
 * 
 * @param argc Number of arguments passed to the program.
 * @param argv Array of strings containing the arguments passed to the program.
 * @return 0 if the program runs successfully.
 */
int	main(int argc, char *argv[])
{
	t_Simulation	sim;
	t_Philosopher	*philosophers;

	if (argc == 5 || argc == 6)
	{
		// Inicia as variaveis da simulação
		init_var_sim(&sim, argc, argv);

		// Criação dos filósofos
		philosophers = malloc(sizeof(t_Philosopher) * (sim.num_philosophers));
		create_philisophers(&sim, philosophers);

		// Executa a simulação
		run_simulation(&sim, philosophers);

		free(philosophers);
		free(sim.forks);
	}
	else
		printf ("Sintax: ./philo nb_philos t_die t_eat t_sleep <nb_t_eat>\n");
	return (0);
}
