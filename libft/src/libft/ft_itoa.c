/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:34:32 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/06/01 17:15:37 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

/*
 *	Function get_num_of_digits returns number of digits in the number
*/
static size_t	get_num_of_digits(int n)
{
	size_t	num;

	num = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		num++;
	}
	while (n > 0)
	{
		num++;
		n /= 10;
	}
	return (num);
}

char	*ft_itoa(int n)
{
	char	*str_num;
	size_t	num_of_digits;

	num_of_digits = get_num_of_digits(n);
	str_num = (char *)malloc((num_of_digits + 1) * sizeof(char));
	if (!str_num)
		return (NULL);
	str_num[num_of_digits--] = 0;
	if (n == 0)
	{
		free(str_num);
		return (ft_strdup("0"));
	}
	if (n < 0)
	{
		str_num[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		str_num[num_of_digits] = n % 10 + '0';
		n /= 10;
		num_of_digits--;
	}
	return (str_num);
}
