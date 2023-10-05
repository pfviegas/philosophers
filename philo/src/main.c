/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:32:31 by pviegas           #+#    #+#             */
/*   Updated: 2023/10/05 13:58:09 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void run_simulation(t_Simulation *sim, t_Philosopher *philosopher)
{
	int i;
	
	pthread_mutex_init(&sim->simulation_lock, NULL);
	pthread_mutex_init(&sim->print_lock, NULL);
	pthread_mutex_init(&sim->meals_lock, NULL);
	pthread_mutex_init(&sim->time_lock, NULL);
	pthread_mutex_init(&sim->start_time_lock, NULL);
	// Inicialização dos garfos
	sim->forks = malloc(sizeof(t_Fork) * (sim->num_philosophers));
	if (!sim->forks)
		exit (4);
	i = 0;
	while(i < sim->num_philosophers)
	{	
		sim->forks[i].is_available = 1;
		pthread_mutex_init(&sim->forks[i].lock, NULL);
		i++;
	}

	sim->start_time = get_time_ms(NULL);
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
	pthread_mutex_destroy(&sim->meals_lock);
	pthread_mutex_destroy(&sim->time_lock);
	pthread_mutex_destroy(&sim->start_time_lock);
	i = 0;
	while(i < sim->num_philosophers)
		pthread_mutex_destroy(&sim->forks[i++].lock);
}

int	main(int argc, char *argv[])
{
	t_Simulation	sim;
	t_Philosopher	*philosophers;

	check_args(argc, argv);
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
