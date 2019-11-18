/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:19:30 by tmaraval          #+#    #+#             */
/*   Updated: 2019/11/14 14:38:16 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	putstr_member_name(char *str, size_t len)
{
	size_t i;

	i = 0;
	while (str[i] && ft_isprint(str[i]) && i < len)
	{
		if (str[i] != '\n' && str[i] != ' ')
			write(1, &str[i], 1);
		i++;
	}
}

int		get_str_offset_archive(t_infile *file, struct ar_hdr *ar_header)
{
	int	ret;

	ret = 0;
	if (file)
		;
	if (protect(file, ar_header->ar_name + ft_strlen(AR_EFMT1)) < 0)
		return (0);
	if (!ft_strncmp(ar_header->ar_name, AR_EFMT1, ft_strlen(AR_EFMT1)))
	{
		ret = ft_atoi((char *)ar_header->ar_name + ft_strlen(AR_EFMT1));
	}
	return (ret);
}

int		print_archive_member(t_infile *file, struct ar_hdr *ar_header)
{
	char	*name;
	int		ret;

	ret = 0;
	name = NULL;
	if (protect(file, ar_header->ar_name + ft_strlen(AR_EFMT1)) < 0)
		return (0);
	if (!ft_strncmp(ar_header->ar_name, AR_EFMT1, ft_strlen(AR_EFMT1)))
	{
		name = (char *)ar_header + sizeof(struct ar_hdr);
		ret = ft_atoi((char *)ar_header->ar_name + ft_strlen(AR_EFMT1));
		ft_printf("\n%s(%s):\n", file->filename, name);
	}
	else
	{
		ft_printf("\n%s(", file->filename);
		putstr_member_name(ar_header->ar_name, 16);
		ft_putstr("):\n");
	}
	return (ret);
}
