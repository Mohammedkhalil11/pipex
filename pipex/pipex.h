/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 23:54:05 by mokhalil          #+#    #+#             */
/*   Updated: 2023/02/16 23:35:05 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PIPEX_H
# define PIPEX_H

#include<stdio.h>
#include<stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *str);
void	ft_bzero(void *s, size_t n);
char	**split_path(char **env);
char	*check_path(char **split, char* cmd);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	**append_arg(char	*path, char	*arg);
char	*ft_strdup(const char *s1);
char	**free_things(char **strings);
#endif