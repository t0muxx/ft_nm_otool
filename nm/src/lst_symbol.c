/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_symbol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:42:09 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/24 16:54:55 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void		lst_symbol_print(t_symbol *head)
{
	while (head)
	{
		printf("symbol : %s\n", head->symbol_name);
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

t_symbol	*lst_symbol_new(void *ptr, char *str, size_t str_len)
{
	t_symbol *new;

	if (!(new = (t_symbol *)malloc(sizeof(t_symbol))))
		return (NULL);
	new->symbol = ptr;
	printf("malloc de %lu\n", str_len+1);
	if (!(new->symbol_name = (char *)malloc(str_len+1)))
	{
		free(new);
		return (NULL);
	}
	ft_strncpy(new->symbol_name, str, str_len);
	new->symbol_name[str_len] = '\0';
	new->next = NULL;
	return (new);
}

void		lst_symbol_append(t_symbol **head, t_symbol *new)
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

