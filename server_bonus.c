/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fekiz <fekiz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 18:33:09 by fekiz             #+#    #+#             */
/*   Updated: 2025/10/26 18:54:29 by fekiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"
#include "signal.h"

int	ft_printf(const char *str, ...);

void	signal_handler(int sig, siginfo_t *info, void *zero)
{
	static int	n;
	static int	result;
	static int	pid;

	(void)zero;
	if (pid != info->si_pid)
	{
		pid = info->si_pid;
		n = 0;
		result = 0;
	}
	if (sig == SIGUSR1)
		result += (1 << n);
	n++;
	if (n == 8)
	{
		write(1, &result, 1);
		n = 0;
		result = 0;
	}
	kill(pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	signals;

	ft_printf("%d\n", getpid());
	signals.sa_sigaction = signal_handler;
	sigemptyset(&signals.sa_mask);
	signals.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &signals, NULL);
	sigaction(SIGUSR2, &signals, NULL);
	while (1)
		pause();
}
