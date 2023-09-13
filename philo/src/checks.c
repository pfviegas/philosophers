/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:20:16 by paulo             #+#    #+#             */
/*   Updated: 2023/09/13 15:04:18 by paulo            ###   ########.fr       */
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
