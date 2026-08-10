/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nisim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 12:37:53 by nisim             #+#    #+#             */
/*   Updated: 2026/08/09 13:26:37 by nisim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_gnl(int fd, char **st_list)
{
	char		*buf;
	ssize_t		total_rbyte;
	char		*line;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	total_rbyte = 1;
	while (!ft_findnl(*st_list) && total_rbyte > 0)
	{
		total_rbyte = read(fd, buf, BUFFER_SIZE);
		if (total_rbyte > 0)
		{
			buf[total_rbyte] = '\0';
			*st_list = ft_strjoin_free(*st_list, buf);
		}
	}
	free(buf);
	if (total_rbyte < 0 || !*st_list || **st_list == '\0')
		return (free(*st_list), *st_list = NULL, NULL);
	line = ft_fetch_line(*st_list);
	return (*st_list = ft_strmove(*st_list), line);
}

t_list	*ft_create_node(int fd)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->fd = fd;
	node->content = NULL;
	node->next = NULL;
	return (node);
}

t_list	*ft_get_node(t_list **head, int fd)
{
	t_list	*current;

	if (!*head)
	{
		*head = ft_create_node(fd);
		return (*head);
	}
	current = *head;
	while (current)
	{
		if (current->fd == fd)
			return (current);
		if (!current->next)
			break ;
		current = current->next;
	}
	current->next = ft_create_node(fd);
	return (current->next);
}

t_list	*ft_free_node(t_list *head, t_list *current)
{
	t_list	*temp;
	t_list	*next;

	if (!head || !current)
		return (head);
	next = current->next;
	if (head == current)
		head = next;
	else
	{
		temp = head;
		while (temp->next && temp->next != current)
			temp = temp->next;
		if (temp->next == current)
			temp->next = next;
	}
	free(current);
	return (head);
}

char	*get_next_line(int fd)
{
	static t_list	*head;
	t_list			*current;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	current = ft_get_node(&head, fd);
	if (!current)
		return (NULL);
	line = ft_gnl(fd, &(current->content));
	if (!(current->content))
		head = ft_free_node(head, current);
	return (line);
}
