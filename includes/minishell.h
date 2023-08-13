/* ************************************************************************** */
/*																			*/
/*					                                    :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:26:39 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/03 18:53:58 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdint.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <ctype.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <errno.h>
# include <fcntl.h>

typedef struct s_token
{
	enum
	{
		TOKEN_PIPE,
		TOKEN_INFILE,
		TOKEN_OUTFILE,
		TOKEN_STRING,
		TOKEN_HERE_DOC,
		TOKEN_APPEND,
		TOKEN_EOF
	}	e_type;
	char	*content;
}	t_token;

typedef struct setval
{
	int		i;
	int		start;
	char	*result;
	bool	in_single_quotes;
	bool	in_double_quotes;
}	t_sv;

typedef struct s_command
{
	t_token				*content;
	struct s_command	*next;
}	t_command;

typedef struct s_cmd
{
	char			*cmd;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_file
{
	char			*filename;
	int				fd;
	int				type;
	struct s_file	*next;
}	t_file;

typedef struct DATA_STRUCT
{
	pid_t				pid;
	t_cmd				*cmd;
	t_file				*file;
	struct DATA_STRUCT	*next;
}	t_data;

typedef struct s_envs
{
	char			*env;
	char			*value;
	struct s_envs	*next;
}	t_envs;

typedef struct s_g
{
	char			**env;
	int				exit_status;
	int				exit_save;
	int				in_fd;
	struct s_envs	*envs;
	int				out_fd;
	int				fd[2];
	int				pos;
	uintptr_t		*ptr;
	int				len;
}	t_g;

t_g			g_lob;

typedef struct s_context
{
	t_command	*lexer;
	t_file		*file;
	t_cmd		*cmd;
	char		**env;
}	t_context;

void		ft_putstr_fd(char *s, int fd);
int			handle_type_4(t_context *context, int count);
void		handle_other_types(t_context *context);
void		handle_type_3(t_context *context);
void		handle_type_0_6(t_context *context, t_data **data);
void		init_vals(t_sv *a);
void		_exitstatus(t_sv *a, char *str);
void		_dollarsign(t_sv *a, char *str);
void		special_chars(t_sv *a, char *str);
void		qoutescase(t_sv *a, char *str);
int			read_line(char **line);
void		init_globals(char **env);
void		process_input_line(char **line);
void		handle_command_execution(t_data *data);
char		*get_env_value(char **env, char *temp, int start, int i);
char		*append_segment(char *result, char *str, int start, int end);
char		*append_env_value(char *result, char *value);
void		assign_less_than_type(t_token *token, char character,
				char next_char);
void		assign_greater_than_type(t_token *token, char character,
				char next_char);
void		assign_pipe_type(t_token *token);
void		assign_eof_type(t_token *token);
void		assign_string_type(t_token *token);
t_token		*init_tokens(void);
void		skip_whitespace(char *line, int *i);
void		process_eof(char *line, int i, t_command **lexer);
void		create_and_process_token(char *line, int *i, t_command **lexer);
void		hadnle_signle(int n);
char		**lst_to_envs(t_envs *ptr);
void		free_data(t_data *head);
char		*get_value(char	*value);
char		*get_env_plus(char *str);
void		process_tokens(char *line, t_command **lexer);
t_token		*create_token(char character, char next_char);
char		*add_char(char *str, char c);
int			check_syntax_errors(t_command *lexer);
int			check_quotes(char *input);
char		*expand_result(char *str, char **env, int hide);
char		*remove_quotes(char *line);
int			is_valid_identifier(char *str);
void		add_to_env_if(char *str);
void		add_to_env(char *str);
void		join_values(char *str);
t_envs		*set_envs(char **av);
void		rl_replace_line(const char *str, int i);
char		*get_envs(char *str);
char		*extract_substring(char *str, int start, int end);
bool		is_variable_character(char c);
char		*append_to_str(char *dest, char *src);
char		*str_alloc_copy(const char *src);
void		err_export(char *str);
void		exit_cmd(char **cmd);
//libft
int			ft_strlen(char *str);
int			ft_strrchr(const char *s, int c);
void		ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
t_command	*ft_lstnew(t_token *content);
t_data		*ft_lstnew_data(t_file *file_name, t_cmd *cmd);
void		ft_lstadd_back_data(t_data **lst, t_data *new);
t_file		*ft_lstnew_file(char *file_name, int type);
void		ft_lstadd_back_file(t_file **lst, t_file *new);
t_cmd		*ft_lstnew_cmd(char *cmd);
void		ft_lstadd_back(t_command **lst, t_command *new);
char		*ft_substr(char *s, unsigned int start, size_t len);
char		*ft_strjoin(char *s1, char *s2);
char		**ft_split(char const *s, char c);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strdup(const char *s1);
char		*ft_itoa(int n);
char		*ft_strchr(char *str, int c);
t_envs		*ft_lstnew_env(char *str);
void		ft_lstadd_back_env(t_envs **lst, t_envs *new);
t_envs		*ft_lstnew_plus(char *str);
char		*ft_strncpy(char *dest, char *src, unsigned int n);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strcat(char *dest, char *src);
char		*ft_strcpy(char *dest, char *src);
int			ft_tabsize(char **tab);
char		**arr_dup(char **tab);
// builtins
void		re_unset(char **args);
void		re_export(char **args);
void		pwd(t_envs *env);
int			cd_cmd(char **args);
void		simple_echo(char **args);
void		_env(char **env);
// heredoc
int			check_flag(t_file *tmp);
int			iterate_files(t_data *lexer, int fd[2]);
void		read_and_write(int flag, char *filename, int fd[2]);
int			here_document(t_data *lexer);
// exec
void		*my_malloc(size_t size);
void		my_free(void *address);
void		my_free_all(void);
void		ft_memset(void *pointer, int c, size_t len);
void		*ft_memcpy(void *destination, void *source, size_t len);
int			check_builtins(t_data *proc);
int			is_builtin(char *cmd);
void		exec_builtin(char **args, int index);
int			ft_lstsize_envsss(t_envs *lst);
char		**lst_to_args(t_cmd *ptr);
void		manage_duplications_and_closing(void);
void		exec_cmd_or_builtin(t_data *proc, char **args);
void		cleanup_after_exec(void);
void		process_files_builting(t_file *ptr);
int			openfiles(t_file *ptr);
void		setup_pipe_and_fork(t_data *proc, int *pass);
void		setup_signal_handlers(void);
void		process_files(t_file *ptr);
void		manage_file(t_file *ptr);
char		*cmd_path(char **paths, char *cmd, int i);
void		skip_spaces(char **file);
void		process_quotes(char **file, char *c);
void		close_and_open_infile(t_file *ptr);
void		close_and_open_outfile(t_file *ptr);
char		**_paths(char **p);
int			stat_fun(char *str);
void		error_check(int a, char *str);
void		execution(t_data *data);

#endif