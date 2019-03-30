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
OBJDIR ?= obj
BINDIR ?= bin

# Get all files based on project structure
SOURCES := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Cleaner
rm = rm -rf

# Juste pour le raccourci : make clean all
all: $(BINDIR)/$(TARGET)

# Link
$(BINDIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(LINKER) $^ $(LFLAGS) -o $@
	@echo "Linking complete!"

# Compile
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
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

.PHONY: clean
clean:
	@$(rm) $(OBJDIR)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"