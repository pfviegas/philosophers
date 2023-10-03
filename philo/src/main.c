/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:20:16 by paulo             #+#    #+#             */
/*   Updated: 2023/10/03 13:08:30 by paulo            ###   ########.fr       */
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
	
	pthread_mutex_init(&sim->simulation_lock, NULL);
	pthread_mutex_init(&sim->print_lock, NULL);
	// Inicialização dos garfos
	sim->forks = malloc(sizeof(t_Fork) * (sim->num_philosophers));
	if (!sim->forks)
		exit (3);
	i = 0;
	while(i < sim->num_philosophers)
	{	
		sim->forks[i].is_available = 1;
		pthread_mutex_init(&sim->forks[i].lock, NULL);
		i++;
	}

	sim->start_time = get_time_ms();
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

	pthread_mutex_destroy(&sim->simulation_lock);
	pthread_mutex_destroy(&sim->print_lock);
	i = 0;
	while(i < sim->num_philosophers)
		pthread_mutex_destroy(&sim->forks[i++].lock);
}

/**
 * @file main.c by 0x401403: main (main.c:84)
 * @brief Entry point of the program. 
 * Initializes the simulation variables, creates philosophers and runs the simulation.
 * 
 * @param argc Number of arguments passed to the program.
 * @param argv Array of	printf ("get_time_ms : %ld\n", get_time_ms());
 * @return 0 if the program runs successfully.
 */
int	main(int argc, char *argv[])
{
	t_Simulation	sim;
	t_Philosopher	*philosophers;

	check_argc(argc);
	check_argv(argv);
	// Inicia as variaveis da simulação
	init_var_sim(&sim, argc, argv);

	// Criação dos filósofos
	philosophers = malloc(sizeof(t_Philosopher) * (sim.num_philosophers));
	if (!philosophers)
		return (1);
	create_philisophers(&sim, philosophers);

	// Executa a simulação
	run_simulation(&sim, philosophers);

	free(philosophers);
	free(sim.forks);
		
	return (0);
}
