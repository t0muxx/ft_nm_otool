/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 08:15:17 by tmaraval          #+#    #+#             */
/*   Updated: 2019/11/15 10:43:53 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	print_file_type(t_infile *file, char *type)
{
	if (file->type_printed == 0)
	{
		if (!ft_strcmp("Archive : ", type))
			ft_printf("%s%s\n", type, file->filename);
		else
			ft_printf("%s%s:\n", type, file->filename);
		file->type_printed = 1;
	}
}

int		print_text_bytes(t_infile *file, uint8_t *current, uint32_t print)
{
	int		i;
	uint8_t *byte;
	int		nb;
	char	base[16];

	nb = 0;
	ft_strcpy(base, "0123456789abcdef")	;
	i = 0;
	byte = current;
	while (i < 16 && print)
	{
		if (protect(file, byte) < 0)
			return (-1);
		nb = *byte / 16;
		ft_putchar(base[nb]);
		nb = *byte % 16;
		ft_putchar(base[nb]);
		ft_putstr(" ");
		i++;
		byte++;
		print--;
		if (protect(file, byte) < 0)
			return (-1);
	}
	return (0);
}
