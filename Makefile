NAME = ft_scop

CC = clang++

LDFLAGS = -g -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi
CFLAGS = -std=c++17 -O2 -g
RM = rm -rf
SRCS = 	newmain.cpp\
		srcs/Window.cpp\
srcs/App.cpp\
srcs/Device.cpp\
srcs/Renderer.cpp\
srcs/Renderer/SwapChain.cpp\
srcs/Utils.cpp

OBJS = $(SRCS:.cpp=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
