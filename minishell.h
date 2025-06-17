/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:30:28 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/17 11:05:44 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <errno.h>

# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h"

# include <readline/readline.h>
# include <readline/history.h>

# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define RESET "\033[0m"
# define BOLD "\033[1m"

# define HISTORY_FILE ".history_file"

typedef enum e_token_type
{
	WORD,
	PIPE,
	RD_OUT,
	RD_IN,
	APPND,
	HERDC
}	t_token_type;

typedef struct s_segment {
	char				*text;
	bool				in_single;
	bool				in_double;
	struct s_segment	*next;
}	t_segment;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef enum e_redirect_type
{
	RED_IN,
	RED_OUT,
	RED_APPEND,
	RED_HEREDOC
}	t_redirect_type;

typedef struct s_redirect
{
	t_redirect_type		type;
	char				*file;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_cmd
{
	char			**args;
	t_redirect		*redirect;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_get_cmds_vars
{
	t_token		*cur;
	t_cmd		*cmd_head;
	t_cmd		*current;
	char		**args;
	int			args_count;
	t_redirect	*redirects;
	t_cmd		*new_cmd;
}	t_get_cmds_vars;

typedef struct s_data
{
	int		start;
	int		i;
	int		tst;
	int		exitstatus;
	char	*input;
	char	*cwd;
	t_cmd	*cmdlst;
	t_token	*lsttoken;
	t_env	*env;
	t_cmd	*cmd;
	pid_t	pid;
	pid_t	*pids;
	int		cmd_index;
	int		prev_fd;
	int		var_start;
	int		var_end;
}	t_data;

typedef struct s_exp_segm
{
	t_segment	*seg;
	t_data		*dt;
	char		**result;
	int			*j;
	int			start;
}	t_exp_segm;

void	ft_signals(void);
void	ctld_handler(t_data *dt);
void	ctlc_handler(int sig);
void	ft_change_global(int flag);

void	ft_add_history(t_data *dt);
int		check_pre_lexing_errors(t_data *dt);
t_cmd	*ft_lexer(t_token **tokenslst, t_data *dt);
int		ft_add_token(t_token **tokens, t_token_type type, char *value);
void	ft_free_tokens(t_token *head);
int		ft_init_data(t_data *dt, int arc, char **env);
int		ft_save_env(t_data *dt, char **env);
void	ft_add_env(t_env **env, char *key, char *value);
void	ft_free_env(t_env *head);
t_cmd	*ft_get_commands(t_data **dt);
int		exec_command(t_cmd *cmd, t_data *dt);
int		ft_handle_redirct(t_redirect *redir);
char	*ft_expand_vars(t_data *dt, char *key);
int		is_valide_arg(char *str, int check);
char	**ft_create_tmp_env(t_env *env);
char	*remove_quotes(const char *str);

int		ft_check_varible_add_token(t_token **tokenslst, char *str, t_data *dt);

int		expand_segment(t_segment *seg, t_data *dt, char **result);
void	ft_free_segments(t_segment *seg);

void	ft_free_double(char **arr);

void	ft_builtin_exit(t_data *dt);
int		ft_builtin_cd(t_cmd *cmd, t_data *dt);
int		ft_builtin_echo(t_cmd *cmd);
int		ft_builtin_env(t_data *dt);
int		ft_builtin_export(t_cmd *cmd, t_data *dt);
int		ft_builtin_unset(char **args, t_data *dt);
void	is_need_del(t_data *dt, char *arg);
int		ft_print_history(t_cmd *cmd, char *file);
int		ft_builtin_pwd(t_cmd *cmd);

int		ft_handle_lexer_pipe(t_token **tokenslst);
int		ft_hndl_lxr_in(t_token **tokenslst, t_data *dt, int *start, int *end);
int		ft_hndl_lxr_out(t_token **tokenslst, t_data *dt, int *start, int *end);
int		ft_split_input(t_token **tokenslst, t_data *dt, int *start, int *end);
void	ft_split_input2(t_data *dt, int *end);

int		ft_add_argument(char ***args, int *count, char *value);
int		ft_add_redirecs(t_token **cur, t_redirect **redirects);
t_cmd	*create_cmd_node(char **args, t_redirect *redirects);

int		ft_prepare_heredocs(t_cmd *cmd, t_data *dt);
char	*expand_heredoc_preserve_quotes(char *line, t_data *dt);

int		ft_split_input_into_segments(char *input, t_segment **segments);
int		handle_named_var(t_exp_segm *info);
int		handle_invalid_var(char **result, t_segment *seg, char *text, int *j);
int		handle_digit_var(t_data *dt, char **result, char digit);
int		handle_exit_status(t_data *dt, char **result);
char	*ft_strjoin_char(char *s, char c);

int		ft_is_special_char(char c);
int		is_special_char(char c);
int		ft_if_should_skip(char c);
char	*remove_quotes(const char *str);
void	print_banner(void);

int		is_builtin_no_pipe(t_cmd *cur_cmd, int has_pipe);
int		is_builtin_no_pipe(t_cmd *cur_cmd, int has_pipe);

void	cleanup_fork_error(int *pipe_fd, int *prev_fd,
			int has_pipe, t_data *dt);

void	handle_parent_process(int *pipe_fd, int *prev_fd,
			int has_pipe);

void	handle_child_process(t_cmd *cur_cmd, t_data *dt,
			int prev_fd, int *pipe_fd);

void	exec_external_cmd(t_cmd *cur_cmd, t_data *dt,
			int *pipe_fd, int has_pipe);

void	exec_builtin_child(t_cmd *cur_cmd, t_data *dt);

void	setup_child_pipes(int prev_fd, int *pipe_fd,
			int has_pipe, t_redirect *redirect);

int		exec_builtin_parent(t_cmd *cur_cmd, t_data *dt, pid_t *pids);
int		save_stdio(int *saved_stdout, int *saved_stdin);
int		count_cmds(t_cmd *cmd);
int		redirects_to_stdout(t_redirect *redir);
int		ft_execute_builtin(t_cmd *cmd, t_data *dt);
int		ft_is_builtin(char **arg);
void	ft_cleanup_heredocs(t_cmd *cmd);
int		setup_pipe(int *pipe_fd, int *prev_fd, int i, pid_t *pids);
int		fork_and_exec(t_cmd *cur_cmd, t_data *dt, int *pipe_fd, int *prev_fd);
char	*ft_get_path(char *cmd, t_data *dt);

int		ft_split_input_into_segments(char *input, t_segment **segments);

char	**extract_key_utils(char *key);

void	ft_free_redirect(t_redirect *redir);
void	ft_free_cmd(t_cmd *cmd);

#endif
