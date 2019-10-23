/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 16:03:22 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/23 15:53:05 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void		*process_infile_error(int fd, t_infile *infile,
		char *path, char *msg)
{
	if (infile)
		free(infile);
	if (fd)
		close(fd);
	ft_putstr_fd("ft_nm : ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(" ", 2);
	ft_putendl_fd(path, 2);
	return (NULL);
}

int			process_infile_mmap(t_infile **infile, struct stat buf, int fd)
{
	if (((*infile)->mem = mmap(NULL, buf.st_size, PROT_READ,
					MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (-1);
	(*infile)->sz = 0;
	(*infile)->type = 0;
	(*infile)->mac_header = NULL;
	(*infile)->segment_command = NULL;
	(*infile)->symtab_command = NULL;
	return (0);
}

t_infile	*process_infile(char *path)
{
	int			fd;
	struct stat buf;
	t_infile	*infile;

	if ((fd = open(path, O_RDONLY)) < 0)
		return (process_infile_error(fd, NULL, path, "can't open"));
	if (fstat(fd, &buf) < 0)
		return (process_infile_error(fd, NULL, path, "can't stat"));
	if (!(infile = (t_infile *)malloc(sizeof(t_infile))))
		return (process_infile_error(fd, NULL, path, "can't malloc"));
	if (process_infile_mmap(&infile, buf, fd) < 0)
		return (process_infile_error(fd, NULL, path, "can't mmap"));
	close(fd);
	infile->sz = buf.st_size;
	return (infile);
}
