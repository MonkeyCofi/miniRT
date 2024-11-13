#ifndef FREES_H
# define FREES_H

# include <structs.h>

void	free_shapes(t_minirt *minirt);
void	free_things(t_minirt *minirt);
void	free_minirt(t_minirt *m);
void	*calloc_and_check(size_t memb_size, size_t nmemb, t_minirt *m, char *s);

#endif