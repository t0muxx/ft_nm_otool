/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 09:48:56 by tmaraval          #+#    #+#             */
/*   Updated: 2019/11/05 10:10:44 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		error_gen(char *str)
{
	ft_putstr_fd("ft_nm : ", 2);
	ft_putendl_fd(str, 2);
	return (-1);
}

size_t	protected_strlen(char *str, t_infile *file)
{
	size_t i;

	i = 0;
	while (((void *)str + i < (void *)file->save + file->sz) && str[i])
		i++;
	return (i);
}

void	protected_munmap(t_infile *file)
{
	if (file->can_munmap)
	{
		munmap(file->save, file->sz);
	}
}
