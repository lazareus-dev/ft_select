/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sel_select.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/22 11:06:26 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/30 21:22:31 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_select.h"
#include "../includes/sel_lst.h"
#include "../includes/sel_error.h"
#include "../includes/sel_refresh.h"
#include <termcap.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>

int			get_termtype(void)
{
	char	*termtype;
	int		ret;

	if (!(termtype = getenv("TERM")))
		return (term_error(TERM_NOT_SET));
	ret = tgetent(NULL, termtype);
	if (ret == -1)
		return (term_error(ACCESS_DB));
	else if (ret == 0)
		return (term_error(TERM_NOT_FOUND));
	return (0);
}

int			set_termios(t_select *select)
{
	if (isatty(STDIN_FILENO) == 0)
		return (1);
	if ((select->fd = open(ttyname(STDIN_FILENO), O_RDWR)) == -1)
		return (1);
	if (tcgetattr(select->fd, &(select->orig_termios)) == -1)
		return (1);
	if (tcgetattr(select->fd, &(select->term)) == -1)
		return (1);
	select->term.c_lflag &= ~(ICANON);
	select->term.c_lflag &= ~(ECHO);
	select->term.c_cc[VMIN] = 1;
	select->term.c_cc[VTIME] = 0;
	if (tcsetattr(select->fd, TCSANOW, &(select->term)) == -1)
		return (1);
	init_term();
	return (0);
}

t_select	*new_select(void)
{
	t_select	*select;

	if (!(select = (t_select *)malloc(sizeof(t_select))))
		return (NULL);
	if (!(select->arglst = (t_headlst *)malloc(sizeof(t_headlst))))
		return (NULL);
	if (get_termtype())
		return (NULL);
	if (set_termios(select))
		return (NULL);
	set_winsize(select);
	select->fd = 0;
	return (select);
}

t_select	*get_select(void)
{
	static t_select	*select = NULL;

	if (!select)
		if (!(select = new_select()))
			return (NULL);
	return (select);
}

void		clear_select(void)
{
	t_select	*select;

	select = get_select();
	free_arglst(select->arglst);
	free(select);
}
