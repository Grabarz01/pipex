/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:24:34 by fgrabows          #+#    #+#             */
/*   Updated: 2024/09/03 17:57:01 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void ft_get_input(void)
{
	/*char *ret;
	
	while(1)
	{
		//ret = get_next_line(0);
		if(!ret)
		{
			ft_putstr_fd("Error occures while providing input\n",2);
			exit(1);
		}
		if(strncmp);
		
	}*/
}
// check edge cases for here_doc
// limiter is "" or " "
// empty input for grep or ls -la
void ft_here_doc(int argc, char *argv[], char *env[])
{
	int file_out;
	int n;
	int pfd[2];

	file_out = ft_open_write(argv[argc - 1], 2);
	ft_args_checker(argc, argv, -1, file_out);
	if(pipe(pfd) == -1)
		ft_error_manager(0);
	ft_get_input();
	n = 1;
	while(++n < argc - 2)
	{
		ft_pipe(argv[n],env);
	}
	dup2(pfd[1],1);
}