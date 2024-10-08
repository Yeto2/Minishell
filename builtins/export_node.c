/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:33:55 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/18 09:18:09 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup_(const char *s1)
{
	char	*array;
	int		x;
	int		size;

	x = 0;
	if (!s1)
		return (0);
	size = ft_strlen(s1);
	array = (char *) g_malloc_env((sizeof(char) * (size + 1)), MALLOC);
	if (!(array))
		return (0);
	while (s1[x])
	{
		array[x] = s1[x];
		x++;
	}
	array[x] = '\0';
	return (array);
}

t_exp	*create_node(char *key, char *value)
{
	t_exp	*new_node;

	new_node = g_malloc_env(sizeof(t_exp), MALLOC);
	if (!new_node)
		return (NULL);
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

void	insert_end(t_exp **head, char *key, char *value)
{
	t_exp	*new_node;
	t_exp	*temp;

	new_node = create_node(ft_strdup_(key), ft_strdup_(value));
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
}
