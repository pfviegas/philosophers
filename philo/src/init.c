/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:33:00 by pviegas           #+#    #+#             */
/*   Updated: 2023/10/06 16:14:38 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/**
 * @brief Converts a string to an integer.
 * 
 * @param str The string to be converted.
 * @return The integer representation of the string.
 */
int	ft_atoi(const char *str)
{
	int	sign;
	int	res;

	sign = 1;
	res = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
	{
		str++;
	}
	while (ft_isdigit(*str))
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (sign * res);
}

/**
 * @brief Checks if a character is a digit.
 * 
 * @param c The character to be checked.
 * @return int Returns 1 if the character is a digit, 0 otherwise.
 */
int	ft_isdigit(int c)
{
	return ((c >= '0' && c <= '9'));
}

/**
 * @brief Initializes the simulation variables with the values 
 * passed as arguments.
 * 
 * @param simulation Pointer to the Simulation struct to be initialized.
 * @param argc Number of arguments passed to the program.
 * @param argv Array of strings containing the arguments.
 */
void	init_var_sim(t_Simulation *sim, int argc, char *argv[])
{
	sim->num_philosophers = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		sim->total_meals = ft_atoi(argv[5]);
	else
		sim->total_meals = -1;
	sim->simulation_running = 1;
}

/**
 * Initializes the mutexes and forks for the simulation.
 * 
 * @param sim Pointer to the simulation struct.
 * @return Returns 0 if successful, otherwise returns 1.
 */
int	init_mutexes(t_Simulation *sim)
{
	int	i;

	if (pthread_mutex_init(&sim->simulation_lock, NULL))
		return (1);
	if (pthread_mutex_init(&sim->print_lock, NULL))
		return (1);
	if (pthread_mutex_init(&sim->meals_lock, NULL))
		return (1);
	if (pthread_mutex_init(&sim->time_lock, NULL))
		return (1);
	if (pthread_mutex_init(&sim->start_time_lock, NULL))
		return (1);
	sim->forks = malloc(sizeof(t_Fork) * (sim->num_philosophers));
	if (!sim->forks)
	{
		printf("Error allocating memory for forks\n");
		exit (5);
	}
	i = -1;
	while (++i < sim->num_philosophers)
	{
		sim->forks[i].is_available = 1;
		pthread_mutex_init(&sim->forks[i].lock, NULL);
	}
	return (0);
}

/**
 * @brief Initializes the philosophers in the simulation 
 * with their respective attributes.
 * 
 * @param sim The simulation struct containing the number 
 * of philosophers and other parameters.
 * @param philosopher The philosopher struct containing the philosopher's id, 
 * meals_left, state, last_meal_time and sim.
 */
void	create_philos(t_Simulation *sim, t_Philosopher *philosopher)
{
	int	i;

	i = 0;
	while (i < sim->num_philosophers)
	{
		philosopher[i].id = i + 1;
		philosopher[i].meals_left = sim->total_meals;
		philosopher[i].state = THINKING;
		philosopher[i].last_meal_time = get_time_ms();
		philosopher[i].sim = sim;
		i++;
	}
}
