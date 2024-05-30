#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
//#include "str_sample.h"

extern ssize_t	ft_read(int fd, void *buf, size_t nbyte);
extern size_t	ft_strlen(const char *str);
extern char	*ft_strcpy(const char *dest, const char *src);
extern int	ft_strcmp(const char *s1, const char *s2);
extern ssize_t	ft_write(int fd, const void *buf, size_t count); 
extern char	*ft_strdup(const char *s);
