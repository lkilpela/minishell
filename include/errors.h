/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 22:50:18 by aklein            #+#    #+#             */
/*   Updated: 2024/06/02 22:50:19 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define ERR_ALLOC "Allocation error."
# define ERR_MS "minishell"
# define ERR_QUOTES "syntax error, quotes not matched"
# define ERR_PIPES "syntax error, pipe all alone in the end"
# define ERR_NEAR_TOKEN "syntax error near unexpected token `"
# define ERR_KEY_VALID "not a valid identifier"
# define ERR_AMBIGUOUS "ambiguous redirect"
# define ERR_CD_ARGS "too many arguments"
# define ERR_CD_HOME "HOME variable not set"
# define NL	"newline"
# define ERR_PIPE "pipe failed"
# define ERR_DUP2 "dup2 failed"
# define ERR_FORK "fork failed"
# define ERR_EXECVE "execve failed"
# define ERR_WAITPID "waitpid failed"
# define ERR_FILE "no such file or directory"
# define ERR_CMD "command not found"
# define ERR_DIR "is a directory"
# define ERR_PERM "permission denied"

# define E_CODE_EXEC 126
# define E_CODE_CMD 127
# define E_CODE_SIG 128
# define E_CODE_SYN 2
# define E_CODE_ERRNO 160
#endif