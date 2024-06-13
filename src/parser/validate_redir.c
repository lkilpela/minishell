/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 22:35:42 by aklein            #+#    #+#             */
/*   Updated: 2024/06/13 23:39:56 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	new_redir(t_cmd *cmd, t_redir *new)
{
	if (new->type == INFILE || new->type == HEREDOC)
	{
		safe_close(cmd->in_file.fd);
		cmd->in_file = *new;
	}
	else
	{
		safe_close(cmd->out_file.fd);
		cmd->out_file = *new;
	}
}

static char	*fix_path(char *file)
{
	char	*str;

	if (*file != '/')
	{
		str = ft_safe_strjoin("./", file);
		return (str);
	}
	return (file);
}

static int	validate_redir(t_redir *file)
{
	int		oflags;
	char	*path;

	if (file->type == HEREDOC)
		return (1);
	if (file->type == INFILE)
		oflags = O_RDONLY;
	if (file->type == OUTFILE)
		oflags = (O_CREAT | O_WRONLY | O_TRUNC);
	if (file->append)
		oflags = (O_CREAT | O_WRONLY | O_APPEND);
	if (file->file)
	{
		path = fix_path(file->file);
		file->fd = open(path, oflags, 0644);
		ft_free((void **)&path);
		if (file->fd == -1)
		{
			print_error(ERR_MS, file->file, NULL, 1);
			return (0);
		}
	}
	else
		file->fd = -1;
	return (1);
}

void	close_fds(void)
{
	int	fd;

	fd = 3;
	while (fd <= 256)
	{
		safe_close(fd);
		fd++;
	}
}

int	validate_redir_list(t_cmd *cmd)
{
	t_redir	*redir;
	t_list	*redirs;

	redirs = cmd->redirs;
	while (redirs)
	{
		redir = (t_redir *)redirs->content;
		if (!validate_redir(redir))
			return (0);
		new_redir(cmd, redir);
		redirs = redirs->next;
	}
	return (1);
}
