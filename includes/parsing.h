/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 22:10:31 by migusant          #+#    #+#             */
/*   Updated: 2026/02/17 14:19:24 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/includes/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

// Enable Debug Mode
# define MINISHELL_DEBUG	0

// Signal Modes
# define SIG_INTERACTIVE	0
# define SIG_IGNORE			1
# define SIG_DEFAULT		2
# define SIG_HEREDOC		3

// Cleanup Modes
# define CLEANUP_PARENT 0
# define CLEANUP_CHILD  1

// Token Types
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_SEMICOLON,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
}	t_token_type;

// Token Structure
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	int				hd_expand;
	int				wd_split;
	struct s_token	*next;
}	t_token;

// Redirection Structure
typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	int				fd;
	int				hd_expand;
	struct s_redir	*next;
}	t_redir;

// Command Structure
typedef struct s_cmd
{
	char			**args;
	t_redir			*redirections;
	struct s_cmd	*next;
}	t_cmd;

// Shell Structure
typedef struct s_shell
{
	char			**envp;
	t_cmd			*cmds;
	t_token			*toks;
	int				exit_code;
}	t_shell;

// ************************************************************************** //
//                                  PARSING                                   //
// ************************************************************************** //

// lexer.c
t_token	*lexer(char *input);

// lexer_helpers.c
t_token	*create_token(t_token_type type, char *value);
void	add_token(t_token **head, t_token *new_token);

// lexer_checks.c
int		is_whitespace(char c);
int		is_special_char(char c);

// lexer_utils.c
int		count_backslashes(char *str, int i);
char	*handle_word(char *input, int *i);

// lexer_quotes.c
void	copy_quoted_section(char *dst, char *src, int *dst_pos, int *src_pos);

// syntax_checker.c
int		check_syntax(void);

// parser.c
void	add_cmd_to_list(t_cmd **head, t_cmd *new_cmd);
int		parser(void);

// parser_utils.c
t_token	*parse_cmd(t_cmd *cmd, t_token *current);

// parser_split_mark.c
void	mark_word_split(t_token *tokens);

// parser_heredoc_mark.c
void	mark_heredoc_expansion(t_token *tokens);

// parser_split_apply.c
void	apply_word_split(t_token **tokens);

// expander.c
char	*expand_token(char *token);
void	expand_tokens(void);

// expander_quotes.c
char	*expand_single_quotes(char *str, int *i);
char	*expand_double_quotes(char *str, int *i);
char	*expand_ansi_c_quotes(char *str, int *i);

// expander_substitutions.c
char	*expand_tilde(char *str, int *i);
char	*extract_var_name(char *str, int *i);
char	*expand_variable(char *str, int *i);

// expander_heredoc.c
char	*expand_heredoc_line(char *line);

// expander_utils.c
char	*dup_char_and_advance(char c, int *i);
char	*expand_var_from_name(char *var_name);
char	*append_string(char *result, char *to_add);
char	*append_char(char *result, char c);

// quote_removal.c
void	handle_quotes(void);

// quote_removal_utils.c
int		count_unquoted_len(char *str);
void	copy_unquoted(char *dest, char *src);

// quote_removal_single.c
void	copy_single_quoted(char *dest, char *src, int *j, int *i);

// quote_removal_double.c
void	copy_double_quoted(char *dest, char *src, int *j, int *i);

// signals.c
void	setup_signals(int mode);

// free.c
void	free_tokens(t_token *tokens);
void	free_split(char **split);
void	free_cmd(t_cmd *cmd);
void	free_cmd_list(t_cmd *cmd_list);

// ************************************************************************** //
//                                ENVIRONMENT                                 //
// ************************************************************************** //

char	*ft_getenv(char **envp, char *key);

// ************************************************************************** //
//                                   MAIN                                     //
// ************************************************************************** //

// main.c
t_shell	*shell(void);
void	cleanup_resources(int mode);

// main_utils.c
int		validate_input(char *input);

// main_pipeline.c
void	process(char *input);

// main_debug.c
void	print_tokens(t_token *tokens, char *stage);
void	print_cmd_list(t_cmd *cmd_list, char *stage);

#endif