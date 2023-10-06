/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:05:16 by pviegas           #+#    #+#             */
/*   Updated: 2023/10/06 17:12:09 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/**
 * Check the validity of the arguments passed to the program.
 * 
 * @param argc The number of arguments passed to the program.
 * @param argv The array of arguments passed to the program.
 */
void	check_args(int argc, char *argv[])
{
	check_argc(argc, argv);
	check_argv(argv);
}

/**
 * Checks the number of arguments and their validity.
 * Exits the program with an error message if the arguments are invalid.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv An array of strings containing the arguments.
 */
void	check_argc(int argc, char *argv[])
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
	{
		printf("Sixtax Error: Wrong number of arguments\n");
		printf("Arguments:\n\t./philo\n\tnumber_of_philosophers\n\t");
		printf("time_to_die\n\ttime_to_eat\n\ttime_to_sleep\n\t");
		printf("[number_of_times_each_philosopher_must_eat]\n");
		exit (1);
	}
	j = 0;
	while (argv[++j])
	{
		i = -1;
		while (argv[j][++i])
		{
			if (!ft_isdigit(argv[j][i]))
			{
				printf("Error: invalid value (%s)\n", argv[j]);
				exit(2);
			}
		}
	}
}

/**
 * This function checks the validity of the command line arguments.
 * It takes an array of strings as input, representing the arguments.
 * The function converts the arguments to integers and checks 
 * if they are within the valid range.
 * 
 * @param argv An array of strings representing the command line arguments.
 * @return void
 */
void	check_argv(char *argv[])
{
	int	num_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_meals;

	num_philos = ft_atoi(argv[1]);
	time_to_die = ft_atoi(argv[2]);
	time_to_eat = ft_atoi(argv[3]);
	time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		num_meals = ft_atoi(argv[5]);
	else
		num_meals = 1;
	if (num_philos < 1 || num_philos > 200 || time_to_die < 60
		|| time_to_eat < 60 || time_to_sleep < 60
		|| num_meals <= 0)
	{
		printf("Error: Invalid arguments\n");
		exit (3);
	}
}

/**
 * Checks if there is only one philosopher and handles its actions.
 * 
 * @param philo Pointer to the philosopher struct.
 * @return 1 if there is only one philosopher, 0 otherwise.
 */
int	one_philo(t_Philosopher *philo)
{
	if (philo->sim->num_philosophers == 1)
	{
		print_msg(philo, "is thinking", 1);
		usleep(philo->sim->time_to_die * 1000);
		print_msg(philo, "died", 1);
		return (1);
	}
	if (!(philo->id % 2))
		usleep(100);
	return (0);
}
