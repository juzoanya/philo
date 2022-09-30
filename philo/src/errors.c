/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juzoanya <juzoanya@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 14:12:07 by juzoanya          #+#    #+#             */
/*   Updated: 2022/07/15 15:49:07 by juzoanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	err_handler(int n)
{
	if (n == 0)
	{
		printf("ERROR: Arguments initialization failed!"
			" OR Philosophers less than 2!");
		exit(0);
	}
	if (n == 2)
	{
		printf("ERROR: Memory Allocation Failure!");
		exit(0);
	}
	if (n == 3)
	{
		printf("ERROR:Thread Creation Failure!");
		exit(0);
	}
	if (n == 4)
	{
		printf("ERROR:Thread Join Failure!");
		exit(0);
	}
}
