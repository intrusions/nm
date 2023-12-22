include nm.mk

SRCS_OBJS := $(patsubst %.c,$(OBJS_DIR)/%.o,$(SRCS))

$(OBJS_DIR)/%.o:$(SRCS_DIR)/%.c
	@mkdir -vp $(dir $@)
	$(CC) \
		$(CFLAGS) \
		-MMD \
		-MP \
		-o $@ \
		-c $< \
		-I $(INCS_DIR)

all: $(NAME)

-include  $(SRCS_OBJS:.o=.d)

$(NAME): $(SRCS_OBJS)
	@$(CC) \
		$^ \
		$(MAIN) \
		$(CFLAGS) \
		-o $(NAME) \
		-I $(INCS_DIR)

g: CFLAGS += $(CFLAGS_DBG)
g: all

clean:
	rm -rf *.dSYM
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY	: all clean g fclean re 