/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:47:15 by jose-jim          #+#    #+#             */
/*   Updated: 2024/10/31 12:41:25 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	digits(long int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n == -2147483648)
		return (10);
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	symbol(long int nbr)
{
	if (nbr < 0)
		return (1);
	else
		return (0);
}

char	*ft_itoa(int n)
{
	char		*res;
	int			neg;
	int			size;
	long int	nbr;

	nbr = (long)n;
	neg = symbol(nbr);
	nbr = nbr * (-2 * neg + 1);
	size = digits(nbr);
	res = (char *)malloc(sizeof(char) * (size + neg + 1));
	if (res == NULL)
		return (NULL);
	if (n == 0)
		res[0] = '0';
	if (neg == 1)
		res[0] = '-';
	res[size + neg] = '\0';
	while (nbr > 0)
	{
		res[--size + neg] = nbr % 10 + '0';
		nbr = nbr / 10;
	}
	return (res);
}
/*
int main() {
    int test_cases[] = {12345, -9876, 0, 2147483647, -2147483648};
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    printf("Testing ft_itoa:\n");
    for (int i = 0; i < num_tests; ++i) {
        int number = test_cases[i];
        char *result = ft_itoa(number);
        printf("Number: %d, Result: %s\n", number, result);
    }

    return 0;
}*/
