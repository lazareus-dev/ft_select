/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sel_signal.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/29 14:44:37 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/29 15:04:27 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <termcap.h>
#include <signal.h>
#include <sys/ioctl.h>
#include "../includes/ft_select.h"
#include "../includes/sel_select.h"
#include "../includes/sel_lst.h"
#include "../includes/sel_refresh.h"

void handle_winch(int sig)
{
	signal(SIGWINCH, SIG_IGN);
	sel_refresh(NULL);
	signal(SIGWINCH, handle_winch);
}
void	sigint_handler(int sig)
{
	t_select	*select;

	select = get_select();
	if (sig == SIGTSTP)
	{
		signal(SIGTSTP, SIG_DFL);
		ioctl(0, TIOCSTI, "\x1a");
		restore_term(select);
	}
	else if (sig == SIGCONT)
	{
		signal(SIGTSTP, sigint_handler);
		tcsetattr(0, TCSANOW, &(select->term));
	}
	else
	{
		clear_select();
		restore_term(select);
		exit(0);
	}
}

void	sig_handlers(void)
{
	signal(SIGWINCH, handle_winch);
	signal(SIGINT, sigint_handler);
	signal(SIGTERM, sigint_handler);
	signal(SIGQUIT, sigint_handler);
	signal(SIGCONT, sigint_handler);
	signal(SIGTSTP, sigint_handler);
//	if ((signal(SIGSEGV, sigint_handler) == SIG_ERR))
//		ft_putendl("SIGSEGV error");
}
