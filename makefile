#directories
SOURCEDIR := src
LIBDIR := libs
BUILDDIR := build

#variables
APPNAME :=
DEBUG := -g
FLAGS := -Wall -fmax-errors=10 -Wshadow #-funroll-loops
LIBSTOCOMPILE :=
DEPENDENCIES :=
LIBS := -I$(LIBDIR)/stb_image -I$(LIBDIR)/glm -I$(LIBDIR)/glad/include -I$(LIBDIR)/SDL2/include -L$(LIBDIR)/SDL2/lib -lmingw32 -lSDL2main -lSDL2
THIRDPARTY :=
INCLUDES := -I$(SOURCEDIR)
ARGS :=
ECHO := @
PROGRESS := 1
DEFINES :=
STDVERSION := -std=c++17
INCLUDEFILESEXTENTIONS := hpp tpp inl
#needed for checking if makefile has changed
MAKEFILENAME := makefile

.DEFAULT_GOAL := compile



#compile all necessarily libs
ifeq (clean,$(filter clean,$(if $(MAKECMDGOALS),$(MAKECMDGOALS),$(.DEFAULT_GOAL))))
OUTPUTIGNORE := $(foreach lib,$(LIBSTOCOMPILE),$(info Cleaning $(lib)...) $(shell make clean ARGS=LIB -C "$(lib)"))
else
OUTPUTIGNORE := $(foreach lib,$(LIBSTOCOMPILE),$(info Compiling $(lib)...) $(shell make ARGS=LIB -C "$(lib)"))
endif

ifeq ($(ARGS),LIB)
PROGRESS := 0
endif

# Note. I use findutils from (clang compiler?) it is located in msys2/usr/bin

#find all folders in $(SOURCEDIR)
SOURCEFOLDERS := $(shell find $(SOURCEDIR) -type d)
#find all thirdparty files if directory is given
THIRDPARTY := $(foreach dir,$(THIRDPARTY),$(if $(wildcard $(dir)/.),$(foreach file,$(shell cd $(dir) && find -type f -name "*.o"),$(subst ./,$(dir)/,$(file))),$(dir)))
#replace $(SOURCEDIR) to $(BUILDDIR) to understand what build folders we need to have
BUILDFOLDERS := $(foreach folder,$(SOURCEFOLDERS),$(subst $(SOURCEDIR),$(BUILDDIR),$(folder)))
#create all necesarily build folders
$(foreach folder,$(BUILDFOLDERS),$(shell mkdir -p $(folder)))

#get all files we need to compile/link/include
SOURCES := $(foreach folder,$(SOURCEFOLDERS),$(wildcard $(folder)/*.cpp))
#first find all include files from source folders
#then find all dependencies if it is folder
INCLUDEFILES := $(foreach ext,$(INCLUDEFILESEXTENTIONS),$(foreach folder,$(SOURCEFOLDERS),$(wildcard $(folder)/*.$(ext)))) \
$(foreach dep,$(DEPENDENCIES),$(if $(wildcard $(dep)/.),$(foreach ext,$(INCLUDEFILESEXTENTIONS),$(shell find "$(dep)" -name "*.$(ext)")),$(dep)))
OBJS := $(foreach file,$(SOURCES),$(file:$(SOURCEDIR)/%.cpp=$(BUILDDIR)/%.o))
#preprocess $(DEFINES)
DEFIENS := $(foreach def,$(DEFINES),$(addprefix -D,$(def)))

all: compile
	$(ECHO)if [ $(PROGRESS) ]; then \
    echo Run!; \
  fi; \
	$(BUILDDIR)/$(APPNAME) $(ARGS)

precompileHeader: $(ARGS)
	$(ECHO)if [ $(PROGRESS) ]; then \
		echo Compiling $(notdir $(ARGS))...; \
	fi; \
	g++ $(DEBUG) $(ARGS) -c $(addsufix .gch,$(ARGS)) $(DEFIENS) $(FLAGS) $(STDVERSION) $(LIBS); \
	if [ $(PROGRESS) ]; then \
		echo Compiled!; \
	fi;

debug: compile
	gdb --args $(BUILDDIR)/$(APPNAME) $(ARGS)

ifneq ($(APPNAME),)
compile: $(OBJS) $(MAKEFILENAME)
	$(ECHO)if [ $(PROGRESS) ]; then \
		echo Compiling $(APPNAME); \
	fi; \
	g++ $(DEBUG) $(OBJS) $(THIRDPARTY) -o $(BUILDDIR)/$(APPNAME) $(DEFIENS) $(FLAGS) $(STDVERSION) $(INCLUDES) $(LIBS); \
	if [ $(PROGRESS) ]; then \
		echo Compiled!; \
	fi
else
compile: $(OBJS) $(MAKEFILENAME)
	$(ECHO)if [ $(PROGRESS) ]; then \
    echo Compiled!; \
  fi
endif

define generateRules
$(1:$(SOURCEDIR)/%.cpp=$(BUILDDIR)/%.o): $1 $(INCLUDEFILES) $(MAKEFILENAME)
	$(ECHO)if [ $(PROGRESS) ]; then \
    echo Compiling $(notdir $(1))...; \
  fi; \
	g++ $(DEBUG) -c $$< -o $$@ $(DEFIENS) $(FLAGS) $(STDVERSION) $(INCLUDES) $(LIBS) 

endef

$(foreach src,$(SOURCES),$(eval $(call generateRules,$(src))))

clean:
	$(ECHO)rm -r -f $(BUILDDIR)