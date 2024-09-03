/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:46:46 by fgrabows          #+#    #+#             */
/*   Updated: 2024/09/03 17:49:32 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

void ft_pipe (char *arg, char **env)
{
	int fd[2];
	int pid;

	if(pipe(fd) == -1)
		ft_error_manager(0);
	pid = fork();
	if(pid == -1)
		ft_error_manager(0);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		ft_execve(env, arg);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		wait(NULL);
	}
}

void ft_pipex(int argc, char *argv[], char *env[])
{
	int n;
	int file_in;
	int file_out;
	
	file_out = ft_open_write(argv[argc - 1], 1);
	file_in = ft_open_read(argv[1]);
	n = 1;
	if(file_in == -1)
	{
		close(file_out);
		exit(0);
	}
	ft_args_checker(argc, argv, file_in, file_out);
	file_in = ft_file_in_manager(file_in);
	dup2(file_in, STDIN_FILENO);
	while (++n < argc - 2)
	{
		ft_pipe(argv[n], env);
		if(n == 2 && file_in > 0)
			close(file_in);
	}
	dup2(file_out,STDOUT_FILENO);
	ft_execve(env,argv[n]);
}

int main(int argc, char *argv[], char *env[])
{
	if (argc < 5)
		ft_error_manager(1);
	if(ft_empty_arg(argv[1]) != 0 && ft_strncmp(argv[1], "here_doc", 8) == 0 && ft_strlen(argv[1]) == 8)
	{
		if(argc < 6)
			ft_error_manager(1);
		ft_here_doc(argc, argv, env);
	}
	else
		ft_pipex(argc, argv, env);		
}

/*
pipe - for write only; truncate; if doesnt exist create new one
hear_doc - for wirte only; append; if doesnt exist create new one
---------------------------------------------------------------------------
X no existance of infile - works like normal but fd of infile doesn't exist; "inile : No such file or directory"; exit(0)
X no existance of outfile - create new one and output there; exit(0); no message
X no existance of infile and outfile - just like as there was no infile 
X no permisions to infile - truncate outfile, "infile : Permission denied"  exit(0); no output
X no permisions to outfile - nothing happens in outfile, "outfile : Permission denied" exit(1);
X no permissions to both files - both messages from two previous cases; exit(1) ; nothing has changed in outfiles
X empty infile - exit(0) , works normally
X empty infile and no permision to outfile - exit(1)
 one of the comands is empty - exit 127, turncates file
 one of the comands is wrong - exit 127, turncates file 
 big message
 urandom
X comand is also with the path
*/