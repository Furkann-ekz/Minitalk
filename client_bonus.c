/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fekiz <fekiz@student.42istanbul.com.tr     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:00:12 by fekiz             #+#    #+#             */
/*   Updated: 2023/11/30 19:35:01 by fekiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"
#include "stdlib.h"
#include "signal.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	count;

	i = 0;
	sign = 1;
	count = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		count = (str[i] - 48) + (10 * count);
		i++;
	}
	return (count * sign);
}

void	signal_giver(int pid, unsigned char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if ((c >> i) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i++;
		usleep (50);
	}
}

int	main(int argc, char **argv)
{
	int	i;

	i = -1;
	if (argc != 3)
	{
		write (1, "Gecersiz kullanim. ", 19);
		write (1, "Lutfen ./client <PID> <MESSAGE> ", 32);
		write (1, "seklinde giris yapiniz...", 25);
		exit (-1);
	}
	while (argv[2][++i])
		signal_giver(ft_atoi(argv[1]), argv[2][i]);
}
