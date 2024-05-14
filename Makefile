#Compiler and Linker
CC          := cc

#The Target Binary Program
TARGET      := fdf

#The Directories, Source, Includes, Objects, Binary and Resources
SRCDIR      := src
INCDIR      := inc
BUILDDIR    := build/obj
TARGETDIR   := build/bin
RESDIR      := res
SRCEXT      := c
OBJEXT      := o

#Flags, Libraries and Includes
CFLAGS      := -Wall -Werror -Wextra
LIB         := lib
LIBFT       := libft
LIBFT.A     := libft.a
MLX         := mlx_linux
MLX_L_FLAGS := -Llib/mlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
MLX_C_FLAGS := -I/usr/include -Ilib/mlx_linux -Ilib/libft -O3
DEBUG_FLAGS := -fsanitize=address -g


#---------------------------------------------------------------------------------
#DO NOT EDIT BELOW THIS LINE
#---------------------------------------------------------------------------------
SOURCES     := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS     := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))

#Default Make
all: directories mlx libft $(TARGET)

#Remake
re: fclean all

#Make the Directories
directories:
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(BUILDDIR)

#Clean only Objects
clean:
	@$(RM) -rf $(BUILDDIR)
	@$(MAKE) -C $(LIB)/$(LIBFT) clean

#Full Clean, Objects and Binaries
fclean: clean
	@$(RM) -rf $(TARGETDIR)
	@$(MAKE) -C $(LIB)/$(LIBFT) fclean

#libft
libft:
	@$(MAKE) -C $(LIB)/$(LIBFT) all

#configure mlx
mlx:
	cd $(LIB)/$(MLX) && ./configure

#Link
$(TARGET): $(OBJECTS)
	$(CC) $^ $(MLX_L_FLAGS) $(LIB)/$(LIBFT)/$(LIB)/$(LIBFT.A) -o  $(TARGETDIR)/$(TARGET) 

#Compile
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(MLX_C_FLAGS) -c -o $@ $<

#Non-File Targets
.PHONY: all re clean fclean lib
