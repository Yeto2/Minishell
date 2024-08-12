/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:39:25 by yessemna          #+#    #+#             */
/*   Updated: 2024/08/12 22:04:23 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	find_node(t_env *envi, t_token *list)
{
	t_token	*tmp;
	int		found;

	tmp = list;
	found = 0;
	if (tmp && tmp->value != HEREDOC)
	{
		while (tmp)
		{
			found = 0;
			if (tmp->value == VAR || tmp->value == DBL_Q)
				handle_expand(envi, &tmp, found);
			tmp = tmp->next;
		}
	}
}

char	*join_char(char *str, char c)
{
	char	*out;
	int		i;
	int		len;

	i = 0;
	if (!str)
		str = ft_strdup("");
	len = ft_strlen(str);
	out = g_malloc(len + 2, MALLOC);
	while (str[i] != '\0')
	{
		out[i] = str[i];
		i++;
	}
	out[i] = c;
	out[i + 1] = '\0';
	return (out);
}
