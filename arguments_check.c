/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albozkur <albozkur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:30:30 by albozkur          #+#    #+#             */
/*   Updated: 2024/04/02 13:58:32 by albozkur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	check_av(int ar, char **av)
{
	int	i;
	int	j;

	i = 1;
	if (ar != 5 && ar != 6)
		return (1);
	while (av[i])
	{
		j = 0;
		if (av[i][j] == '+')
			j++;
		while (av[i][j])
		{
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

long	ft_atoi(char *num)
{
	int	number;
	int	i;

	i = 0;
	number = 0;
	while (num[i])
	{
		number = number * 10 + (num[i] - '0');
		i++;
	}
	return (number);
}
