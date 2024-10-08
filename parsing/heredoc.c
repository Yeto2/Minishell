/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 04:12:59 by yessemna          #+#    #+#             */
/*   Updated: 2024/09/24 00:55:52 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	putin_fd(int fd, char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		write(fd, &line[i], 1);
		i++;
	}
}

void	search_in_env(char **ret, char **exp, t_env **envi)
{
	t_env	*tmp_env;
	int		found;

	tmp_env = *envi;
	found = 0;
	while (tmp_env)
	{
		if (ft_strcmp(*exp, tmp_env->key) == 0)
		{
			*ret = ft_srtjoin(*ret, ft_strdup(tmp_env->value));
			found = 1;
			break ;
		}
		tmp_env = tmp_env->next;
	}
	if (!found)
		*ret = "";
}

char	*heredoc_expand(char *line, t_env *envi)
{
	int		i;
	char	*ret;
	char	*exp;

	((1) && (ret = NULL, exp = NULL, i = 0));
	while (line[i])
	{
		while (line[i] == '\'' || line[i] == '\"')
			((1) && (ret = join_char(ret, line[i]), i++));
		if (line[i] == '$')
		{
			i++;
			while (line[i] && is_alnum(line[i]))
				((1) && (exp = join_char(exp, line[i]), i++));
			search_in_env(&ret, &exp, &envi);
		}
		else
			((1) && (ret = join_char(ret, line[i]), i++));
	}
	return (ret);
}

void	hd_heper(char **line, t_token **tmp, char **buff, t_env **envi)
{
	char	*tompo;

	while (1)
	{
		if (!ttyname(0))
			break ;
		*line = readline("> ");
		if (!*(line))
			break ;
		tompo = *line;
		*line = ft_strdup(*line);
		free(tompo);
		if (!ft_strcmp_her((*line), (*tmp)->key)
			&& ((*tmp)->value == DBL_Q || (*tmp)->value == SNGL_Q))
			break ;
		else if (!ft_strcmp_her((*line), (*tmp)->key))
			break ;
		if (!((*tmp)->value == DBL_Q || (*tmp)->value == SNGL_Q))
			(*line) = heredoc_expand((*line), *envi);
		*buff = ft_srtjoin(*buff, *line);
		*buff = join_char(*buff, '\n');
	}
}

void	ft_here_doc(t_token *cmd, t_env *envi, int *red_in, t_fd_col *collector)
{
	t_token	*tmp;
	char	*line;
	char	*buff;
	int		fd_write;

	buff = NULL;
	((1) && (tmp = cmd, line = NULL));
	hd_heper(&line, &tmp, &buff, &envi);
	fd_write = ft_open(collector, "/tmp/dog", O_WRONLY
			| O_CREAT | O_TRUNC, 0644);
	if (fd_write != -1)
		*red_in = fd_write;
	putin_fd(fd_write, buff);
	close(fd_write);
	if (ttyname(0))
		ft_exit_status(0, SET);
}
