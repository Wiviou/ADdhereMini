/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 02:16:45 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/17 23:03:53 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../libft/ft_printf/ft_printf.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/stat.h> 

extern volatile sig_atomic_t	g_child_running;

// -- Structure Execution -- //
typedef struct s_stat
{
	char	**alloc;
	int		status;
	int		i;
	int		is_append;
	int		in_file;
	char	*sss;
	int		s;
	int		out_file;
	int		fd_fd;
	int		fd;
	int		ffd;
	int		in;
	int		out;
	char	*line;
	char	*cmd_path;
	int		pip[2];
	int		pipex[2];
	pid_t	pid;
	pid_t	*pide;
	int		y;
	int		out_fd;
	int		in_fd;
	char	**ihia;
	int		n;
	char	*cmd;
	char	*command;
	int		is_out_in;
	int		is_in;
	int		x;
	int		k;
	char	*kkk;
	int		kj;
	int		gg;
	int		vg;
	int		*piper;
	int		nbr_pipe;
	int		is_redir;
	int		is_in_echo;
	int		fff;
	int		is_kate;
	int		is_build;
	int		pi[2];
	int		rx;
}		t_stat;

typedef struct t_s
{
	int	i;
	int	h;
	int	sec;
	int	start;
	int	end;
	int	blend;
	int	lend;
}	t_n;

typedef enum s_token
{
	WORD,
	COMMAND,
	PIPE,
	HEREDOC,
	REDIR_IN,
	REDIR_OUT,
	APPEND_REDIR_OUT,
	BUILT_IN,
	DEAD,
	R,
}	t_token;

// -- Structure pour gerer unset et export	ENVP -- //
typedef struct s_env
{
	char	*key;
	char	*val;
}	t_env;

typedef struct s_envp
{
	t_env			*env;
	struct s_envp	*next;	
}	t_envp;

//* STRUCTURE POUR Norme *//
typedef struct s_struct
{
	int		jkll;
	t_token	c;
	int		ppp;
	int		iii;
	int		ff;
	int		verife;
	int		echo;
	int		redir;
	int		out_redir;
	int		vvvx;
	int		r_pipe;
	size_t	len;
	size_t	i;
	size_t	j;
	size_t	f;
	size_t	l;
	size_t	g;
	int		nbr_pipe;
	int		v;
	char	*out;
	char	quote;
	char	*key;
	char	*val;
	char	**envv;
	int		pipe;
	int		fd;
	int		ffd;
	int		preout;
	t_stat	state;
	char	*temp_str;
	char	*porte;
	char	**enve;
	int		vfv;
	int		interro;
	int		simple_file;
	int		exit_nodig;
	int		exit_to_many;
	int		exit_val;
	int		no_val;
	int		plus;
	int		ambigus;
	char	*result;
	char	*temp;
	char	*path;
	char	**dir;
	char	**arg;
	char	*full_path;
	int		hhx;
	int		built_in;
	int		is_cat;
	int		is_cd;
	int		o;
	int		dead;
	char	*rsult;
	char	*couleur_in;
	char	*couleur_out;
	size_t	len_invite;
	char	*invite;
	t_envp		*envp;
	char	**eeenv;
	char	*lun;
}	t_struct;


// Structure Liste chainee de struct liste chainee de structure //
typedef struct s_dta
{
	char	*val;
	t_token	token;
}	t_dta;

typedef struct s_sub
{
	t_dta			*dta;
	struct s_sub	*next;
}	t_sub;

typedef struct s_node
{
	t_sub			*sub;
	struct s_node	*next;
}	t_node;

typedef struct heredoc_data_s
{
	int		num_delimiters;
	char	**delimiters;
	char	**temp_filenames;
	char	*cmd;
	int		final_fd;
	char	final_tempfile[256];
}	t_heredoc_data_t;

typedef struct s_t
{
	t_envp		*envp;
	t_node		*node;
	t_sub		*sub;
	t_struct	*rr;
	t_n			*catn;
	int			l;
	int			kk;
	int			o;
	char	*luna;
}	t_t;

// main1 //
void	pwd_o(t_struct **rr);
char	*invite_pwd(t_struct **rr);
void	init_main(t_struct **rr, t_envp **envp, char **env);

// main2 //
int		check_struct(t_struct **rr, t_n **catn);
void	init_main(t_struct **rr, t_envp **envp, char **env);
char	*concat_n(char *line, t_n **catn);

// main3 //
int		p_main(char ***dir, t_t **k_, char **processed_line);
int		pro_main(t_t **k_, char **processed_line);
int		main_read(t_t **k_, char **line, char ***dir, char	**luna);
t_t		*init_k(void);

// main4 //
void	concat_ni(t_n **catn, char *line, char **no_n);
void	init_main_read(t_t **k_);

// execute here command ... 
void	execute_child_process(char **argv);
int		ft_str_isdigit(char *s);

// command_main1 //
int		init_command_search(char *cmd, t_struct **rr, char **path);
int		setup_search_structures(char *path, char *cmd, char ***dir, \
		char ***arg);
int		process_command_search(char **dir, char **arg, t_struct **rr);

// command_main2 //
void	cleanup_search_structures(char **arg, char **dir);
int		command_exist(char *cmd, t_struct **rr);
void	so_clean(char *s, int *i, int *v);

// read_shell2 //
void	read_filter(t_node **node, t_struct **rr);
void	read_filter0(t_node **node, t_struct **rr);
int		true_pwd(char **command, t_struct **rr, t_node **node);

// read_shell1 //
char	**node_command(t_sub **sub);
void	init_stcat(t_node **node, t_struct **rr);

// read_shell3 //
int		read_fd0(char **command, t_struct **rr);
int		read_fd00(char **command, t_struct **rr);
int		read_fd1(char **command, t_struct **rr, t_node **node);

// read_shell4 //
void	read_jkll(int *jkl, t_struct **rr, t_node **node, char **command);
int		read_cd(char **command, t_struct **rr, t_node **node, t_envp **envp);

// read_shell5 //
void	read_inn(t_struct **rr, t_node **node, char **command);
int		read_statek(int *jkl, t_struct **rr, t_node **node, char **command);
void	read_ambigus(t_struct **rr, t_node **node, char **command);
void	read_state_pi(t_struct **rr, t_node **node, char **command);

// read_shell6 //
int		read_exitx(t_struct **rr, char **command, t_node **node);
void	read_now(t_struct **rr, char **command, t_envp **envp);

// read_shll7 //
void	read_co(t_struct **rr, t_envp **envp, char **command);

// read_shell8 //
int		read_part1(int *jkl, char **command, t_struct **rr, t_node **node);
int		read_part2(t_envp **envp, char **command, t_struct **rr, t_node **node);
int		read_part3(char **command, t_node **node, t_struct **rr);
int		read_concat(char **command, t_node **node, t_struct **rr);
void	compacte_read(t_struct **rr, t_envp **envp, char **command, t_node **node);
char	**handle_heredocs(char **delimiters, int num_delimiters);
int		count_heredoc_delimiters(char *line);
char	**extract_delimiters(char *line, int *num_delimiters);
int		open_and_write_tempfile(char *filename, char *delimiter);
char	**allocate_temp_filenames(int num_delimiters);
char	*generate_unique_temp_filename(void);

//pour extract delim ! 
char	**resize_delimiters_array(char **delimiters, int *capacity);
char	*extract_next_delimiter(char **start, int *num_delimiters, \
								char **delimiters, int *capacity);
void	free_delimiters(char **delimiters, int num_delimiters);

//process;;
char	*process_heredocs(char *line);
char	*replace_heredoc_with_tempfile(char *original_line, \
char **temp_filenames, int num_delimiters);
char	*allocate_new_line(void);
char	*replace_heredoc_with_tempfile(char *original_line, \
char **temp_filenames, int num_delimiters);
void	insert_filename(char **dest, char *filename);
char	*skip_heredoc_identifier(char *start);
int	copy_until_heredoc(char **dest, char *src, char *end);
void	cleanup_delimiters_and_tempfiles(char **delimiters, \
		char **temp_filenames, int num_delimiters);
int		open_final_tempfile(char *final_tempfile);
void	copy_tempfiles_to_final(char **temp_filenames, int num_delimiters, \
								int final_fd);
void	exe_command(char *cmd, char *final_tempfile, char **temp_filenames, \
					int num_delimiters);

//copy multiple tempfile car tempfiles to final avait 29 lines
void	copy_single_tempfile(int final_fd, char *temp_filename);
void	copy_tempfiles_to_final(char **temp_filenames, int num_delimiters, \
									int final_fd);
void	interro_state(t_struct **rr);

//build_utils.c
void	echo_tab_fd(int i, char **echo_tab, t_struct **rr, int f);

//exec_utils.c //
void	is_in_file(t_stat *state);
void	is_out_redir(t_stat *state);
void	exec_sig(t_stat *state, char **cmd, t_envp **env, t_struct **rr);
void	path_exec_1(char **full_path, char **dir, t_stat *state, char **cmd);

// -- exec .c -- //
int		manni(char *cmd);
void	command_exec(char **cmd, t_envp **env, t_struct **rr);
void	pero_frexit(char *s, void *k);
void	perrus(char *s);
void	process_buffer(char *buffer, int bytes_read, int output_fd, \
							t_struct **rr);

// ***	1 2 3 ///** 
void	command_exec1(char **cmd, t_envp **envp, t_struct **rr);
void	command_exec2(char **cmd, t_envp **envp, t_struct **rr);
void	command_exec3(char **cmd, t_envp **envp, t_struct **rr);
void	wait_pid(t_stat **state);

// -- EXEC Now 1 2 3 == //
void	command_exec_now(char **cmd, t_envp **envp, t_struct **rr);
void	command_exec_now1(char **cmd, t_envp **envp, t_struct **rr);
void	command_exec_now2(char **cmd, t_envp **envp, t_struct **rr);
void	command_exec_now3(char **cmd, t_envp **envp, t_struct **rr);

// -- gestin_liste .c -- //
t_node	*create_node(t_sub *sub);
void	push(t_node **head_ref, t_sub *sub);
void	print_list(t_node *node);
void	delete_list_and(t_node **head);
void	append(t_node **head_ref, t_sub *sub);
void	delete_node(t_node **node_ref);

// -- Gestion D list -- //
t_sub	*create_sub_node(char *val, t_token c);
void	push_d(t_sub **head_ref, char *val, t_token c);
void	print_sub(t_sub *sub);
void	delete_sub_list(t_sub **head_ref);
void	append_d(t_sub **head_ref, char *val, t_token c);

// -- token.c -- //
void	token(char **t, t_node **node, t_sub **sub, t_struct **rr);
int		tokennix01(t_struct **rr, char **t);
int		tokennix02(char **t, t_struct **rr, int *hh);
int		tokennix03(t_struct **rr, char **t, int *hh);
void	plop(char c, int *hh);
int		built_in(char *in, t_struct **rr);
t_token	tokennix(char **t, t_struct **rr, int *hh);
t_token	tokennix07(char **t, t_struct **rr, int *hh);
int		tokennix06(t_struct **rr, char **t);
int		tokennix05(char **t, t_struct **rr);
int		tokennix04(t_struct **rr, char **t, int ret);
int		token_command0(t_node *new_node);
t_node	*find_by_val(t_node *head, t_struct **rr, int r_pipe);
void	insert_node(t_node **head, t_node *new_node, int r_pipe);
int		token_command1(t_node *new_node, t_struct **rr, char **t);
t_node	*find_by_pipe(t_node *head, int r_pipe);
void	token_dead(t_struct **rr, char **t, t_node **node, t_sub **sub);
int		token_command(t_struct **rr, t_sub **sub, t_node **node, char **t);
void	token_pipe(t_struct **rr, char **t, t_node **node, t_sub **sub);
int		token_command_0(t_struct **rr, char **t, t_node **node, t_sub **sub);
int		token_command2(t_struct **rr, char **t, t_node **node);
void	token_append(t_struct **rr, char **t, t_node **node, t_sub **sub);
void	token_in(t_struct **rr, char **t, t_node **node, t_sub **sub);
void	token_out(t_struct **rr, char **t, t_node **node, t_sub **sub);
void	token_word(t_struct **rr, char **t, t_node **node, t_sub **sub);
void	init_token(t_struct **rr);
int		token_world(t_struct **rr, char **t, t_node **node, t_sub **sub);
int		token_pipx(t_struct **rr);
void	token_echo(t_struct **rr, char **t, t_sub **sub);

// -- token_0 .c -- //
int		is_token(t_token c);
int		valid_access(char **s, t_struct **rr);
char	*get_env(char *key, t_struct **rr);
int		is_chr(char **s, t_struct **rr);
void	change_last_access(char *cmd, t_struct **rr);
int		is_innchr(char **s, struct stat *path_stat);
int		is_inchr(char **s, t_struct **rr);
int		valid_path(char **s, char **dir, t_struct **rr);
int		valid_access(char **s, t_struct **rr);

// -- Utils .c -- //
void	free_tab(void	**f);
void	ft_get_line(int fd, int out);
void	ft_lseek(int fd, const char *filename, mode_t mode);
void	ft_get_endline(int fd, int out);

// -- ft_split_quote . c-- //
char	**ft_split_quote(const char *s, char c1, char c2);
char	**free_mem(char **tab, size_t id);
void	is_in_quote(char c, int *in, int *inn);

// -- Clean Quote .c  -- //
char	**clean_quote_tab(char **tab, t_struct **rr);

//- - search_multi .c - -//
char	*search_multi(char	*line);

// -- envp .c -- //
void	make_env(t_envp **envp, char **env, t_struct **rr);
void	env_env(t_struct **rr);
void	refact_env(t_envp **envp, t_struct **rr);
void	export_env(t_envp **envp, char **key_val, t_struct **rr);
void	unset_env(t_envp **envp, char **key);
void	see_export(t_struct **rr);
char	**see_export1(int n, t_struct **rr);
void	see_export01(int i, char **temp);
void	see_export02(int i, char **temp, t_struct **rr);
char	*export_env0(int i, char **key_val, t_struct **rr);
void	process_redir(int i, char **temp, t_struct **rr);
int		verife_env_and_del(t_envp **envp, t_struct **rr);
int		count_env_vars(t_struct **rr);
void	process_non_redir(int i, char **temp, t_struct **rr);
int		andel(t_envp **envp, t_envp **prev, t_envp **cur, t_struct **rr);
void	ve_andel(t_envp **envp, t_envp **prev, t_envp **current);
void	ve_andel0(t_struct **rr, t_envp **current);

// -- liste_env .c -- //
t_envp	*create_t_envp(char *key, char *val);
void	push_env(t_envp **head_ref, char *key, char *val);
void	append_envp(t_envp **head_ref, char *key, char *val);
void	print_envp(t_envp *envp);
void	delete_envp(t_envp **head_ref);
void	delete_env(t_envp **head_ref, char **key, t_struct **rr);
void	re_set_enve(t_envp **envp, t_struct **rr);

// -- read_shell .c -- //
int		read_shell(t_node **node, t_envp **envp, t_struct **rr, char **env);

// -- command_main .c -- //
char	**command_path(char *cmd, t_struct **rr);
int		command_exist(char *cmd, t_struct **rr);
int		cd_command(char **tab, t_struct **rr, t_envp **envp);
void	destroy_file(void);

// -- build .c -- //
void	handle_sigint(int sig);
void	setup_sigint_handler(void);
void	ft_echo_co(char **echo_tab, t_struct **rr);

// -- clean concate .c-- 
char	*clean_concat(char *s);

void	pwd_o(t_struct **rr);

void	stor_env(t_envp **envp, t_struct **rr);

// --  exec_utils.c - //
int		path_exec(t_stat *state, char **cmd, t_struct **rr);

//-- -- //
void	setup_child_signal_handlers(void);

//--- ---//
char	*extract_delimiter(char *line);
char	*generate_temp_filename(void);
char	*split_command(char *line);
void	safe_command_concat(char *cmd, const char *to_add);
void	write_line_to_fd(int fd, const char *line);
void	setup_argv(char **argv, char *cmd);
int		execute_here_command(char **argv);
char	*perform_replacements(const char *str, size_t total_length, \
			t_struct **rr);
void	handle_dollar_expansions(const char **str, char **temp, \
				const char *end, t_struct **rr);
int		is_within_double_quotes(const char *str, const char *pos);
void	handle_variable_replacement(const char **ptr, char **temp, \
			const char *end, t_struct **rr);
void	safe_append_string(char **dest, const char *src, const char *end);
void	perform_variable_expansion(const char **str, char **temp, \
		const char *end, t_struct **rr);
int		is_within_single_quotes(const char *str, const char *pos);
size_t	calculate_special_length(const char **str, t_struct **rr);
size_t	calculate_required_length(const char *str, t_struct **rr);
char	*extract_env_key(const char *start, const char *end);
void	handle_variable_inside_quotes(const char **str, char **temp, \
				const char *end, t_struct **rr);
void	handle_quotes(const char **str, char **temp, const char *end, \
						t_struct **rr);
void	handle_special_variable(const char **ptr, char **temp, \
				const char *end, t_struct **rr);
size_t	handle_length_calculation(const char **ptr, t_struct **rr);
size_t	handle_dollar_signs(const char **str);
size_t	handle_environment_variables(const char **str, t_struct **rr);
size_t	handle_question_mark(const char **str, t_struct **rr);
void	append_string(char **dest, const char *src);
void	env_command(t_envp **envp);
void	export_command(char **command, t_struct **rr, t_envp **envp);
void	unset_command(int *v, t_struct **rr, char **command, t_envp **envp);
void	echo_command(int *v, t_struct **rr, char **command);

#endif
