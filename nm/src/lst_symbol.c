/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_symbol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:33:55 by tmaraval          #+#    #+#             */
/*   Updated: 2019/11/04 16:34:46 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void		lst_symbol_swap(t_symbol *node1, t_symbol *node2)
{
	t_symbol	temp;
	size_t		lenght;

	lenght = sizeof(t_symbol) - sizeof(t_symbol *);
	ft_memcpy(&temp, node1, lenght);
	ft_memcpy(node1, node2, lenght);
	ft_memcpy(node2, &temp, lenght);
}

void		lst_symbol_sort(t_symbol *start)
{
	int			swapped;
	t_symbol	*ptr1;
	t_symbol	*lptr;

	lptr = NULL;
	if (start == NULL)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr1 = start;
		while (ptr1->next != lptr)
		{
			if (ft_strcmp(ptr1->symbol_name, ptr1->next->symbol_name) > 0 ||
				(!ft_strcmp(ptr1->symbol_name, ptr1->next->symbol_name) &&
				ptr1->symb_value > ptr1->next->symb_value))
			{
				lst_symbol_swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
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
	if (!(new->symbol_name = (char *)malloc(str_len + 1)))
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
