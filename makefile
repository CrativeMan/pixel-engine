CC = g++
CFLAGS = -Wall -Wextra -pedantic -Wno-type-limits
LDFLAGS = -lglfw -lGL -lGLEW -lglm -lm -limgui

SRCDIR = src
ENGINE_SRCDIR = $(SRCDIR)/engine
ENGINE_HEADERDIR = $(ENGINE_SRCDIR)/header
OBJDIR = obj
TARGETDIR = bin

ENGINE_SOURCES = $(shell find $(ENGINE_SRCDIR) -name '*.cpp')
ENGINE_OBJECTS = $(patsubst $(ENGINE_SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(ENGINE_SOURCES))
ENGINE_TARGET = $(TARGETDIR)/engine

all: $(ENGINE_TARGET)

new: clean all

engine: $(ENGINE_TARGET)

# target building
$(ENGINE_TARGET): $(ENGINE_OBJECTS) | $(TARGETDIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# object building
$(OBJDIR)/%.o: $(ENGINE_SRCDIR)/%.cpp | $(OBJDIR) $(OBJDIR)/subdirs
	$(CC) $(CFLAGS) -I$(ENGINE_HEADERDIR) -c $< -o $@

# directories
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/subdirs:
	mkdir -p $(OBJDIR) $(patsubst $(ENGINE_SRCDIR)/%, $(OBJDIR)/%, $(shell find $(ENGINE_SRCDIR) -type d))


$(TARGETDIR):
	mkdir -p $(TARGETDIR)

clean:
	rm -rf $(OBJDIR)
	rm -rf $(TARGETDIR)

count:
	cloc --exclude-list-file=.clocignore .

run:
	./bin/engine

.phony: all new engine clean count run
