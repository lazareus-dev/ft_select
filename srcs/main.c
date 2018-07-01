/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 10:55:55 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/01 16:26:14 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <termcap.h>
#include "../includes/ft_select.h"
#include "../includes/sel_select.h"
#include "../includes/sel_refresh.h"
#include "../includes/sel_lst.h"
#include "../includes/sel_signal.h"
#include "../includes/sel_loop.h"

void	init_term(void)
{
	tputs(tgetstr("ti", NULL), 1, ft_putchar_term);
	tputs(tgetstr("vi", NULL), 1, ft_putchar_term);
}

void	restore_term(t_select *select)
{
	if (!select)
		select = get_select();
	tcsetattr(select->fd, TCSAFLUSH, &(select->orig_termios));
	tputs(tgetstr("te", NULL), 1, ft_putchar_term);
	tputs(tgetstr("ve", NULL), 1, ft_putchar_term);
}

int		main(int ac, char **av)
{
	t_select	*select;

	if (ac == 1)
		return (0);
	if (!(select = get_select()))
		return (1);
	init_arglst(select, ac, av);
	sig_handlers();
	sel_refresh(NULL);
	sel_loop();
	restore_term(NULL);
	echo_result();
	clear_select();
	return (0);
}
