/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:20:16 by paulo             #+#    #+#             */
/*   Updated: 2023/09/13 17:23:26 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// atualizar cabeçalho

#include "../includes/philosophers.h"

void	init_var_sim(t_Simulation *simulation, int argc, char *argv[])
{
	simulation->num_philosophers = ft_atoi(argv[1]);
	simulation->time_to_die = ft_atoi(argv[2]);
	simulation->time_to_eat = ft_atoi(argv[3]);
	simulation->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		simulation->eat_count = atoi(argv[5]);
	else
		simulation->eat_count = -1;
}

void	create_philisophers(t_Simulation *simulation, t_Philosopher *philosopher)
{
	int				i;
//	t_Philosopher	*philosopher;

//	philosopher = malloc(sizeof(t_Philosopher) * (simulation->num_philosophers + 1));
	i = 0;
	while (i < simulation->num_philosophers)
	{

		philosopher[i].id = i + 1;
		philosopher[i].meals_left = simulation->eat_count;
		philosopher[i].state = THINKING;
		philosopher[i].last_meal_time = 0;
		philosopher[i].sim = simulation;
		i++;
	}
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
	for (int i = 0; i < sim.num_philosophers; i++) {
		printf("philosopher id : %d\n", philosophers[i].id);
		printf("meals left : %d\n", philosophers[i].meals_left);
		printf("state id : %u\n", philosophers[i].state);
		printf("last meal time : %ld\n", philosophers[i].last_meal_time);
		printf("philosopher sim : %p\n\n", philosophers[i].sim);
	}
/*
	// Executa a simulação
	run_simulation(&sim, philosophers);

*/
	return (0);
}
