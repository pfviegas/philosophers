/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:32:31 by pviegas           #+#    #+#             */
/*   Updated: 2023/10/06 15:58:39 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/**
 * Runs the simulation with the given simulation and philosopher parameters.
 * Initializes mutexes and starts philosopher threads.
 * Waits for philosopher threads to finish and destroys mutexes.
 * @param sim The simulation parameters.
 * @param philo The philosopher parameters.
 */
void	run_simulation(t_Simulation *sim, t_Philosopher *philo)
{
	int	i;

	if (init_mutexes(sim) == 1)
	{
		printf("Error initializing mutexes\n");
		exit(4);
	}
	sim->start_time = get_time_ms();
	i = 0;
	while (i < sim->num_philosophers)
	{
		pthread_create(&philo[i].thread, NULL, philosopher_life, &philo[i]);
		i++;
	}
	i = 0;
	while (i < sim->num_philosophers)
		pthread_join(philo[i++].thread, NULL);
	destroy_mutexes(sim);
}

/**
 * The main function of the program 
 * that creates and runs the simulation of the dining philosophers problem.
 * 
 * @param argc The number of arguments passed to the program.
 * @param argv An array of strings containing the arguments.
 * @return Returns 0 if the program runs successfully, otherwise returns 1.
 */
int	main(int argc, char *argv[])
{
	t_Simulation	sim;
	t_Philosopher	*philosophers;

	check_args(argc, argv);
	init_var_sim(&sim, argc, argv);
	philosophers = malloc(sizeof(t_Philosopher) * (sim.num_philosophers));
	if (!philosophers)
	{
		printf("Error allocating memory for philosophers\n");
		return (1);
	}
	create_philos(&sim, philosophers);
	run_simulation(&sim, philosophers);
	free(philosophers);
	free(sim.forks);
	return (0);
}
