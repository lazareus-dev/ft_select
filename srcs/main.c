/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 10:55:55 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/29 15:24:36 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <termcap.h>
#include <signal.h>
#include <sys/ioctl.h>
#include "../includes/ft_select.h"
#include "../includes/sel_select.h"
#include "../includes/sel_display.h"
#include "../includes/sel_lst.h"
#include "../includes/sel_signal.h"
#include "../includes/sel_keys.h"

void	restore_term(t_select *select)
{
	tputs(tgetstr("te", NULL), 0, ft_putchar_term);
	tputs(tgetstr("ve", NULL), 0, ft_putchar_term);
	tcsetattr(0, TCSANOW, &(select->orig_termios));
}

int		sel_loop(void)
{
	while (101)
	{
	}
}

void	init_ft_select(void)
{
	tputs(tgetstr("ti", NULL), 0, ft_putchar_term);
	tputs(tgetstr("vi", NULL), 0, ft_putchar_term);
}

void	clear_screen(void)
{
	int			i;
	t_select	*select;
	
	select = get_select();
	i = 0;
	while (i < select->win.ws_row)
	{
		ft_putstr_fd(tgoto(tgetstr("cm", NULL), 0, i), 2);
		ft_putstr_fd(tgetstr("ce", NULL), 2);
		i++;
	}
}

int		main(int ac, char **av)
{
	t_select	*select;
	int			ret;

	if (ac == 1)
		return (0);
	sig_handlers();
	select = get_select();
	init_arglst(select->arglst, ac, av);
	init_ft_select();
	display_list(select->arglst);
	voir_touche();
//	sel_loop();
	restore_term(select);
//	clear_screen();
	echo_result();
	clear_select();
	return (0);
}
