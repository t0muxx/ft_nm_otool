/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_symbol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:42:09 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/30 14:26:25 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void		lst_symbol_print_64(t_symbol *head)
{
	while (head)
	{
		if (head->symb_char != 'U')
		{
			ft_printf("%016lx %c %s\n", 
					head->symb_value,
					head->symb_char,
					head->symbol_name);
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

void		lst_symbol_print_32(t_symbol *head)
{
	while (head)
	{
		if (head->symb_char != 'U')
		{
			ft_printf("%08lx %c %s\n", 
					head->symb_value,
					head->symb_char,
					head->symbol_name);
		}
		else
		{
			ft_printf("%s %c %s\n", 
					"        ",
					head->symb_char,
					head->symbol_name);

		}
		head = head->next;
	}
}

void		lst_symbol_free(t_symbol *head)
{
	t_symbol *tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->symbol_name);
		free(tmp);
		tmp = NULL;
	}
	head = NULL;
}

t_symbol	*lst_symbol_new(void *ptr, char *str, size_t str_len, uint64_t val)
{
	t_symbol *new;

	if (!(new = (t_symbol *)malloc(sizeof(t_symbol))))
		return (NULL);
	new->symbol = ptr;
	if (!(new->symbol_name = (char *)malloc(str_len+1)))
	{
		free(new);
		return (NULL);
	}
	ft_strncpy(new->symbol_name, str, str_len);
	new->symbol_name[str_len] = '\0';
	new->symb_char = 0;
	new->symb_value = val;
	new->next = NULL;
	return (new);
}

void		lst_symbol_append_nosort(t_symbol **head, t_symbol *new)
{
	t_symbol *last;

	last = *head;
	new->next = NULL;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new;
	return ;

}

void		lst_symbol_append(t_symbol **last, t_symbol *new)
{
	t_symbol *current;

	if (*last == NULL ||
			ft_strcmp((*last)->symbol_name, new->symbol_name) > 0)
	{
		new->next = *last;
		*last = new;
	}
	else
	{
		current = *last;
		while (current->next != NULL &&
		ft_strcmp(current->next->symbol_name, new->symbol_name) <= 0)
			current = current->next;
		while (current->next != NULL && 
				!ft_strcmp(current->next->symbol_name, new->symbol_name)
				&& new->symb_value > current->next->symb_value)
			current = current->next;
		new->next = current->next;
		current->next = new;
	}
	return ;
}

