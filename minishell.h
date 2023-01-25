/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltombell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:45:27 by aboncine          #+#    #+#             */
/*   Updated: 2023/01/25 12:19:39 by ltombell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "get_next_line.h"

typedef struct s_cmd	t_cmd;

typedef struct s_prg
{
	t_cmd	*cmds;
	char	**envp;
	pid_t	pid;
}		t_prg;

typedef struct s_cmd
{
	char	**full_cmd;
	int		infile;
	int		outfile;
	char	*delimiter;
	t_cmd	*next;
}		t_cmd;

extern int exitStatus;

char	**ft_split(char const *s, char c);
char	**get_paths(char **envp);
void	execute_cmd(char **cmd_args, char **envp);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**variable_expander(char **prompt);
char	*ft_strdup(const char *s);
char	**ft_simple_split(char const *s, char c);
char	*extract_var(char *s);
char	**parse_pipe_min_mag(char **prompt);
char	*ft_strncpy(char *s, int start, int finish);
int		is_there_a_special_char(char *s);
void	ft_add_element(t_cmd **cmd_list, char **cmd_arr);
void	ft_clean_list(t_cmd *comandi);
void	ft_simple_echo(char **to_print, int n);
char	*ft_create_sc_word(char *s, int start, int i);
int		how_many_strings(char **prompt);
int		how_many_strings_with_s_c(char *s);
int		is_there_a_special_char(char *s);
int		how_many_special_chars(char *s);
char	*create_str3(char const *s, int *i, int *flag, char *c);
void	here_doc_handler(char *delim);
void	ft_execute_child(t_prg *box, char **envp);

#endif
