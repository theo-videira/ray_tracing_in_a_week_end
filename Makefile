NAME			= ray_tracing

CXX				= clang++
CFLAGS			= -Wall -Wextra -Werror

SRCS_DIR		= srcs
SRCS_FILES		= ppm_example.cpp
SRCS			= $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))

INCS			= 

OBJS_DIR		= objs
OBJS_FILES		= $(SRCS_FILES:.cpp=.o)
OBJS			= $(addprefix $(OBJS_DIR)/, $(OBJS_FILES))

all: $(NAME)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp $(HEADERS) | $(OBJS_DIR)
	$(CXX) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CXX) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re