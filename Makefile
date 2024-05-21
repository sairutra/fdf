include sources.mk

#Compiler and Linker
CC          := cc

#The Target Binary Program
TARGET      := fdf

#The Directories, Source, Includes, Objects, Binary and Resources
SRCDIR      := src
INCDIR      := inc
OBJDIR      := build/obj
TARGETDIR   := build/bin
BUILDIR     := build
RESDIR      := res
SRCEXT      := c
OBJEXT      := o

#Flags, Libraries and Includes
CFLAGS      := -Wall -Werror -Wextra
LIB         := lib
LIBFT       := libft
LIBFT.A     := libft.a
MLX         := mlx_linux
MLX.A       := libmlx.a
MLX_L_FLAGS := -Llib/mlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
MLX_C_FLAGS := -I/usr/include -Ilib/mlx_linux -Ilib/libft -O3
DEBUG_FLAGS := -fsanitize=address -g


#---------------------------------------------------------------------------------
#DO NOT EDIT BELOW THIS LINE
#---------------------------------------------------------------------------------
OBJECTS     := $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))

#Default Make

all: build $(LIB)/$(MLX)/$(MLX.A) $(LIB)/$(LIBFT)/$(LIB)/$(LIBFT.A) $(TARGETDIR)/$(TARGET) 

#Remake
re: fclean all

#Make the Directories
build:
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(OBJDIR)

#Clean only Objects
clean:
	@$(RM) -rf $(OBJDIR)
	@$(MAKE) -C $(LIB)/$(LIBFT) clean
	@$(MAKE) -C $(LIB)/$(MLX) clean

#Full Clean, Objects and Binaries
fclean: clean
	@$(RM) -rf $(BUILDIR)
	@$(MAKE) -C $(LIB)/$(LIBFT) fclean
	@$(MAKE) -C $(LIB)/$(MLX) clean

#libft
$(LIB)/$(LIBFT)/$(LIB)/$(LIBFT.A):
	@$(MAKE) -C $(LIB)/$(LIBFT) all

#configure mlx
$(LIB)/$(MLX)/$(MLX.A):
	cd $(LIB)/$(MLX) && ./configure

#Link
$(TARGETDIR)/$(TARGET) : $(OBJECTS)
	$(CC) $(OBJECTS) $(MLX_L_FLAGS) $(LIB)/$(LIBFT)/$(LIB)/$(LIBFT.A) -o  $(TARGETDIR)/$(TARGET) 

#Compile
$(OBJDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(MLX_C_FLAGS) -c -o $@ $^


#Non-File Targets
.PHONY: all re clean fclean lib
