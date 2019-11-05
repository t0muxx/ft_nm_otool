/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_bytes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 11:18:24 by tmaraval          #+#    #+#             */
/*   Updated: 2019/11/05 16:50:53 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

uint8_t		reverse_8(uint8_t should, uint8_t num)
{
	uint8_t b;
	
	b = num;
	if (should == 0)
		return (num);
	b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
	b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
	b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
	return (b);
}

uint32_t	reverse_32(uint8_t should, uint32_t num)
{
	uint32_t ret;

	ret = 0;
	if (should == 1)
	{
		ret = ((num & 0x000000FF) << 24) |
			((num & 0x0000FF00) << 8) |
			((num & 0x00FF0000) >> 8) |
			((num & 0xFF000000) >> 24);
	}
	else
		return (num);
	return (ret);
}

uint64_t	reverse_64(uint8_t should, uint64_t num)
{
	uint64_t ret;

	ret = 0;
	if (should == 1)
	{
		ret = ((num & 0x00000000000000FFULL) << 56) |
			((num & 0x000000000000FF00ULL) << 40) |
			((num & 0x0000000000FF0000ULL) << 24) |
			((num & 0x00000000FF000000ULL) << 8) |
			((num & 0x000000FF00000000ULL) >> 8) |
			((num & 0x0000FF0000000000ULL) >> 24) |
			((num & 0x00FF000000000000ULL) >> 40) |
			((num & 0xFF00000000000000ULL) >> 56);
	}
	else
		return (num);
	return (ret);
}
