# Makefile Universal by Marc NGUYEN
# Project Name
TARGET ?= $(shell basename $(CURDIR))

# Compiler
CC ?= gcc
CFLAGS ?= -g -Wall -Wextra -lm -I .

# Linker
LINKER ?= $(CC)
LFLAGS ?= -Wall -I . -lm

# Project structure
SRCDIR ?= src
LIBDIR ?= lib
OBJDIR ?= obj
BINDIR ?= bin

# Get all files based on project structure
SOURCES := $(wildcard $(SRCDIR)/*.c)
SOURCES_LIB := $(wildcard $(LIBDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
INCLUDES_LIB := $(wildcard $(LIBDIR)/*.h)
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
OBJECTS_LIB := $(SOURCES_LIB:$(LIBDIR)/%.c=$(OBJDIR)/%.o)

# Cleaner
rm = rm -rf

# Link
$(BINDIR)/$(TARGET): $(OBJECTS) $(OBJECTS_LIB)
	@mkdir -p $(BINDIR)
	$(LINKER) $(OBJECTS) $(OBJECTS_LIB) $(LFLAGS) -o $@
	@echo "Linking complete!"


# Compile
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

$(OBJECTS_LIB): $(OBJDIR)/%.o : $(LIBDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: echoes
echoes:
	@echo "OBJECTS :"
	@echo "$(OBJECTS)"
	@echo "INCLUDES :"
	@echo "$(INCLUDES)"
	@echo "SOURCES :"
	@echo "$(SOURCES)"
	@echo "OBJECTS_LIB :"
	@echo "$(OBJECTS_LIB)"
	@echo "INCLUDES_LIB :"
	@echo "$(INCLUDES_LIB)"
	@echo "SOURCES_LIB :"
	@echo "$(SOURCES_LIB)"

.PHONY: clean
clean:
	@$(rm) $(OBJDIR)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"