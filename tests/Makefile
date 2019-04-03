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
all: $(BINDIR)/population_test $(BINDIR)/statistique_test $(BINDIR)/jouer_un_tour_test

# Link
$(BINDIR)/jouer_un_tour_test: $(OBJDIR)/jouer_un_tour_test.o $(OBJDIR)/jouer_un_tour.o $(OBJDIR)/population.o
	@mkdir -p $(BINDIR)
	$(LINKER) $^ $(LFLAGS) -o $@
	@echo "Linking complete!"

$(BINDIR)/population_test: $(OBJDIR)/population_test.o $(OBJDIR)/population.o
	@mkdir -p $(BINDIR)
	$(LINKER) $^ $(LFLAGS) -o $@
	@echo "Linking complete!"

$(BINDIR)/statistique_test: $(OBJDIR)/statistique_test.o $(OBJDIR)/population.o $(OBJDIR)/statistique.o
	@mkdir -p $(BINDIR)
	$(LINKER) $^ $(LFLAGS) -o $@
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
	@$(rm) $(BINDIR)/population_test* $(BINDIR)/statistique_test*
	@echo "Executable removed!"