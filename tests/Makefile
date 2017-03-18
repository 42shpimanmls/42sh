CUNIT_VER ?= $(shell pwd)/CUnit-2.1-3
CUNIT_SRC_ARCHIVE ?= $(CUNIT_VER).tar.bz2
CUINT_LOCAL_DIR ?= $(CUNIT_VER)/install
CUNIT_STATIC_LIB ?= $(CUINT_LOCAL_DIR)/lib/libcunit.a
CUNIT_INCLUDE_ROOT ?= $(CUINT_LOCAL_DIR)/include
CFLAGS = -Wall -Wextra -Werror -I$(CUNIT_INCLUDE_ROOT)
CC ?= clang
COMPILER = $(CC) -c
LINKER = $(CC)

PROG_NAME = 42sh_unit_tests

SRCS_ROOT = srcs
INCL_ROOT = includes
OBJS_ROOT = objs

SRCS_DIRS = $(shell find $(SRCS_ROOT) -type d)
OBJS_DIRS = $(patsubst $(SRCS_ROOT)%, $(OBJS_ROOT)%, $(SRCS_DIRS))

SRCS = $(filter %.c,$(shell find $(SRCS_ROOT) -type f))
OBJS = $(patsubst $(SRCS_ROOT)/%.c, $(OBJS_ROOT)/%.o, $(SRCS))

MAKE_OPTS 			= --no-print-directory

all: $(CUNIT_STATIC_LIB)
	@echo "BUILDING TESTS:"
	@$(MAKE) $(PROG_NAME) $(MAKE_OPTS)
	@echo "RUNNING TESTS:"
	@./$(PROG_NAME)

$(CUNIT_STATIC_LIB):
	@echo "BUILDING CUNIT:"
	tar -xf $(CUNIT_SRC_ARCHIVE)
	#cd $(CUNIT_VER) && aclocal
	cd $(CUNIT_VER) && autoconf
	cd $(CUNIT_VER) && autoreconf -i
	#cd $(CUNIT_VER) && automake
	cd $(CUNIT_VER) && ./configure --prefix $(CUNIT_VER)/install
	make -C $(CUNIT_VER)
	make install -C $(CUNIT_VER)


$(PROG_NAME): $(OBJS_DIRS) $(OBJS) $(CUNIT_STATIC_LIB)
	@echo "LINK   " $@
	@$(LINKER) -o $@ $(OBJS) $(CUNIT_STATIC_LIB)

$(OBJS_DIRS):
	@mkdir -p $@

$(OBJS_ROOT)/%.o: $(SRCS_ROOT)/%.c
	@echo "COMPILE" $(patsubst $(SRCS_ROOT)/%.c,%,$^)
	@$(COMPILER) -o $@ $(CFLAGS) -I$(dir $(patsubst $(SRCS_ROOT)%,$(INCL_ROOT)%,$<)) $<

clean:
	@rm -fr $(OBJS_ROOT)
	@rm -fr $(CUNIT_VER)

fclean: clean
	@rm -f $(PROG_NAME)

re: fclean all
