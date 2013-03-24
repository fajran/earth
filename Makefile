CC := clang++
PKGS := glew libglfw
SRCDIR := src
BUILDDIR := build
CFLAGS := -Wall `pkg-config --cflags $(PKGS)`
LIBS := `pkg-config --libs $(PKGS)`
TARGET := earth

SRCEXT := cc
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
DEPS := $(OBJECTS:.o=.deps)

$(TARGET) : $(OBJECTS)
	@echo "Linking..."
	@$(CC) $^ -o $(TARGET) $(LIBS)

$(BUILDDIR)/%.o : $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo "CC $<"
	@$(CC) $(CFLAGS) -MD -MF $(@:.o=.deps) -c -o $@ $<

clean:
	@echo "Cleaning..."
	@$(RM) -r $(BUILDDIR) $(TARGET)

-include $(DEPS)
.PHONY: clean
