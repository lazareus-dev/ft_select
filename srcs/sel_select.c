/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sel_select.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/22 11:06:26 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/22 11:39:36 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

t_select	*new_select()
{
	t_select	*select;

	init_select(select);
	init_termios(select);
	return (select);
}

t_select	*get_select()
{
	static t_select	*select;

	if (select == NULL)
		select = new_select();
	return (select);
}

int     init_select(t_select *select)
{
	char    *termtype;
	int     ret;

	select->buff = NULL;
	if (!(termtype = getenv("TERM")))
	{
		ft_putendl_fd("TERM not set\n" ,2);
		return (-1);
	}
	ret = tgetent(NULL, termtype);
	if (ret == -1)
	{
		ft_putendl_fd("Can't access termcap DB\n" ,2);
		return (-1);
	}
	else if (ret == 0)
	{
		ft_putendl_fd("Terminal type not defined in DB\n" ,2);
		return (-1);
	}
	return (0);
}

int     init_termios(t_select *select)
{
	if (tcgetattr(0, &(select->orig_termios)) == -1)
		return (1);
	if (tcgetattr(0, &(select->term)) == -1)
		return (1);
	select->term.c_lflag &= ~(ICANON); /* Met le terminal en mode canonique. La fonction Read recevra les entrées clavier en direct sans attendre qu'on appuie sur Enter */
	select->term.c_lflag &= ~(ECHO); /* Les touches tapées au clavier ne s'affficheront plus dans le terminal */
	select->term.c_cc[VMIN] = 1;
	select->term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &(select->term)) == -1)
		return (1);
	return (0);
}
