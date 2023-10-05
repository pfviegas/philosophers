/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:05:29 by pviegas           #+#    #+#             */
/*   Updated: 2023/10/05 14:55:31 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/**
 * @brief Prints a message with the philosopher's ID and 
 * the current simulation time.
 * 
 * @param philo Pointer to the philosopher struct.
 * @param message The message to be printed.
 */
void	print_msg(t_Philosopher *philo, char *message, int sim_lock)
{
	if (sim_lock)
		pthread_mutex_lock(&philo->sim->simulation_lock);
	pthread_mutex_lock(&philo->sim->print_lock);
//	if (philo->sim->simulation_running == 1 || philo->state == DEAD)
	if (philo->sim->simulation_running == 1)
	{
		printf("%ld %d %s\n", (get_time_ms(&philo->sim->time_lock) - philo->sim->start_time), philo->id, message);
	}
	pthread_mutex_unlock(&philo->sim->print_lock);
	if (sim_lock)
		pthread_mutex_unlock(&philo->sim->simulation_lock);
}

// long int	get_time_ms(void)
long int	get_time_ms(pthread_mutex_t *mutex)
{
	struct timeval	current_time;

	if (mutex)
	{
		pthread_mutex_lock(mutex);
		gettimeofday(&current_time, NULL);
		pthread_mutex_unlock(mutex);
	}
	else
		gettimeofday(&current_time, NULL);


	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

int	died(t_Philosopher *philo)
{

	pthread_mutex_lock(&philo->sim->simulation_lock);
	if ((get_time_ms(&philo->sim->time_lock) - philo->last_meal_time)
		>= philo->sim->time_to_die)
	{
		if (philo->sim->simulation_running == 1)
		{
			print_msg(philo, "died", 0);
		}
		philo->sim->simulation_running = 0;
		philo->state = DEAD;
		pthread_mutex_unlock(&philo->sim->simulation_lock);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo->sim->simulation_lock);
		return (0);
	}
}

void	action_philo(long int time, t_Philosopher *philo)
{
//	long int	start_time;
	
	//pthread_mutex_lock(&philo->sim->start_time_lock);
	
//	start_time = get_time_ms();
	philo->start_time = get_time_ms(&philo->sim->time_lock);
//	printf("time: %ld\n", time);
//	sleep(1);
//	printf("t.p.: %ld\n", get_time_ms() - philo->start_time);

	while ((get_time_ms(&philo->sim->time_lock) - philo->start_time) < time)
	{
		if (died(philo))
		{
	//		pthread_mutex_unlock(&philo->sim->start_time_lock);
			return ;
		}
//		usleep(10);
	}
//	printf("tempo passado: %ld\n", get_time_ms() - philo->start_time);
	//pthread_mutex_unlock(&philo->sim->start_time_lock);
//	sleep(1);
}