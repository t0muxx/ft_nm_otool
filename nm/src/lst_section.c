/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_section.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 11:11:21 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/24 13:46:15 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void		lst_section_free(t_section *head)
{
	t_section *tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
		tmp = NULL;
	}
	head = NULL;
}

t_section	*lst_section_new(void *ptr, int id)
{
	t_section *new;

	if (!(new = (t_section *)malloc(sizeof(t_section))))
		return (NULL);
	new->section = ptr;
	new->id = id;
	new->next = NULL;
	return (new);
}

void		lst_section_append(t_section **head, t_section *new)
{
	t_section *last;

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

