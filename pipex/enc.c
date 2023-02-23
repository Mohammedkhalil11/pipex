/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:58:43 by mokhalil          #+#    #+#             */
/*   Updated: 2023/02/18 00:09:33 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include "pipex.h"

char	**split_path(char **env)
{
        char **split;
		int	i;
		int j;
		
		i = 0;
		while (env[i] && ft_strncmp(env[i],"PATH",4))
				i++;
		split = ft_split(&env[i][5],':');
	return split;
}
char	*check_path(char **split, char* cmd)
{
	int	i;
	char	*p;
	char	*k;
	char **arg = ft_split(cmd,' ');
	i = 1;
	if (access(arg[0],X_OK) == 0)
	{
		return (arg[0]);
	}
	p = ft_strjoin("/",arg[0]);
	arg = free_things(arg);
	while(split[i])
	{
		k = ft_strjoin(split[i],p);
		if (access(k,X_OK) == 0)
		{
			free(p);
			return (k);	
		}
		free(k);
		i++;
	}
	free(p);
	free(k);
	return (NULL);
}

char	**append_arg(char	*path, char	*arg)
{
	char	**s;
	s = ft_split(arg, ' ');
	s[0] = ft_strdup(path);
	return (s);
}
//execve("/usr/bin/ls", {"/usr/bin/ls","-l",null}, null);
// int main(int ac, char **av, char** env)
// {
//     if (ac != 0)
//     {
// 		int i;
// 		i = 0;
//         char **split = split_path(env);
// 		char	*l = check_path(split,av[1]);
// 	// 	char **k = append_arg(l, av[1]);
// 	// 	printf("%s\n", l);
// 	// 	while (k[i])
// 	// 	{
// 	// 		printf("%s\n", k[i]);
// 	// 		i++;
// 	// 	}
//     // }
// 	}
// 	system("leaks a.out");
//     return 0;
// }
