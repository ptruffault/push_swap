# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ptruffau <ptruffau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/16 11:16:13 by ptruffau          #+#    #+#              #
#                                                      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= checker

NAME2	= push_swap


SRC		:=	\
	main_checker.c					\
	setup/init_pile.c 				\
	setup/init_tools.c 				\
	moves/move_rr.c 				\
	moves/move_r.c 					\
	moves/move_p.c 					\
	moves/move_s.c 					\
	moves/instruction_handler.c 	\
	piles/check_sort.c 				\
	piles/pile_tools.c 				\
	piles/display.c 				\

SRC2		:=	\
	main_push_swap.c 	\
	setup/init_pile.c 				\
	setup/init_tools.c 				\
	moves/move_rr.c 				\
	moves/move_r.c 					\
	moves/move_p.c 					\
	moves/move_s.c 					\
	moves/instruction_handler.c 	\
	piles/check_sort.c 				\
	piles/pile_tools.c 				\
	piles/display.c 				\
	piles/sort_tools.c 				\

SRCDIR	:=	srcs
INCDIR	:=	includes
LIBDIR	:=	lib

BUILDDIR	:=	bin
OBJDIR		:=	$(BUILDDIR)/obj
DBGDIR		:=	$(BUILDDIR)/debug
DEPDIR		:=	$(BUILDDIR)/dep

# Libft
LIBFT		:=	libft.a
LIBFT_PATH	:= $(LIBDIR)/libft
LIB_LINK	+= -L $(LIBFT_PATH) -l ft
LIB_INC		+= -I $(LIBFT_PATH)/includes

#### COMPILER ####
CC			?=	cc

INCFLAG		:=	-I $(INCDIR) $(LIB_INC)
 
WFLAGS		?=	-Wall -Wextra -Werror -pedantic -g
CFLAGS		=	$(WFLAGS) $(INCFLAG) 

DEPGEN		:=	$(CC)
DEPFLAG		:=	-MM $(INCFLAG)

LD			:=	$(CC)
LDFLAG		=	$(LIB_LINK) -ltermcap
LDFLAG		+=	-Wno-unused-command-line-argument $(WFLAGS)

#############################
#    MAKEFILE VARIABLES     #
#############################
#### FILE STRUCTURE ####
# *LOCA is the list of all subdirectory in a directory
SRCLOCA	:=	$(shell find $(SRCDIR) -type d)
OBJLOCA	:=	$(subst $(SRCDIR), $(OBJDIR), $(SRCLOCA))
DBGLOCA	:=	$(subst $(SRCDIR), $(DBGDIR), $(SRCLOCA))
DEPLOCA	:=	$(subst $(SRCDIR), $(DEPDIR), $(SRCLOCA))

OBJ		:=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))
OBJ2	:=	$(addprefix $(OBJDIR)/, $(SRC2:.c=.o))
DBG		:=	$(addprefix $(DBGDIR)/, $(SRC:.c=.o))
DEP		:=	$(addprefix $(DEPDIR)/, $(SRC:.c=.d))
SRC		:=	$(addprefix $(SRCDIR)/, $(SRC))

COLOR		= 		\033[01;34m
NO_COLOR	= 		\033[00m
OP_COLOR	= 		\033[1;31m
DONE 		= 		$(NO_COLOR)[\033[1;32mOK$(NO_COLOR)]
KO			= 		$(NO_COLOR)[\033[00;31mKO$(NO_COLOR)]


#############################
#           RULES           #
#############################
#### COMPILE ####
all: $(NAME) $(NAME2)

$(NAME):	$(OBJ) $(LIBFT_PATH)/$(LIBFT)
	@ echo "$(OP_COLOR) building $(NAME)$(NO_COLOR)"
	@ $(LD) -o $(NAME) $(OBJ) $(LDFLAG)
	@ printf "$(DONE)$(OP_COLOR)$(NAME)$(NO_COLOR)\n"

$(NAME2): 	$(OBJ2) $(LIBFT_PATH)/$(LIBFT)
	@ echo "$(OP_COLOR) building $(NAME2)$(NO_COLOR)"
	@ $(LD) -o $(NAME2) $(OBJ2) $(LDFLAG)
	@ printf "$(DONE)$(OP_COLOR)$(NAME2)$(NO_COLOR)\n"


$(OBJDIR)/%.o:	$(SRCDIR)/%.c | $(OBJDIR) $(DEPDIR)
	@ $(CC) -c $< $(CFLAGS) -o $@ \
		&& printf "$(DONE)	: $(COLOR)$<$(NO_COLOR)\n" \
		|| (printf "$(KO)	<-  $(COLOR)$<$(NO_COLOR)\n" ; false)
	@ $(DEPGEN) -c $< $(DEPFLAG) -MQ $@ \
			> $(subst $(SRCDIR), $(DEPDIR), $(<:.c=.d))

$(LIBFT_PATH)/$(LIBFT):
	@ $(MAKE) -C $(LIBFT_PATH) --no-print-directory

# Dir created to store build cache
$(OBJDIR):
	@ mkdir -p $(OBJLOCA)
$(DBGDIR):
	@ mkdir -p $(DBGLOCA)
$(DEPDIR):
	@ mkdir -p $(DEPLOCA)
$(BUILDDIR):
	@ mkdir -p $(BUILDDIR)


# Recompile with as much warning as possible
warn:	WFLAGS := -Wall -Wextra -ansi -Wpedantic -Wno-vla
warn:	WFLAGS += -Wstrict-prototypes -Wunreachable-code  -Wwrite-strings
warn:	WFLAGS += -Wpointer-arith -Wbad-function-cast -Wcast-align -Wcast-qual
CLANG_INSTALLED	:= $(shell which clang > /dev/null 2> /dev/null && echo yes)
# If clang is installed also add this exclusive warning
ifdef CLANG_INSTALLED
warn:	CC := clang
warn:	WFLAGS += -Weverything -Wno-padded -Wno-missing-noreturn
endif
warn:	lre

#### DEBUGING ####
$(DBGDIR)/%.o:		$(SRCDIR)/%.c | $(DBGDIR) $(DEPDIR)
	@printf "$(COLOR)$<$(NO_COLOR) -> "
	@ $(CC) -c $< $(CFLAGS) -o  $@ && printf "$(DONE)\n" || printf "$(KO)\n"
	@ $(DEPGEN) -c $< $(DEPFLAG) -MQ $@ \
		> $(subst $(SRCDIR), $(DEPDIR), $(<:.c=.d))

debug:	WFLAGS		:= -g
debug:	$(DBG) | $(LIBFT_PATH)/$(LIBFT) $(LIBFT_PRTF_PATH)/$(LIBFT_PRTF)
	@echo "$(OP_COLOR) building $(NAME)$(NO_COLOR)"
	@$ $(LD) -o $(NAME) $(DBG) $(LDFLAG)
	@printf "$(DONE)$(OP_COLOR)$(NAME)$(NO_COLOR)  \n"

debugclean:
	@ rm -r $(DBGDIR) 1> /dev/null 2> /dev/null \
		&& printf "$(OP_COLOR)[CLR]$(NO_COLOR)"	:" debug obj" \
		; (exit 0)

rdebug: debugclean debug

clear:
	@clear

sclean:
	@rm -rf $(OBJ) $(OBJ2) $(NAME) $(NAME2)

#### LOCAL (Don't recompile lib) ####
lclean:
	@ rm -r $(BUILDDIR) 1> /dev/null 2> /dev/null \
		&& printf "$(OP_COLOR)[CLR]$(NO_COLOR)	: obj\n" \
		; (exit 0)

lfclean: lclean
	@ rm -Rf *.dSYM 1> /dev/null 2> /dev/null
	@ rm $(NAME) $(NAME2) 1> /dev/null 2> /dev/null \
		&& printf "$(OP_COLOR)[CLR]$(NO_COLOR)	: $(NAME)\n" \
		; (exit 0)

lre: lfclean all

#### MANDATORY ####
clean: lclean
	@ $(MAKE) -C $(LIBFT_PATH) --no-print-directory clean
	@ $(MAKE) -C $(TESTDIR) --no-print-directory clean
	@ $(MAKE) -C $(LIBFT_PRTF_PATH) --no-print-directory clean

fclean:	lfclean
	@ $(MAKE) -C $(LIBFT_PATH) fclean

re:		fclean all

fre: clear sclean all

exe: all
	./$(NAME)

val: all
	@ valgrind --leak-check=full --show-leak-kinds=all -v ./$(NAME)

save: fclean clear
	@ git add --all && git commit -m "make save" && git push

test: all
	@echo "SAVED:"
	@cat test/saved
	@echo "\nLAST:"
	@cat test/last
	@echo "PERF:"
	@sh test/moyenne.sh


build:
	@mkdir $(BUILDDIR) $(OBJDIR) $(DBGDIR) $(DEPDIR) $(SRCDIR) $(INCDIR) $(LIBDIR)
	@echo ptruffau > auteur
	@echo "#include \"$(NAME).h\"\n\
\n\
int main(int argc, char **argv)\n\
{\n\
\t(void)argc;\n\
\t(void)argv;\n\
\treturn (0);\n\
}\n\
" > $(SRCDIR)/main.c
	@echo "#ifndef\n\
# define\n\
\
#endif" >  includes/$(NAME).h
	@git clone https://github.com/ptruffault/libft.git lib/libft

#############################
#          SETTING          #
#############################
# Add rule to phony if they are not based on actual files.
.PHONY: all re build
.PHONY: debug rdebug debugclean
.PHONY: warn
.PHONY: lclean lfclean lre val exe fre
.PHONY: clear sclean clean fclean save
.PHONY: save val exe fre

#############################
#         DEPENDENCY        #
#############################
# Include all custom dependency rules created in .d's
# the '-' prevent error in case of non existing files
-include $(DEP)
