/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-moun <eel-moun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 14:27:57 by eel-moun          #+#    #+#             */
/*   Updated: 2022/04/21 15:10:15 by eel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int	ft_atoi(const char *str)
{
	int	res;

	res = 0;
	while (*str >= 48 && *str <= 57)
	{
		res = (res * 10) + (*str - 48);
		str++;
	}
	return (res);
}

void	sig_sender(char *str, pid_t pid)
{
	int	bitshift;

	bitshift = 0;
	while (*str)
	{
		while (bitshift < 8)
		{
			if (*str & (128 >> bitshift))
			{	
				if (kill(pid, SIGUSR1) == -1)
					exit(1);
				usleep(400);
			}
			else
			{
				if (kill(pid, SIGUSR2) == -1)
					exit(1);
				usleep(400);
			}
			bitshift++;
		}
		str++;
		bitshift = 0;
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3)
		return (0);
	if (!(argv[1][0] >= '0' && argv[1][0] <= '9'))
		return (0);
	if (!argv[2])
		return (0);
	pid = ft_atoi(argv[1]);
	sig_sender(argv[2], pid);
	return (0);
}
