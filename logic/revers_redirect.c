#include "../includes/minishell.h"

t_cmd	*find_revers_redirect(t_cmd *cmd)
{
	while (cmd->next)
	{
		if (!ft_strncmp_nr(">", cmd->next->cmd, ft_strlen(cmd->next->cmd))
			|| !ft_strncmp_nr(">>", cmd->next->cmd, ft_strlen(cmd->next->cmd)))
		{
			cmd = cmd->next;
			continue ;
		}
		break ;
	}
	if (cmd->next)
	{
		if (!ft_strncmp_nr("<", cmd->next->cmd, ft_strlen(cmd->next->cmd))
			|| !ft_strncmp_nr("<<", cmd->next->cmd, ft_strlen(cmd->next->cmd)))
			return (cmd->next);
	}
	return (NULL);
}

int	get_fd_rredirecta(t_cmd *redirect)
{
	int	fd;

	fd = open(redirect->args[0], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd(redirect->args[0], 2);
		ft_putendl_fd(" : Error open file", 2);
		return (-1);
	}
	return (fd);
}

int	close_mistake(int fd, char *file)
{
	close(fd);
	ft_putstr_fd(file, 2);
	ft_putendl_fd(": can't read file", 2);
	return (-1);
}

int	find_infile_des(t_cmd *cmd)
{
	t_cmd	*redirect;
	int		fd;

	redirect = find_revers_redirect(cmd);
	while (redirect)
	{
		if (redirect->next && find_revers_redirect(redirect))
		{
			if (!ft_strncmp(redirect->cmd, "<", 2))
			{
				fd = open(redirect->args[0], O_RDONLY);
				if (fd < 0)
					return (close_mistake(fd, redirect->args[0]));
				close(fd);
			}
			redirect = find_revers_redirect(redirect);
			continue ;
		}
		return (get_fd_rredirecta(redirect));
	}
	return (0);
}

int	comand_revers_redirect(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->args[0], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd(cmd->args[0], 2);
		ft_putendl_fd(": can't read file", 2);
		close(fd);
		return (-1);
	}
	fd = find_infile_des(cmd);
	if (fd > 2)
		close(fd);
	return (0);
}
