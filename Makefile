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

UNAME	:= $(shell uname)

SRC		:=	\
	main.c				\
	init_pile.c 		\
	display.c 			\
	move_rr.c 			\
	move_r.c 			\
	move_p.c 			\
	move_s.c 			\

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
ifeq ($(UNAME), Linux)
STDFLAG		?=	-std=gnu11
endif

ifeq ($(UNAME), Darwin)
STDFLAG		?=	-ansi
endif
WFLAGS		?=	-Wall -Wextra -Werror -pedantic
CFLAGS		=	$(WFLAGS) $(INCFLAG) $(STDFLAG)

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
all: $(NAME)

$(NAME):	$(OBJ) $(LIBFT_PATH)/$(LIBFT) $(LIBFT_PRTF_PATH)/$(LIBFT_PRTF)
	@ echo "$(OP_COLOR) building $(NAME)$(NO_COLOR)"
	@ $(LD) -o $(NAME) $(OBJ) $(LDFLAG)
	@ printf "$(DONE)$(OP_COLOR)$(NAME)$(NO_COLOR)\n"


$(OBJDIR)/%.o:	$(SRCDIR)/%.c | $(OBJDIR) $(DEPDIR)
	@ $(CC) -c $< $(CFLAGS) -o $@ \
		&& printf "$(DONE)	: $(COLOR)$<$(NO_COLOR)\n" \
		|| (printf "$(KO)	<-  $(COLOR)$<$(NO_COLOR)\n" ; false)
	@ $(DEPGEN) -c $< $(DEPFLAG) -MQ $@ \
			> $(subst $(SRCDIR), $(DEPDIR), $(<:.c=.d))

$(LIBFT_PATH)/$(LIBFT):
	@ $(MAKE) -C $(LIBFT_PATH) --no-print-directory

$(LIBFT_PRTF_PATH)/$(LIBFT_PRTF):
	@ $(MAKE) -C $(LIBFT_PRTF_PATH) --no-print-directory

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
	@touch $<
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
	@rm -rf $(OBJ) $(NAME)

#### LOCAL (Don't recompile lib) ####
lclean:
	@ rm -r $(BUILDDIR) 1> /dev/null 2> /dev/null \
		&& printf "$(OP_COLOR)[CLR]$(NO_COLOR)	: obj\n" \
		; (exit 0)

lfclean: lclean
	@ rm -Rf *.dSYM 1> /dev/null 2> /dev/null
	@ rm $(NAME) 1> /dev/null 2> /dev/null \
		&& printf "$(OP_COLOR)[CLR]$(NO_COLOR)	: $(NAME)\n" \
		; (exit 0)

lre: lfclean all

#### MANDATORY ####
clean: lclean
	@ $(MAKE) -C $(LIBFT_PATH) --no-print-directory clean
	@ $(MAKE) -C $(TESTDIR) --no-print-directory clean
	@ $(MAKE) -C $(LIBFT_PRTF_PATH) --no-print-directory clean

fclean:	lfclean
	@ $(MAKE) -C $(LIBFT_PATH) --no-print-directory fclean
	@ $(MAKE) -C $(LIBFT_PRTF_PATH) --no-print-directory fclean

re:		fclean all

fre: clear sclean all

exe: all
	./$(NAME)

val: all
	@ valgrind --leak-check=full --show-leak-kinds=all -v ./$(NAME)

save: fclean clear
	@ git add --all && git commit -m "make save" && git push


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
