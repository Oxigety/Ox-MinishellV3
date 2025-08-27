/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babou <babou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:44:54 by bchapuis          #+#    #+#             */
/*   Updated: 2024/06/10 11:16:35 by babou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdbool.h>
# include <curses.h>
# include <errno.h>
# include "libft.h"
# include <limits.h>
# define MAX_NB_PIPES 490

/* -------------------------------------------------------------------------- */
/*									STRUCTURES								  */
/* -------------------------------------------------------------------------- */

typedef enum s_exitflag
{
	NODE,
	STR,
	NONE,
	END,
}			t_exitflag;

struct s_env_list
{
	struct s_env_list	*next;
	char				*var_name;
	char				*value;
};
typedef struct s_env_list	t_env_list;

struct s_nb
{
	int	i;
	int	j;
};
typedef struct s_nb			t_nb;

struct s_heredoc
{
	char				*delim;
	char				*filename;
	int					pipe_pos;
	struct s_heredoc	*next;
};
typedef struct s_heredoc	t_heredoc;

typedef struct s_command
{
	char				**v_cmd;
	char				*cmd;
	char				*input_redirection;
	char				*output_redirection;
	int					heredoc_fd;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

typedef struct s_shell
{
	int				exit;
	int				exitcode;
	char			**env;
	char			**split_path;
	char			*str;
	char			*input;
	bool			heredoc_quoted;
	int				heredoc_counter;
	char			*heredoc_name;
	char			*heredoc_fork_cnt;
	char			*heredoc_delim;
	int				cmd_lvl;
	int				*pipe_fds;
	int				nb_pipes;
	int				saved_index;
	char			*path;
	t_command		*cmd_list;
	t_env_list		*list;
	t_heredoc		*hdoc_list;
	int				stdin;
}	t_shell;

/* -------------------------------------------------------------------------- */
/*									MAIN									  */
/* -------------------------------------------------------------------------- */

void		signal_handler_c(int signum);
void		set_signals(void);
void		save_shell(int *ex_code, int exit_code);
char		*ft_read_input(t_shell *shell);
int			process_message(t_shell *shell);
bool		standardize_command(t_shell *shell, t_command *command);

/* -------------------------------------------------------------------------- */
/*									PROMPT									  */
/* -------------------------------------------------------------------------- */

char		*ft_strjoin_f(char *s1, char *s2, bool to_free);
char		*path_string(t_shell *shell);
bool		quotes_closed(const char *input);
char		*expand_input(t_shell *shell, char *str);
bool		contains_global_var(char *str, int *begin, int *end, int i);
char		*handle_quotes(t_shell *shell, char *input, bool s_is_open,
				bool d_is_open);
int			extract_dollar_size(t_shell *shell, char *str, int begin,
				int end);

/* -------------------------------------------------------------------------- */
/*								  HEREDOC									  */
/* -------------------------------------------------------------------------- */

char		*get_env_value(t_shell *shell, char *var_name, bool *found);
char		*read_heredoc(t_shell *shell, char *delimiter, char *t_free);
int			handle_heredoc(t_shell *shell, char *delimiter, char *t_free);
size_t		ft_get_delimiter(char *str);
char		*search_heredoc(t_shell *shell, char *input, size_t i, char *delim);
char		*expand_variables(t_shell *shell, char *input, char *result);
int			get_del_length(char *str);
void		open_and_write_heredoc(t_shell *shell, char *content, char *delim);
char		*copy_file_into_content(t_shell *shell, char *tf1, char *tf2);
bool		can_i_leave_please(char **line, char *delimiter);
bool		reuse_tmp(t_heredoc *list, char *delim, int lvl);
void		moove_into_next_redir(t_shell *shell, char *t_free, bool reset);
t_shell		*free_shell_addr(t_shell *shell, char *s1, char *s2, bool to_free);
void		moove_into_next_redir(t_shell *shell, char *t_free, bool reset);
void		heredoc_fork(t_shell *shell, char *delimiter, char *t_free);
void		find_delim_quote_char(t_shell *shell, char **str);
void		check_heredoc_existence(t_shell *shell, char *t_free, char *delim,
				char *content);
void		open_and_write_child(t_shell *shell, char *content, char *name,
				char *delim);
char		*expand_single_variable(t_shell *shell, char **start,
				char *dollar, char *result);
char		*is_expand_needed(t_shell *shell, char *line,
				char *t_free, char *content);
void		init_list_heredoc(char *delimiter, t_shell *shell,
				char *t_free, int lvl);
char		*extract_delimiter(t_shell *shell, char *heredoc_pos,
				size_t length);

/* -------------------------------------------------------------------------- */
/*								  INIT ENV									  */
/* -------------------------------------------------------------------------- */

void		init_envp(t_shell *shell, char **envp);
int			del_envlist(t_shell **shell, char *name);
void		add_envlist(t_shell **shell, t_env_list **new_node, char *var,
				bool lone);

/* -------------------------------------------------------------------------- */
/*									PWD										  */
/* -------------------------------------------------------------------------- */

char		*ft_get_cwd(t_shell *shell);
void		ft_pwd(t_shell *shell);

/* -------------------------------------------------------------------------- */
/*									EXIT									  */
/* -------------------------------------------------------------------------- */

void		safe_exit(t_shell *shell, void *param, t_exitflag flag, int err);
bool		str_is_num(char *str);
int			get_exit_code(char *str);
int			ft_is_exit(t_shell *shell, char **v_cmd);
void		exit_ctrl(t_shell *shell, int err);

/* -------------------------------------------------------------------------- */
/*									 CD										  */
/* -------------------------------------------------------------------------- */

void		update_env_var(t_shell *shell, char *var, char *new_value);
void		goto_home_path(t_shell *shell, int *err);
void		goto_root_dir(t_shell *shell, char *cmd, int *err, bool found);
void		ft_cd(t_shell *shell, char **v_cmd);

/* -------------------------------------------------------------------------- */
/*									ECHO									  */
/* -------------------------------------------------------------------------- */

char		*ft_getenv(t_shell *shell, char *target, char *to_free);
void		ft_echo(t_shell *shell, char **v_cmd);

/* -------------------------------------------------------------------------- */
/*									 ENV									  */
/* -------------------------------------------------------------------------- */

void		ft_env(t_shell *shell);
bool		env_is_empty(t_shell *shell, int len);
void		add_envlist(t_shell **shell, t_env_list **new_node, char *var,
				bool lone);

/* -------------------------------------------------------------------------- */
/*									EXPORT									  */
/* -------------------------------------------------------------------------- */

int			var_already_exists(t_shell *shell, int *i, char *new);
char		**rewrite_env(t_shell *shell, char *new_var, int i);
void		print_export(t_shell *shell);
char		*get_var_name(const char *str);
char		*get_var_value(char *str);
void		change_var_value(t_shell *shell, int i, int j, char **v_cmd);
void		ft_export(t_shell *shell, char **v_cmd);

/* -------------------------------------------------------------------------- */
/*								    UNSET									  */
/* -------------------------------------------------------------------------- */

void		ft_unset(t_shell *shell, char **v_cmd);

/* -------------------------------------------------------------------------- */
/*								  FIND EXEC									  */
/* -------------------------------------------------------------------------- */

void		ft_execute(char **cmd, char **envp, t_shell *shell);
char		*join_path_cmd(t_shell *shell, char *path, char *cmd);
char		*get_cmd_path(t_shell *shell, char *cmd, char **path, int i);

/* -------------------------------------------------------------------------- */
/*								PIPE & REDIR								  */
/* -------------------------------------------------------------------------- */

size_t		count_pipes(t_shell *shell, const char *str);
void		exec_redirections(t_shell *shell, t_command *cmd, int i);
char		*next_redirection_name(t_command *cmd, int i);
bool		check_last_redirection(char *str, char c);
int			last_redirection_size(char *cmd, char c, int *start);
bool		is_redirection_valid(const char *str);
void		pipes_commands(t_shell *shell, t_command *command, unsigned int i);
bool		is_command_valid(t_shell *shell, const char *message);
void		print_redir_err(const char *str, int i);
void		in_out_redirection(t_shell *shell, t_command *command,
				int pipe_fd, int i);

/* -------------------------------------------------------------------------- */
/*								BUILD & EXEC								  */
/* -------------------------------------------------------------------------- */

char		*clean_command(char *cmd);
bool		split_command(t_shell *shell, t_command *command);
void		free_cmd_list(t_command *cmd_list);
void		cmd_new(t_command *prev);
int			exec(t_shell *shell, t_command *cmd, int *pipe_fd);
bool		path_is_real(t_shell *shell, char **env, t_command *cmd);
char		*manage_path_type(t_shell *shell, char *cmd);
char		*add_abs_path(t_shell *shell, char *res, char *cmd);
bool		handle_command2(t_shell *shell, t_command *cmd);
bool		handle_command3(t_shell *shell, t_command *cmd);

/* -------------------------------------------------------------------------- */
/*								ERROR HANDLING								  */
/* -------------------------------------------------------------------------- */

void		error(t_shell *shell, int exit_code);
void		exec_errors(t_shell *shell, t_command *cmd);
void		print_errors(t_shell *shell, int exit_code, char *s2, char *s3);
bool		is_command_valid(t_shell *shell, const char *message);
bool		is_empty_pipe(const char *str);
bool		is_ended_by_pipe(const char *str);
bool		is_starting_by_pipe(const char *str);
bool		is_invalid_char_in_quote(const char *str);
void		find_invalid_syntax(const char *str);
int			check_invalid_char(char *s);
void		printferr(char *str);

/* -------------------------------------------------------------------------- */
/*								STR OPERATIONS								  */
/* -------------------------------------------------------------------------- */

int			is_in_quotes(const char *str, int j);
char		*grab_var_value(t_shell *shell, char *to_search);
bool		is_heredoc_delim(char *str, int *i, bool incr);
bool		char_sym(const char s, const char *charset);
bool		is_there_chr(char *str, char c);
int			count_quotes(const char *str);
int			size_redirection(char *cmd, int *i, int res);
char		*str_without_quotes(char *str);
void		copy_quoteless(char *result, char *str);
bool		var_is_valid(char *str);
bool		handle_isspace(char *str);
char		**split_arguments(const char *s, char *set);
void		copy_without_redirections(char *cmd, char *result);
void		copy_without_quotes(char *word, const char *s,
				unsigned int start, unsigned int end);

/* -------------------------------------------------------------------------- */
/*									PRINTF2								 	  */
/* -------------------------------------------------------------------------- */

void		ft_putnbr_err(int nbr, int *size, char BUFFER[BUFFER_SIZE]);
void		ft_special_char_err(char c, va_list argptr, int *size,
				char BUFFER[BUFFER_SIZE]);
void		ft_putncount_char_err(char c, int *size, char BUFFER[BUFFER_SIZE]);
void		ft_print_ptr_err(unsigned long long ptr, int *size,
				char BUFFER[BUFFER_SIZE]);
void		uns_2(unsigned int nbr, char *base, int *size,
				char BUFFER[BUFFER_SIZE]);
void		ft_putncount_str_err(char *str, int *size,
				char BUFFER[BUFFER_SIZE]);
int			ft_printf2(const char *text, ...);

/* -------------------------------------------------------------------------- */
/*									UTILS									  */
/* -------------------------------------------------------------------------- */

size_t		ft_strlen_c(const char *str, char c, bool *found);
char		*ft_strdup_c(const char *s, int *j, char c, bool *found);
int			ft_strcmp_c( const char *first, const char *second, char c);
int			ft_strcmp( const char *first, const char *second);
char		*ft_strndup(const char *s, int n);
void		ft_free_env(t_env_list **head);
void		ft_free_split(char **tab);
void		free_nodes(t_env_list *node);
char		*ft_strcpy(char *dest, const char *src);
char		*strjoin_and_free(char *s1, const char *s2);
char		*ft_strdup2(const char *s);
char		*ft_strjoin_f(char *s1, char *s2, bool to_free);
void		*ft_memset2(void *s, int c, size_t n);
int			ft_isspace(int c);
void		ft_free(void *ptr);
void		free_heredocs(t_heredoc *heredocs, bool to_unlink);
char		*ft_strnstr_i(const char *big, const char *little, size_t len,
				size_t *i);
#endif