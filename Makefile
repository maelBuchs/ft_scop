NAME = ft_scop

CC = clang++

# FLAGS CLASSIQUES
CFLAGS = -std=c++17 -O2 -g
LDFLAGS = -g -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

# FLAGS DEBUG (ASan)
DEBUG_CFLAGS = -std=c++17 -O0 -g -fsanitize=address -fno-omit-frame-pointer
DEBUG_LDFLAGS = -fsanitize=address -g -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

RM = rm -rf

SRCS = 	newmain.cpp\
		srcs/Window.cpp\
		srcs/App.cpp\
		srcs/Device.cpp\
		srcs/Renderer.cpp\
		srcs/Renderer/SwapChain.cpp\
		srcs/Renderer/Pipeline.cpp\
		srcs/Renderer/CommandManager.cpp\
		srcs/Renderer/BufferManager.cpp\
		srcs/Renderer/DescriptorManager.cpp\
		srcs/Renderer/SyncObjects.cpp\
		srcs/AppLoop.cpp\
		srcs/Utils.cpp

OBJS = $(SRCS:.cpp=.o)
DEBUG_OBJS = $(SRCS:.cpp=.debug.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

%.debug.o: %.cpp
	$(CC) $(DEBUG_CFLAGS) -c $< -o $@

debug: $(DEBUG_OBJS)
	$(CC) $(DEBUG_CFLAGS) $(DEBUG_LDFLAGS) $(DEBUG_OBJS) -o $(NAME)_debug

clean:
	$(RM) $(OBJS) $(DEBUG_OBJS)

fclean: clean
	$(RM) $(NAME) $(NAME)_debug

re: fclean all

.PHONY: all clean fclean re debug
