#directories
SOURCEDIR := src
LIBDIR := libs
BUILDDIR := build

#variables
APPNAME := main.exe
DEBUG := -g
FLAGS := -Wall -fmax-errors=10 -Wshadow #-Wl,-subsystem,console
LIBS :=  -Iglm -Iglad/include -ISDL2/include -LSDL2/lib -lmingw32 -lSDL2main -lSDL2
THIRDPARTY := glad/src/glad.o
ARGS :=
ECHO := @
PROGRESS := 1
DEFINES := DEBUG
STDVERSION := -std=c++17
INCLUDEFILESEXTENTIONS := hpp tpp inl
INCLUDEEVERYFOLDER := 
#needed for checking if makefile has changed
MAKEFILENAME := makefile

#find all folders in $(SOURCEDIR)
SOURCEFOLDERS := $(shell find $(SOURCEDIR) -type d)
#replace $(SOURCEDIR) to $(BUILDDIR) to understand what build folders we need to have
BUILDFOLDERS := $(foreach folder,$(SOURCEFOLDERS),$(subst $(SOURCEDIR),$(BUILDDIR),$(folder)))
#create all necesarily folders
$(foreach folder,$(BUILDFOLDERS),$(shell mkdir -p $(folder)))

#get all files we need to compile/link/include
SOURCES := $(foreach folder,$(SOURCEFOLDERS),$(wildcard $(folder)/*.cpp))
ifdef INCLUDEEVERYFOLDER
INCLUDES := $(foreach folder,$(SOURCEFOLDERS),$(addprefix -I,$(folder)))
else
INCLUDES := -I$(SOURCEDIR)
endif
INCLUDEFILES := $(foreach extention,$(INCLUDEFILESEXTENTIONS),$(foreach folder,$(SOURCEFOLDERS),$(wildcard $(folder)/*.$(extention))))
OBJS := $(foreach file,$(SOURCES),$(file:$(SOURCEDIR)/%.cpp=$(BUILDDIR)/%.o))
#preprocess $(LIBS) and $(THIRDPARTY) to right format
LIBS := $(subst -I,-I$(LIBDIR)/,$(LIBS))
LIBS := $(subst -L,-L$(LIBDIR)/,$(LIBS))
THIRDPARTY := $(foreach path,$(THIRDPARTY),$(addprefix $(LIBDIR)/,$(path)))
#preprocess $(DEFINES)
DEFIENS := $(foreach def,$(DEFINES),$(addprefix -D,$(def)))

run: compile
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

compile: $(OBJS) $(MAKEFILENAME)
	$(ECHO)g++ $(DEBUG) $(OBJS) $(THIRDPARTY) -o $(BUILDDIR)/$(APPNAME) $(DEFIENS) $(FLAGS) $(STDVERSION) $(INCLUDES) $(LIBS); \
	if [ $(PROGRESS) ]; then \
    echo Compiled!; \
  fi

makefileTest:
	@echo Done!

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