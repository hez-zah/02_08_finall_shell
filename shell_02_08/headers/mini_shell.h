/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:10:34 by hez-zahi          #+#    #+#             */
/*   Updated: 2023/07/29 17:53:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_limit
{
	char			*limit;
	int				index_limit;
	struct s_limit	*next_limit;	
}t_limit;


typedef struct s_pip
{
	char			**pip_arg;
	t_limit			*limit;
	int				fd_red[2];
	int				permi;
	int				spc_return;
	int				herd_in;
	int				herd_out;
	int				access;
	int				pip_infile;
	int				pip_outfile;
	int				pip_in;
	int				pip_out;
	int				index;
	struct s_pip	*next_pip;
}t_pip;

typedef struct s_pid
{
	t_pip	*all;
	char	**old_env;
}t_pia;

char		*ft_strjoin_exe(char const *s1, char const *s2);
size_t		ft_strlen1(const char *s);
char		*ft_concat(char const *s1, char const *s2);

char		*patht(char *cmd, char **env);
char		*ft_patht(char *cmd, char **env);
t_limit		*creat_linkdlist(t_limit	*head, char *limit, int index);

char		*get_next_line(int fd);
char		*ft_strjoin1(char const *s1, char const *s2);
char		*ft_strchr(const char *s, int c);
char		*copy(char *txt, char *save, int i);
char		*conc(char *stash, char *buf);

void		init_limit(t_pip *pip);
void		child_1(char **env, t_pip *pip);
void		child_2(char **env, t_pip *pip);
void		affich(t_pip *pip);
void		creat_pipe(t_pip *pip);
void		file_redric(t_pip *pip);
//redirection
t_pip		*redirect1(t_pip *pip);

void		herdoc(t_pip *pip);
void		file_red_pip(t_pip *pip, int i);

int			check_herdoc(char **arg);

t_pip		*make_pip(t_pip *head, char *arg, int index);

int			creat_file1(char *filename, int lo_method);

// redirect_fd.c
int			check_infile_herd(char **str);
int			ft_check_cmd_arg(char *str);

//closer.c
void		close_pip_file(t_pip *pip);
void		close_file(t_pip *pip);
void		close_fd_all(t_pip *all);
void		close_herd_file(t_pip *all);

void		free_stack_herdoc(t_limit **limit);
int			freeDoublePointer(char **str);
char		**ft_export_unset(t_pip *pip, char **new_env, int nbr);


//unset
char		**ft_unset(t_pip *pip, char **new_env, char **str, int nbr);
int			error_unset(char *str);
//export
int			aid_export(char **str, char **new_env, int nbr, int n);
char		**ft_export(char **new_env, char **str, int nbr, t_pip *pip);
int			set_env(char **env);
//export_just_affich
int			affich_env(char **env, int nbr);
//env
int			reel_env(char **str, char **env);
int			unset_env(char **str, char **env);
//cd
int			cmd_cd(char **cmd, char **env);
//echo
int			cmd_echo(char **cmd);
//exit
int			cmd_exit(char **cmd, int last_return);
int			exit_atoi(const char *nptr, int *error);
//pwd
int			cmd_pwd(char **cmd, char **env);
////
int			exp_uns(char *led);

#endif
