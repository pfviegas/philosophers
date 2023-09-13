/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:20:16 by paulo             #+#    #+#             */
/*   Updated: 2023/09/13 12:58:18 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// atualizar cabeçalho

#include "../includes/philosophers.h"

// imprime a mensagem de erro, liberta a memória e encerra o programa 
// de maneira controlada quando ocorrem erros ou situações excepcionais. 
void	quit(char *s, int exit_code)
{
	printf("Error\n%s\n(%d)\n", s, exit_code);
	exit(exit_code);
}
