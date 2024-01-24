NAME         := nm
CC           := gcc
SRCS_DIR     := srcs
OBJS_DIR     := .objs
INCS_DIR     := incs
MAIN         := srcs/main.c

CFLAGS :=                           \
    -Wall                           \
    -Wextra                         \
    -Werror                         \
    -pedantic 

# export ASAN_OPTIONS="log_path=sanitizer.log"
# export ASAN_OPTIONS="detect_leaks=1"

CFLAGS_DBG :=                       \
    -g3                             \
    -O0                             \
    -fsanitize=address              \
    -fsanitize=undefined            \
    -fno-omit-frame-pointer         \
    -fstack-protector-strong        \
    -fno-optimize-sibling-calls 

SRCS :=                                 \
    debug/print_flag.c                  \
    core/nm.c                           \
    core/handle_64.c                    \
    flag/manage_flag.c                  \
    utils/free_sym_list.c                  