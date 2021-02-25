#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include "str_sample.h"

ssize_t ft_read(int fd, void *buf, size_t nbyte);
size_t	ft_strlen(const char *str);
size_t	ft_strcpy(const char *dest, const char *src);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_write(int fd, char *str, int len);
char	*ft_strdup(const char *s);
