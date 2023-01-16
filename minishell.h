#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef	struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_prg
{
	t_list	*cmds;
	char	**envp;
	pid_t	pid;
}		t_prg;

typedef struct s_cmd
{
	char	**full_cmd;
	char	*full_path;
	int	infile;
	int	outfile;
}		t_cmd;

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

