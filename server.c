/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fekiz <fekiz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 18:33:13 by fekiz             #+#    #+#             */
/*   Updated: 2025/10/26 18:54:14 by fekiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"
#include "signal.h"

int	ft_printf(const char *str, ...);

void	signal_handler(int sig)
{
	static int	n;
	static int	result;

	if (sig == SIGUSR1)
		result += (1 << n);
	n++;
	if (n == 7)
	{
		write(1, &result, 1);
		n = 0;
		result = 0;
	}
}

int	main(void)
{
	ft_printf("%d\n", getpid());
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	while (1)
		pause();
}
