/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_readers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:18:18 by fgrabows          #+#    #+#             */
/*   Updated: 2024/09/03 17:51:36 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_read_file(int file_in, int pfd_w)
{
	char	buf[1000];
	int		r_bit;
	
	while(1)
	{
		r_bit = read(file_in, buf, sizeof(buf));
		if (r_bit == -1)
			ft_error_manager(0);
		if (r_bit == 0)
			break;
		if(write(pfd_w, buf, r_bit) == -1)
			ft_error_manager(0);
	}
}

int ft_file_in_manager(int file_in)
{
	int pfd[2];
	
	
	if(pipe(pfd) == -1)
		ft_error_manager(0);
	if (file_in < 0)
	{
		write(pfd[1],"\0",1);
		close(pfd[1]);
	}
	else
	{
		ft_read_file(file_in, pfd[1]);
		close(file_in);
		close(pfd[1]);
	}
	return(pfd[0]);
}

int ft_open_read (char *argv)
{
	int fd;

	if (access(argv, F_OK) == -1)
	{
		ft_putstr_fd(argv,2);
		perror(" ");
		return (-2);
	}
	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd(argv,2);
		perror(" ");
		return(-1);
	}
	return (fd);
}
//1 - pipex
//2 - bonus
int ft_open_write(char *argv, int x)
{
	int fd;
	
	if(x == 1)
		fd = open(argv, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else if(x == 2)
		fd = open(argv, O_WRONLY | O_APPEND | O_CREAT, 0666);
	if (fd < 0)
	{
		ft_putstr_fd(argv,2);
		perror(" ");
		exit(EXIT_FAILURE);
	}
	return(fd);
	
}