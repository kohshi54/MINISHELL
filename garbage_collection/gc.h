#ifndef GC_H
# define GC_H

# include "../libft/ft_printf.h"
# include "../libft/libft.h"

void	ft_free(void *ptr);
void	*ft_malloc(size_t size, t_list **list);
void	free_all_mallocated_area(t_list *list);

#endif