# Makefile Universal by Marc NGUYEN

# Compiler
CC ?= gcc
CFLAGS ?= -g -Wall -Wextra -lm -I .

# Linker
LINKER ?= $(CC)
LFLAGS ?= -Wall -I . -lm

# Project structure
SRCDIR ?= ../src
OBJDIR ?= obj
BINDIR ?= bin
TESTDIR ?= .

SOURCES := $(wildcard $(SRCDIR)/*.c)
SOURCES_TEST := $(wildcard $(TESTDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
INCLUDES_TEST := $(wildcard $(TESTDIR)/*.h)
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
OBJECTS_TEST := $(SOURCES_TEST:$(TESTDIR)/%.c=$(OBJDIR)/%.o)

# Cleaner
rm = rm -rf

# Make all
all: $(BINDIR)/population_tests

# Link
$(BINDIR)/population_tests: $(OBJDIR)/population_test.o $(SRCDIR)/population.o
	@mkdir -p $(BINDIR)
	$(LINKER) $(OBJDIR)/population_test.o $(SRCDIR)/population.o $(LFLAGS) -o $@
	@echo "Linking complete!"

# Compile
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

$(OBJECTS_TEST): $(OBJDIR)/%.o : $(TESTDIR)/%.c
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
	@echo "OBJECTS_TEST :"
	@echo "$(OBJECTS_TEST)"
	@echo "INCLUDES_TEST :"
	@echo "$(INCLUDES_TEST)"
	@echo "SOURCES_TEST :"
	@echo "$(SOURCES_TEST)"

.PHONY: clean
clean:
	@$(rm) $(OBJDIR)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"