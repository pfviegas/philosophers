/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:20:16 by paulo             #+#    #+#             */
/*   Updated: 2023/09/16 15:34:41 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// atualizar cabeçalho

#include "../includes/philosophers.h"

/**
 * @brief Converte uma string para um valor inteiro.
 *
 * A função `ft_atoi` converte a string `str` em um valor inteiro.
 *
 * @param str A string a ser convertida.
 * @return O valor inteiro convertido.
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
 * @brief Verifica se um caractere é um dígito decimal.
 *
 * A função `ft_isdigit` verifica se o caractere `c` é um dígito decimal (0-9).
 *
 * @param c O caractere a ser verificado.
 * @return 1 se o caractere for um dígito decimal, 0 caso contrário.
 */
int	ft_isdigit(int c)
{
	return ((c >= '0' && c <= '9'));
}

/**
 * Initializes the simulation variables with the values passed as arguments.
 * 
 * @param simulation Pointer to the Simulation struct to be initialized.
 * @param argc Number of arguments passed to the program.
 * @param argv Array of strings containing the arguments passed to the program.
 */
void init_var_sim(t_Simulation *simulation, int argc, char *argv[]) 
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

/**
 * Initializes the philosophers in the simulation with their respective attributes.
 * @param simulation The simulation struct containing the number of philosophers and other parameters.
 * @param philosopher The philosopher struct containing the philosopher's id, meals_left, state, last_meal_time and sim.
 */
void create_philisophers(t_Simulation *simulation, t_Philosopher *philosopher)
{
	int i;

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
