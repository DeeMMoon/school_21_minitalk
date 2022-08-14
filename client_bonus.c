/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gantedil <gantedil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 14:38:37 by gantedil          #+#    #+#             */
/*   Updated: 2022/02/12 14:51:52 by gantedil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int	g_confirm = 0;

static long	ft_drop(char *p)
{
	long	i;

	i = 0;
	while (p[i] != '\0' && (p[i] == '\t' || p[i] == '\n' || p[i] == '\r'
			|| p[i] == '\v' || p[i] == '\f' || p[i] == ' '))
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	char	*p;
	long	i;
	long	num;
	int		minus;

	minus = 0;
	p = (char *)str;
	i = ft_drop(p);
	if (p[i] == '-' || p[i] == '+')
	{
		if (p[i] == '-')
			minus++;
		i++;
	}
	num = 0;
	while (p[i] && p[i] >= 48 && p[i] <= 57)
	{
		num = num * 10 + (p[i] - '0');
		i++;
	}
	if (minus == 1)
		return (-num);
	return (num);
}

void	ft_client_hanler(int signal)
{
	if (signal == SIGUSR1)
		g_confirm = 1;
	if (signal == SIGUSR2)
		write(1, "Message received\n", 17);
}

void	send_symbol(int pid, char c)
{
	int	n;

	n = 128;
	while (n > 0)
	{
		usleep (150);
		if (c & n)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (g_confirm != 1)
			usleep(1);
		n = n / 2;
		g_confirm = 0;
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	i = 0;
	if (argc < 3)
		return (0);
	pid = ft_atoi(argv[1]);
	signal (SIGUSR1, ft_client_hanler);
	signal (SIGUSR2, ft_client_hanler);
	while (argv[2][i] != '\0')
	{
		send_symbol (pid, argv [2][i]);
		i++;
	}
	send_symbol(pid, argv[2][i]);
	return (0);
}
