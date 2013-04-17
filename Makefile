CXX ?= clang++
PKGS := glew libglfw
SRCDIR := src
BUILDDIR := build
CFLAGS := -Wall -std=c++0x $(shell pkg-config --cflags $(PKGS))
LIBS := -lm $(shell pkg-config --libs $(PKGS))
TARGET := earth

SRCEXT := cc
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
DEPS := $(OBJECTS:.o=.deps)

all : $(TARGET)

$(TARGET) : $(OBJECTS)
	@echo "Linking..."
	@$(CXX) $^ -o $(TARGET) $(LIBS)

$(BUILDDIR)/%.o : $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo "CC $<"
	@$(CXX) $(CFLAGS) -MD -MF $(@:.o=.deps) -c -o $@ $<

clean:
	@echo "Cleaning..."
	@$(RM) -r $(BUILDDIR) $(TARGET)

-include $(DEPS)
.PHONY: all clean

