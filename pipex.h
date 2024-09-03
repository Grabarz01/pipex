#ifndef PIPEX_H
#define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <wait.h>


void	ft_free_split(char **args);
void 	ft_pipe (char *arg, char **env);
void 	ft_pipex(int argc, char *argv[], char *env[]);
int 	main(int argc, char *argv[], char *env[]);
void 	ft_error_manager(int x);
char	*ft_get_env(char **env, char *env_var);
char	*ft_path(char *argv, char *my_var, char *path_env);
void 	ft_execve(char **env, char *argv);
int 	ft_empty_arg(char *argv);
void 	ft_args_checker(int argc, char **argv, int file_in, int file_out);
void	ft_read_file(int file_in, int pfd_w);
int		ft_file_in_manager(int file_in);
int		ft_open_read (char *argv);
int		ft_open_write(char *argv, int x);
void	ft_here_doc(int argc, char *argv[], char *env[]);
void	ft_get_input(void);


#endif