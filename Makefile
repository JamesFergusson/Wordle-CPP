# Desktop
CC  := g++ 
CFLAGS := -std=c++20
LIBS := 


# dirs

SRCDIR := Code
OBJDIR := Objects
BINDIR := .


# files
FILES_wordle =  wordle_funcs
OBJFILES_wordle = $(CFILES_wordle:%=%.o)

PROGRAMS = wordle
wordle = wordle_main

# rules

all : $(PROGRAMS)

wordle: $(FILES_wordle:%=$(OBJDIR)/%.o) $(wordle:%=$(OBJDIR)/%.o)
	$(CC) $(CFLAGS) -I$(SRCDIR) $^ -o $(BINDIR)/$@ $(LIBS) $(LIBSMPI)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -I$(SRCDIR) -c $< -o $@ 

$(OBJDIR)/%.o: $(SRCDIR)/%.h

clean:
	rm -f $(OBJDIR)/*.o $(PROGRAMS)
