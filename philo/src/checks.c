/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:05:16 by pviegas           #+#    #+#             */
/*   Updated: 2023/10/03 14:49:18 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	check_args(int argc, char *argv[])
{
	check_argc(argc, argv);
	check_argv(argv);
}
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
		num_meals = 0;
	if (num_philos < 1 || num_philos > 200 || time_to_die < 0
		|| time_to_eat < 0 || time_to_sleep < 0
		|| num_meals < 0)
	{
		printf("Error: Invalid arguments\n");
		exit (3);
	}
}
