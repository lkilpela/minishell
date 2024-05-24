/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:02:42 by lkilpela          #+#    #+#             */
/*   Updated: 2024/04/10 10:26:47 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	is_directory(char *cmd)
{
	int	fd;

	if (access(cmd, F_OK) != 0)
		error_args(ERR_FILE, cmd);
	fd = open(cmd, O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		return (1);
	}
	return (0);
}

static int	validate_command(t_pipex *p, t_command *c, char *cmd)
{
	t_tokenize	t;

	init_tokenize(&t);
	c->args = split_command(&t, cmd);
	if (c->args == NULL || c->args[0] == NULL)
		return (0);
	c->path = find_command(p, c->args[0]);
	if (!c->path)
	{
		print_error(ERR_CMD, c->args[0]);
		return (0);
	}
	if (is_directory(c->path))
	{
		print_error(ERR_DIR, c->args[0]);
		return (0);
	}
	if (c->path && access(c->path, X_OK) != 0)
	{
		if (access(c->path, F_OK) != 0)
			error_args(ERR_PERM, c->args[0]);
		else
			error_args(ERR_CMD, c->args[0]);
	}
	return (1);
}

static void	validate_permission(t_pipex *p)
{
	p->infilefd = open(p->argv[1], O_RDONLY);
	if (p->infilefd == -1)
		error_args(ERR_PERM, p->argv[1]);
	p->outfilefd = open(p->argv[p->argc - 1],
			O_CREAT | O_WRONLY | O_TRUNC, PERMISSIONS);
	if (p->outfilefd == -1)
		error_args(ERR_PERM, p->argv[p->argc - 1]);
}

void	validate_arguments(t_pipex *p)
{
	int	cmd1_valid;
	int	cmd2_valid;

	if (p->argc != 5)
		error(ERR_SYNTAX);
	if (ft_strlen(p->argv[1]) == 0 || ft_strlen(p->argv[4]) == 0)
		error(ERR_FILE);
	if (access(p->argv[1], F_OK) != 0)
		error_args(ERR_FILE, p->argv[1]);
	validate_permission(p);
	cmd1_valid = validate_command(p, &p->cmds[0], p->argv[2]);
	cmd2_valid = validate_command(p, &p->cmds[1], p->argv[3]);
	if (!cmd1_valid || !cmd2_valid)
		exit(EXIT_FAILURE);
}
