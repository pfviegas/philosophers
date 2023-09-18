/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:51:44 by paulo             #+#    #+#             */
/*   Updated: 2023/09/16 21:14:47 by paulo            ###   ########.fr       */
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
	if (should_die(philo))
	{
		philo->state = DEAD;
		print_message(philo, "died");
		return;
	}

	philo->meals_left--;

	pthread_mutex_lock(&philo->sim->forks[philo->id]);
	print_message(philo, "has taken a fork");

	pthread_mutex_lock(&philo->sim->forks[(philo->id + 1) % philo->sim->num_philosophers]);
	print_message(philo, "has taken a fork");

	philo->last_meal_time = total_time(philo->sim);
	philo->state = EATING;
	print_message(philo, "is eating");

	usleep(philo->sim->time_to_eat * 1000);

	pthread_mutex_unlock(&philo->sim->forks[philo->id]);
	pthread_mutex_unlock(&philo->sim->forks[(philo->id + 1) % philo->sim->num_philosophers]);

	philo->state = THINKING;
}

// Função que define o ciclo de vida de um filósofo
void *philosopher_life(void *arg) 
{
	t_Philosopher *philo;

	philo = (t_Philosopher *)arg;
	while (philo->meals_left != 0) 
	{
		eat_philo(philo);
		think_philo(philo);
		sleep_philo(philo);
	}
	return (NULL);
}
