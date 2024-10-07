NAME = ft_scop

CC = c++
CFLAGS = -Iinclude -I$(LOCAL_DIR)/include -Wall -g

LDFLAGS = -ldl

RM = rm -rf
SRCS = main.cpp \
       src/glad.c \
       src/Shader.cpp \
       include/stb_image.cpp \
       src/Camera.cpp \
	   src/callbacks.cpp \
	   src/Scene.cpp
	   
OBJS = $(SRCS:.cpp=.o)
OBJS := $(OBJS:.c=.o)

LOCAL_DIR = $(HOME)/local
GLFW_INC = $(LOCAL_DIR)/include/GLFW/glfw3.h

# Vérifier si GLFW est installé localement
ifeq ($(wildcard $(GLFW_INC)),)
GLFW_LOCAL_INSTALL = true
else
GLFW_LOCAL_INSTALL = false
endif

# Définir les chemins d'inclusion et de lien de GLFW
ifeq ($(GLFW_LOCAL_INSTALL), true)
GLFW_CFLAGS = -I$(LOCAL_DIR)/include
GLFW_LDFLAGS = -L$(LOCAL_DIR)/lib64 -lglfw


else
GLFW_CFLAGS = $(shell pkg-config --cflags glfw3)
GLFW_LDFLAGS = $(shell pkg-config --libs glfw3)
endif

# Cibles
all: glfw $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(GLFW_CFLAGS) $(OBJS) -o $(NAME) $(GLFW_LDFLAGS) $(LDFLAGS)
$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(GLFW_CFLAGS) $(GLFW_LDFLAGS) $(LDFLAGS) -o $(NAME)


%.o: %.cpp
	$(CC) $(CFLAGS) $(GLFW_CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(GLFW_CFLAGS) -c $< -o $@

glfw:
	@if [ "$(GLFW_LOCAL_INSTALL)" = "true" ]; then \
		echo "GLFW not found, installing locally..."; \
		git clone https://github.com/glfw/glfw.git && \
		cd glfw && \
		cmake -S . -B build -DCMAKE_INSTALL_PREFIX=$(LOCAL_DIR) && \
		cmake --build build && \
		cmake --install build && \
		rm -rf glfw; \
	else \
		echo "GLFW found, skipping installation."; \
	fi

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re glfw
