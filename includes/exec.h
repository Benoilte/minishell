/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:35:50 by tmartin2          #+#    #+#             */
/*   Updated: 2024/07/09 21:03:36 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

// exec/exec.c

void	set_exit_code(t_bash *bash);

// exec/sort_red.c

int		sort_red(t_instruction *instruction, t_bash *bash);
int		setup_pipe(t_instruction *current);
int		inst_have_input_red(t_token *current_red);
int		inst_have_output_red(t_token *current_red);

// exec/ft_cmd.c

void	ft_cmd(char *sender, t_token *cmd, char **argv, t_bash *bash);
char	*get_path(char *cmd, t_bash *bash);
int		is_path_reachable(char *path, char *sender, t_token *cmd, t_bash *bash);

// exec/process.c

int		handle_process(t_instruction *current, t_bash *bash, char **envp);
void	child_process(t_instruction *instruction, t_bash *bash, char **envp);
int		parent_process(t_instruction *instruction);
int		wait_child_process(t_instruction *instruction);

// exec/red.c

int		red(t_token *current_red);
int		open_file(char *red, t_token *token);
int		dup_and_close(int fd, int fd2);

// exec/red_here_doc.c

int		setup_here_doc(t_instruction *inst, t_token *current_red, t_bash *bash);
int		display_here_doc(char *limiter, t_instruction *inst, t_bash *bash);
char	*here_doc_readline(char *limiter, t_bash *bash);

// exec/red_here_doc_utils.c

int		handle_here_doc_process(pid_t reader, t_instruction *inst,
			t_token *current_red, t_bash *bash);
void	child_here_doc_process(t_instruction *inst, t_token *current_red,
			t_bash *bash);
int		parent_here_doc_process(pid_t reader, t_instruction *inst,
			t_token *current_red);


// exec/sort_cmd_builtin

void	sort_cmd_builtin(t_instruction *instruction, t_bash *bash, char **envp);

// exec/utils_exec.c

int		ft_get_next_line(char **line);
int		ft_strcmp(char *s1, char *s2);
int		is_digit_only(char *str);

// exec/handle_execution_error.c

void	print_red_error(char *sender, t_token *red);
void	print_cmd_error(char *sender, t_token *cmd);
void	print_error_and_exit(char *sender, t_token *cmd,
			int status, t_bash *bash);

// exec/exec_commands.c

void	exec_commands(t_bash *bash, t_instruction *instr, char **envp);

// exec/file_desriptors_utils.c

void	reset_fd_stdin_and_stdout(t_instruction *inst);
void	reset_fd_stdout(t_instruction *inst);
void	reset_fd_stdin(t_instruction *inst);
int		close_and_reset_fd(t_instruction *curent_inst, int *fd);
void	close_unused_fd(t_instruction *current_inst, t_bash *bash);

#endif
