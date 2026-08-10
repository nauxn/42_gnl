/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nisim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 12:48:26 by nisim             #+#    #+#             */
/*   Updated: 2026/08/09 13:26:09 by nisim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	int				fd;
	char			*content;
	struct s_list	*next;
}					t_list;

char	*get_next_line(int fd);
char	*ft_gnl(int fd, char **st_list);
t_list	*ft_create_node(int fd);
t_list	*ft_get_node(t_list **head, int fd);
t_list	*ft_free_node(t_list *head, t_list *current);
int		ft_strlen(char *str);
int		ft_findnl(char *s1);
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_fetch_line(char *s1);
char	*ft_strmove(char *s1);

#endif
