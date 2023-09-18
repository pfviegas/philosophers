/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:20:16 by paulo             #+#    #+#             */
/*   Updated: 2023/09/18 12:21:17 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// atualizar cabeçalho

#include "../includes/philosophers.h"


// Função para criar e iniciar a simulação
void run_simulation(t_Simulation *sim, t_Philosopher *philosopher)
{
	int i;
	
	sim->forks = malloc(sizeof(t_Philosopher) * (sim->num_philosophers + 1));
	pthread_mutex_init(&sim->print_lock, NULL);
	// Inicialização dos garfos
	i = 0;
	while(i < sim->num_philosophers)
	{	
		pthread_mutex_init(&sim->forks[i].lock, NULL);
		sim->forks[i].is_available = 1;
		i++;
//		pthread_mutex_init(&sim->forks[i++], NULL);
	}

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

	// Criação dos filósofos
	philosophers = malloc(sizeof(t_Philosopher) * (sim.num_philosophers));
	create_philisophers(&sim, philosophers);

	// Executa a simulação
	run_simulation(&sim, philosophers);
	
	return (0);
}
