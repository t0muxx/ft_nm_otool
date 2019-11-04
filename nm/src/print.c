/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:10:27 by tmaraval          #+#    #+#             */
/*   Updated: 2019/11/04 15:14:59 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"


void		lst_symbol_print_32(t_symbol *head)
{
	lst_symbol_sort(head);
	while (head)
	{
		if (head->symb_char != 'U')
		{
			if (head->symb_char == 'I')
			{
				ft_printf("%s %c %s (indirect for %s)\n", "        ",
					head->symb_char, head->symbol_name,	head->symbol_name);
			}
			ft_printf("%08lx %c %s\n", head->symb_value, head->symb_char,
				head->symbol_name);
		}
		else
		{
			ft_printf("%s %c %s\n", "        ",	head->symb_char,
				head->symbol_name);

		}
		head = head->next;
	}
}

void		lst_symbol_print_64(t_symbol *head)
{
	lst_symbol_sort(head);
	while (head)
	{
		if (head->symb_char != 'U')
		{
			if (head->symb_char == 'I')
			{
				ft_printf("%s %c %s (indirect for %s)\n", 
					"                ",
					head->symb_char,
					head->symbol_name,
					head->symbol_name);
			}
			else
			{
				ft_printf("%016lx %c %s\n", 
					head->symb_value,
					head->symb_char,
					head->symbol_name);
			}
		}
		else
		{
			ft_printf("%s %c %s\n", 
					"                ",
					head->symb_char,
					head->symbol_name);

		}
		head = head->next;
	}
}
