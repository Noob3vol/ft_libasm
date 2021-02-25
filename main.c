#include "test.h"
#define TEST_FILE "Test_file.txt"

typedef	struct	s_ret_write
{
	int		ret;
	int		ft_ret;
	int		errnum;
	int		ft_errnum;
	char	*str;
}				t_ret_wr;


typedef	struct	s_ret_read
{
	int		ret;
	int		ft_ret;
	int		errnum;
	int		ft_errnum;
	char	*buff;
	char	*ft_buff;
}				t_ret_rd;


/*
** We return 42 on NULL pointer to trigger error for function write and read
** We will skip them for other function as it is suppose to crash and i don't
** have time to implement bash script + multiple binary to check if your
** program crash like original does
*/

size_t		ft_strlen(const char *str)
{
	int i;

	if (!str)
		return (42);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		open_output_file(void)
{
	int fd;

	fd = open(TEST_FILE, O_CREAT|O_TRUNC);
	return (fd);
}

/*
**	structure to stock information concerning the syscall ft (read, write)
**	we stock 
*/

#define	RD_ERROR_RET				1
#define	RD_ERROR_ERRNUM				2
#define	RD_ERROR_CONTENT			4
#define	WR_ERROR_RET				8
#define	WR_ERROR_ERRNUM				16
#define	WR_ERROR_CONTENT			32

typedef	struct	s_error_fmt
{
	int		id;
	char	*msg;
}				t_error_fmt;

t_error_fmt		error_rd_tab[4] =
{
	{RD_ERROR_RET, "Bad return : is %d, should be %d\n"},
	{RD_ERROR_ERRNUM, "Bad Errnum : is %d, should be %d\n"},
	{RD_ERROR_CONTENT, "Bad Content : is \"%s\", should be \"%s\"\n"},
	{0, NULL}
};

t_error_fmt		error_wr_tab[4] =
{
	{WR_ERROR_RET, "Bad return : is %d, should be %d\n"},
	{WR_ERROR_ERRNUM, "Bad Errnum : is %d, should be %d\n"},
	{WR_ERROR_CONTENT, "Bad Content : is \"%s\" should be \"%s\"\n"},
	{0, NULL}
};

void		ft_print_rd_error(int errmask, t_ret_rd *rd_ret)
{
	int			i;

	printf("Error Read\n");
	i = 0;
	while (error_rd_tab[i].id <= RD_ERROR_CONTENT)
	{
		if (errmask & error_rd_tab[i].id)
		{
			if (error_rd_tab[i].id == RD_ERROR_CONTENT)
				printf(error_rd_tab[i].msg, rd_ret->ft_buff, rd_ret->buff);
			else
				printf(error_rd_tab[i].msg, *((int *)rd_ret + i)
						, *((int *)rd_ret + i + 1));
		}
		i++;
	}
}

void		ft_print_wr_error(int errmask, t_ret_wr *wr_ret, t_ret_rd *rd_ret)
{
	int i;

	i = 0;
	printf("Error Write\n");
	while (error_wr_tab[i].id)
	{
		if (errmask & error_wr_tab[i].id)
		{
			if (error_wr_tab[i].id == WR_ERROR_CONTENT)
				printf(error_wr_tab[i].msg, rd_ret->buff, wr_ret->str);
			else
				printf(error_wr_tab[i].msg, *((int *)wr_ret + i)
						, *((int *)wr_ret + i + 1));
		}
		i++;
	}
}

void		ft_print_rdwr_resutl(int errmsk, t_ret_wr *wr_ret, t_ret_rd *rd_ret)
{
	int			i;

	i = 0;
	if (errmsk & 56)
		ft_print_wr_error(errmsk, wr_ret, rd_ret);
	else
		printf("Write ok\n");
	if (errmsk & 7)
		ft_print_rd_error(errmsk, rd_ret);
	else
		printf("Read ok\n");
}

int			ft_check_rd_wr(t_ret_wr *wr_ret, t_ret_rd *rd_ret)
{
	int	error_mask;

	error_mask = 0;
	if (wr_ret->ret != wr_ret->ft_ret)
		error_mask |= WR_ERROR_RET;
	if (wr_ret->errnum != wr_ret->ft_errnum)
		error_mask |= WR_ERROR_ERRNUM;
	if (strcmp(wr_ret->str, rd_ret->buff))
		error_mask |= WR_ERROR_CONTENT;
	if (rd_ret->ret != rd_ret->ft_ret)
		error_mask |= RD_ERROR_RET;
	if (rd_ret->errnum != rd_ret->ft_errnum)
		error_mask |= RD_ERROR_ERRNUM;
	if (strcmp(rd_ret->buff, rd_ret->ft_buff))
		error_mask |= RD_ERROR_CONTENT;
	ft_print_rdwr_resutl(error_mask, wr_ret, rd_ret);
	free(wr_ret);
	free(rd_ret->buff);
	free(rd_ret->ft_buff);
	return (error_mask);
}

#define FD_ERROR_FLAG	1
#define FD_FILE_FLAG	2

t_ret_wr	*write_unitest(int test_type, int str_i)
{
	t_ret_wr	*new;
	int			fd;

	fd = 1;
	new = (t_ret_wr *)malloc(sizeof(t_ret_wr));
	new->str = strdup(str_index[str_i].str);
	if (test_type & FD_ERROR_FLAG)
		fd = -1;
	if (test_type & FD_FILE_FLAG)
		fd = open(TEST_FILE, O_CREAT|O_TRUNC|O_RDWR, 0666);
	new->ret = write(fd, new->str, ft_strlen(new->str));
	new->errnum = errno;
	if (test_type & FD_FILE_FLAG)
		close(fd);
	if (test_type & FD_FILE_FLAG)
		fd = open(TEST_FILE, O_CREAT|O_TRUNC|O_RDWR, 0666);
	new->ft_ret = ft_write(fd, new->str, ft_strlen(new->str));
	new->ft_errnum = errno;
	if (test_type & FD_FILE_FLAG)
		close(fd);
	return (new);
}

t_ret_rd	*read_unitest(int fd_type, int str_i)
{
	t_ret_rd	*new;
	int			fd;
	int			str_len;

	new = (t_ret_rd *)malloc(sizeof(t_ret_rd));
	str_len = ft_strlen(str_index[str_i].str);
	fd = 1;
	if (fd_type & FD_ERROR_FLAG)
		fd = -1;
	if (fd_type & FD_FILE_FLAG)
		fd = open(TEST_FILE, O_RDONLY);
	new->buff = (char *)malloc(sizeof(char) * (str_len + 1));
	new->ft_buff = (char *)malloc(sizeof(char) * (str_len + 1));
	new->buff[str_len] = 0;
	new->ft_buff[str_len] = 0;
	new->ret = read(fd, new->buff, str_len);
	new->errnum = errno;
	if (fd_type & FD_FILE_FLAG)
		close(fd);
	if (fd_type & FD_FILE_FLAG)
		fd = open(TEST_FILE, O_RDONLY);
	new->ft_ret = ft_read(fd, new->ft_buff, str_len);
	new->ft_errnum = errno;
	if (fd_type & FD_FILE_FLAG)
		close(fd);
	return (new);
}

/*
**	write and read test are perfomed together because we need read call to check
**	that write function operate correctly
*/

void	write_read_test(void)
{
	t_ret_wr	*wr_ret;
	t_ret_rd	*rd_ret;
	int				i;
	int				fd_type;

	i = 0;
	fd_type = FD_FILE_FLAG;
	while (i < NB_STR)
	{
		printf("Testing with str = \"%s\"\n", str_index[i].str);
		printf("-----------------------------------------------------\n");
		wr_ret = write_unitest(fd_type, i);
		rd_ret = read_unitest(fd_type, i);
		ft_check_rd_wr(wr_ret, rd_ret);
		printf("=====================================================\n");
		i++;
	}
}

int		main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	write_read_test();
	return (0);
}
