/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:16:19 by tmaraval          #+#    #+#             */
/*   Updated: 2019/11/04 13:42:21 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int protect(t_infile *file, void *ptr)
{
	if (ptr > (void *)file->save + file->sz)
	{
		return (-1);
	}
	else
		return (0);
}
