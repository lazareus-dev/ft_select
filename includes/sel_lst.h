/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sel_lst.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/21 16:21:18 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/21 16:25:15 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef SEL_LST_H
# define SEL_LST_H

int		init_arglst(t_headlst *lst, int ac, char **av);
void	print_arglst(t_headlst *lst);
void	free_arglst(t_headlst *lst);

#endif
