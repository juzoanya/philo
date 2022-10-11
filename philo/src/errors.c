/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juzoanya <juzoanya@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 14:12:07 by juzoanya          #+#    #+#             */
/*   Updated: 2022/10/10 22:09:47 by juzoanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	err_handler(int err_code)
{
	if (err_code == 0)
	{
		printf("Argument count less than run threshold \
			requirement OR arguments contain alphabet(s)\n");
		return (0);
	}
	else if (err_code == 1)
	{
		printf("Argument initialization error\n");
		return (0);
	}
	else if (err_code == 2)
	{
		printf("mutex initialization error\n");
		return (0);
	}
	else if (err_code == 3)
		printf("memory allocation error\n");
	// else if (err_code == 4)
	// {
	// 	printf("mutex initialization error\n");
	// 	return (0);
	// }
	return (0);
}
