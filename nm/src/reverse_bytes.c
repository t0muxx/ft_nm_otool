/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_bytes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 11:18:24 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/25 11:38:48 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

uint8_t reverse_8(uint8_t should, uint8_t num)
{
	uint8_t ret;
	uint32_t i;
	uint8_t temp;

	ret = 0;
	i = 0;
	temp = 0;
	if (should == 1)
	{
		while (i < sizeof(num) * 8)
		{
			temp = (num & (1 << i));
			if(temp)
				ret |= (1 << ((sizeof(num) * 8 - 1) - i));
			i++;
		}
    }
	else
		return (num);
    return ret;
}

uint32_t reverse_32(uint8_t should, uint32_t num)
{
	uint32_t ret;
	uint32_t i;
	uint32_t temp;

	ret = 0;
	i = 0;
	temp = 0;
	if (should == 1)
	{
		while (i < sizeof(num) * 8)
		{
			temp = (num & (1 << i));
			if(temp)
				ret |= (1 << ((sizeof(num) * 8 - 1) - i));
			i++;
		}
    }
	else
		return (num);
    return ret;
}

uint64_t reverse_64(uint8_t should, uint64_t num)
{
	uint64_t ret;
	uint64_t i;
	uint64_t temp;

	ret = 0;
	i = 0;
	temp = 0;
	if (should == 1)
	{
		while (i < sizeof(num) * 8)
		{
			temp = (num & (1 << i));
			if(temp)
				ret |= (1 << ((sizeof(num) * 8 - 1) - i));
			i++;
		}
    }
	else
		return (num);
    return ret;
}
