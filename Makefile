NAME = ft_scop

CC = c++
CFLAGS = -Iinclude -Wall -lglfw -ldl -g
RM = rm -rf
SRCS = main.cpp \
       src/glad.c \
	   src/Shader.cpp \
	   include/stb_image.cpp
OBJS = $(SRCS:.cpp=.o)
OBJS := $(OBJS:.c=.o)

all: $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
