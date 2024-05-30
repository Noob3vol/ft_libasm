NAME=libasm.a
ASM=nasm
ASM_FLAG= -felf64 -g
CC=clang
CC_FLAGS= -g3

#test file
MAIN=main.c

HDR_NAME=test.h\
str_sample.h

HDR_DIR=include/

HDRS=$(addprefix $(HDR_DIR), $(HDR_NAME))

TEST=test


SRC = ft_strlen.s\
 ft_read.s\
 ft_strdup.s\
 ft_strcmp.s\
 ft_write.s\
 ft_strcpy.s

BONUS = ft_atoi_base.s

ifdef BONUS_FLAG
SRC_NAME= $(SRC)\
			 $(BONUS)
else
SRC_NAME= $(SRC)
endif


SRC_DIR= ./srcs/
OBJ_DIR= ./objs/


SRCS= $(addprefix $(SRC_DIR), $(SRC_NAME))
OBJS= $(addprefix $(OBJ_DIR), $(SRC_NAME:.s=.o))

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
	ranlib $(NAME)

$(OBJ_DIR): 
	mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.s
	$(ASM) $(ASM_FLAG) -o $@ $<

$(TEST) : $(NAME) $(MAIN) $(HDRS)
	$(CC) $(CC_FLAGS) -I$(HDR_DIR) -o $(TEST) $(MAIN) $(NAME) 

bonus:
	make BONUS_FLAG=1
re_bonus:
	make BONUS_FLAG=1 re

clean:
	rm -f $(OBJS) $(BONUS)

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST)

re: clean fclean all

re_test : re test

.PHONY: all clean fclean re
