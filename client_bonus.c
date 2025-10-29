/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fekiz <fekiz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 18:33:22 by fekiz             #+#    #+#             */
/*   Updated: 2025/10/26 19:00:01 by fekiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"
#include "stdlib.h"
#include "signal.h"

int	g_control;

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
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (-1);
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
		g_control = 0;
		if ((c >> i) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i++;
		while (g_control == 0)
			pause();
	}
}

void	signal_handler(int sig)
{
	if (sig == SIGUSR1)
		g_control = 1;
}

int	main(int argc, char **argv)
{
	int	i;

	i = -1;
	if (argc != 3 || ft_atoi(argv[1]) == -1)
	{
		write (1, "Gecersiz kullanim. ", 19);
		write (1, "Lutfen ./client <PID> <MESSAGE> ", 32);
		write (1, "seklinde giris yapiniz...", 25);
		exit (-1);
	}
	signal(SIGUSR1, signal_handler);
	while (argv[2][++i])
		signal_giver(ft_atoi(argv[1]), argv[2][i]);
}
