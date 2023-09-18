/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:51:44 by paulo             #+#    #+#             */
/*   Updated: 2023/09/18 12:11:40 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// atualizar cabeçalho

#include "../includes/philosophers.h"

// Função para realizar a ação de dormir
void sleep_philo(t_Philosopher *philo) {
    if (should_die(philo)) {
        philo->state = DEAD;
        print_message(philo, "died");
        exit(0);
    }

    philo->state = SLEEPING;
    print_message(philo, "is sleeping");
    usleep(philo->sim->time_to_sleep * 1000);
}

// Função para realizar a ação de pensar
void think_philo(t_Philosopher *philo) 
{
    if (should_die(philo)) {
        philo->state = DEAD;
        print_message(philo, "died");
        return;
    }

    philo->state = THINKING;
    print_message(philo, "is thinking");
}

// Função para realizar a ação de comer
void	eat_philo(t_Philosopher *philo) 
{
	int	left_fork;
	int	right_fork;

	if (should_die(philo))
	{
		philo->state = DEAD;
		print_message(philo, "died");
		return;
	}

	philo->meals_left--;

	left_fork = philo->id;
	right_fork = (philo->id + 1) % philo->sim->num_philosophers;

	// Lock no garfo à esquerda
	pthread_mutex_lock(&philo->sim->forks[left_fork].lock);
    if (!philo->sim->forks[left_fork].is_available)
	{
		// Se o garfo à esquerda não estiver disponível, liberamos o garfo e saímos
		pthread_mutex_unlock(&philo->sim->forks[left_fork].lock);
		philo->state = THINKING;
		return;
	}
	print_message(philo, "has taken left fork");

	// Lock no garfo à direita
	pthread_mutex_lock(&philo->sim->forks[right_fork].lock);
	if (!philo->sim->forks[right_fork].is_available) 
	{
		// Se o garfo à direita não estiver disponível, liberamos ambos os garfos e saímos
		pthread_mutex_unlock(&philo->sim->forks[left_fork].lock);
		philo->state = THINKING;
		return;
	}
	print_message(philo, "has taken right fork");

	// Marcamos os garfos como não disponíveis
	philo->sim->forks[left_fork].is_available = 0;
	philo->sim->forks[right_fork].is_available = 0;

	philo->last_meal_time = total_time(philo->sim);
	philo->state = EATING;
	print_message(philo, "is eating");
	usleep(philo->sim->time_to_eat * 1000);

	// Liberamos os garfos
	philo->sim->forks[left_fork].is_available = 1;
	philo->sim->forks[right_fork].is_available = 1;

	pthread_mutex_unlock(&philo->sim->forks[left_fork].lock);
	pthread_mutex_unlock(&philo->sim->forks[right_fork].lock);

	philo->state = SLEEPING;
}

// Função que define o ciclo de vida de um filósofo
void *philosopher_life(void *arg) 
{
	t_Philosopher *philo;

	philo = (t_Philosopher *)arg;
	while (philo->meals_left != 0) 
	{
		eat_philo(philo);
		sleep_philo(philo);
		think_philo(philo);
	}
	return (NULL);
}
