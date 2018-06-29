/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_select.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 13:08:40 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/29 17:15:14 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <termios.h>
# include "../libft/ft_printf/ft_printf.h"

# define RESET	"\e[0m"
# define V_INV	"\e[7m"
# define BOLD	"\e[1m"
# define GREEN	"\e[32m"

typedef struct termios	t_ermios;

typedef struct		s_elem
{
	char			*name;
	int				selected;
	int				cur;
	struct s_elem	*prev;
	struct s_elem	*next;
}					t_elem;

typedef struct		s_select
{
	t_ermios		term;
	t_ermios		orig_termios;
	struct winsize	win;
	t_headlst		*arglst;
	t_elem			*cur;
}					t_select;

#endif
