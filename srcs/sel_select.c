/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sel_select.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/22 11:06:26 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/29 15:29:01 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_select.h"
#include "../includes/sel_lst.h"
#include <termcap.h>
#include <stdlib.h>
#include <sys/ioctl.h>

int     get_termtype()
{
	char    *termtype;
	int     ret;

	if (!(termtype = getenv("TERM")))
	{
		ft_putendl_fd("TERM not set\n", 2);
		return (-1);
	}
	ret = tgetent(0, termtype);
	if (ret == -1)
	{
		ft_putendl_fd("Can't access termcap DB\n", 2);
		return (-1);
	}
	else if (ret == 0)
	{
		ft_putendl_fd("Terminal type not defined in DB\n", 2);
		return (-1);
	}
	return (0);
}

int     set_termios(t_select *select)
{
	if (isatty(STDIN_FILENO) == 0 || tcgetattr(0, &(select->orig_termios)) == -1)
		return (1);
	if (tcgetattr(0, &(select->term)) == -1)
		return (1);
	select->term.c_lflag &= ~(ICANON | ECHO);
	select->term.c_cc[VMIN] = 1;
	select->term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &(select->term)) == -1)
		return (1);
	return (0);
}

t_select	*new_select(void)
{
	t_select	*select;

	if (!(select = (t_select *)malloc(sizeof(t_select))))
		return (NULL);
	select->buff = NULL;
	if (!(select->arglst = (t_headlst *)malloc(sizeof(t_headlst))))
		return (NULL);
	if (get_termtype())
		return (NULL);
	set_termios(select);
	ioctl(0, TIOCGWINSZ, &(select->win));
	return (select);
}

t_select	*get_select(void)
{
	static t_select	*select;

	if (!select)
		if (!(select = new_select()))
			return (NULL);
	return (select);
}

void    clear_select(void)
{
	t_select	*select;

	select = get_select();
	free_arglst(select->arglst);
	ft_strdel(&(select->buff));
	free(select);
}
