/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:46:10 by jose-jim          #+#    #+#             */
/*   Updated: 2024/10/31 12:41:04 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
/*
int main()
{
   if(ft_isascii(89))
     printf("TRUE");

   else
    printf("FALSE");

  return 0;
}*/
