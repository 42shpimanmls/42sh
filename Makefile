PROG_NAME = 42sh

COMPILER = clang -c
CFLAGS = -Wall -Wextra -Werror -g -I$(INCL_ROOT)
LINKER = clang

SRCS_ROOT = srcs
INCL_ROOT = includes
OBJS_ROOT = objs

SRCS_DIRS = $(shell find $(SRCS_ROOT) -type d)
OBJS_DIRS = $(patsubst $(SRCS_ROOT)%, $(OBJS_ROOT)%, $(SRCS_DIRS))

SRCS = $(shell find $(SRCS_ROOT) -type f)
OBJS = $(patsubst $(SRCS_ROOT)/%.c, $(OBJS_ROOT)/%.o, $(SRCS))

MAKE_OPTS = --no-print-directory -j9

all:
	@$(MAKE) $(PROG_NAME) $(MAKE_OPTS)

$(PROG_NAME): $(OBJS_DIRS) $(OBJS)
	@echo "LINK   " $@
	@$(LINKER) -o $@ $(OBJS)

$(OBJS_DIRS):
	@mkdir -p $@

$(OBJS_ROOT)/%.o: $(SRCS_ROOT)/%.c
	@echo "COMPILE" $(patsubst $(SRCS_ROOT)/%.c,%,$^)
	@$(COMPILER) -o $@ $(CFLAGS) -I$(dir $(patsubst $(SRCS_ROOT)%,$(INCL_ROOT)%,$<)) $^

clean:
	@rm -fr $(OBJS_ROOT)

fclean: clean
	@rm -f $(PROG_NAME)

re: fclean all

.PHONY: all clean fclean re
