#ifndef TESTER_H
# define TESTER_H

# include <stdio.h>
# include <stdint.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_list
{
	void *data;
	struct s_list *next;
}	t_list;

extern size_t	ft_strlen(const char *str);
extern char		*ft_strcpy(char *dst, const char *src);
extern int		ft_strcmp(const char *s1, const char *s2);
extern ssize_t	ft_write(int fd, const void *buffer, size_t count);
extern ssize_t	ft_read(int fd, const void *buffer, size_t count);
extern char		*ft_strdup(const char *s);
extern int		ft_atoi_base(const char *str, const char *base);
extern void		ft_list_push_front(t_list **lst, t_list *new);
extern void 	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));
extern int		ft_list_size(t_list *lst);

#endif
