#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

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

