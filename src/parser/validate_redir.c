/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 22:35:42 by aklein            #+#    #+#             */
/*   Updated: 2024/06/17 00:26:40 by aklein           ###   ########.fr       */
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

	if (*file == '/')
		return (ft_safe_strdup(*file));
	if (*file)
	{
		str = ft_safe_strjoin("./", file);
		return (str);
	}
	return (ft_safe_strdup(""));
}

int	get_oflags(t_redir *file)
{
	if (file->append)
		return ((O_CREAT | O_WRONLY | O_APPEND));
	if (file->type == OUTFILE)
		return ((O_CREAT | O_WRONLY | O_TRUNC));
	if (file->type == INFILE)
		return (O_RDONLY);
	return (1);
}

static int	validate_redir(t_redir *file)
{
	char	*path;

	if (file->type == HEREDOC)
		return (1);
	if (file->file)
	{
		if (is_ambiguous(file->file, file->key))
			return (0);
		path = fix_path(file->file);
		file->fd = safe_open(path, get_oflags(file), 0644);
		if (file->fd == -1)
		{
			if (errno == EACCES)
				print_error(ERR_MS, file->file, NULL, 1);
			else if (is_dir(path))
				print_error(ERR_MS, file->file, ERR_DIR, 0);
			else
				print_error(ERR_MS, file->file, ERR_FILE, 0);
			return (0);
		}
		ft_free((void **)&path);
	}
	else
		file->fd = -1;
	return (1);
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
