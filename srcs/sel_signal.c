/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sel_signal.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/29 14:44:37 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/01 15:11:25 by tle-coza    ###    #+. /#+    ###.fr     */
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

static void	handle_winch(int sig)
{
	signal(SIGWINCH, SIG_IGN);
	sel_refresh(NULL);
	signal(SIGWINCH, handle_winch);
}

static void	sigint_handler(int sig)
{
	t_select	*select;

	select = get_select();
	if (sig == SIGTSTP)
	{
		signal(SIGTSTP, SIG_DFL);
		restore_term(select);
		ioctl(0, TIOCSTI, "\x1a");
	}
	else if (sig == SIGCONT)
	{
		signal(SIGTSTP, sigint_handler);
		tcsetattr(0, TCSANOW, &(select->term));
		init_term();
		sel_refresh(select);
	}
	else
	{
		clear_select();
		restore_term(select);
		exit(0);
	}
}

void		sig_handlers(void)
{
	signal(SIGWINCH, handle_winch);
	signal(SIGINT, sigint_handler);
	signal(SIGTERM, sigint_handler);
	signal(SIGQUIT, sigint_handler);
	signal(SIGABRT, sigint_handler);
	signal(SIGCONT, sigint_handler);
	signal(SIGTSTP, sigint_handler);
	signal(SIGUSR1, sigint_handler);
	signal(SIGUSR2, sigint_handler);
	signal(SIGSEGV, sigint_handler);
	signal(SIGHUP, sigint_handler);
}
