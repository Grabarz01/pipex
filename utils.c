/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:26:39 by fgrabows          #+#    #+#             */
/*   Updated: 2024/09/03 17:52:36 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void ft_error_manager(int x)
{
	if (x == 0)
		perror(NULL);
	if (x == 1)
		ft_putstr_fd("Too few arguments\n", 2);
	if (x == 2)
		ft_putstr_fd("No such environment variable\n", 2);
	if (x == 3)
		ft_putstr_fd("Command not found\n", 2);
	exit (1);
}

char	*ft_get_env(char **env, char *env_var)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		if (ft_strncmp(env[i], env_var,j) == 0)
			return(env[i] + j + 1);
		else 
			i++;	
	}
	return(NULL);
}
char	*ft_path(char *argv, char *my_var, char *path_env)
{
	char	**paths;
	char	*path;
	char	*final_path;
	int		i;
	
	i = 0;
	if(access(argv , F_OK | X_OK) == 0)
		return(argv);
	paths = ft_split(path_env, ':');
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		final_path = ft_strjoin(path, my_var);
		free(path);
		if(access(final_path , F_OK | X_OK) == 0)
		{
			ft_free_split(paths);
			return(final_path);
		}
		free(final_path);
		i++;
	}
	ft_free_split(paths);
	return(NULL);
}
void ft_execve(char **env, char *argv)
{
	char		*path;
	char		**whole_comand;
	static char	*path_env;
	
	if (!path_env)
		path_env = ft_get_env(env, "PATH");
	if (!path_env)
		ft_error_manager(3);
	whole_comand = ft_split(argv, ' ');
	path = ft_path(argv,whole_comand[0], path_env);
	if(!path)
	{
		ft_free_split(whole_comand);
		ft_error_manager(3);
	}
	if(execve(path,whole_comand,env) != 0)
	{
		ft_free_split(whole_comand);
		free(path);
		ft_error_manager(0);
	}
}