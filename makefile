CC=g++
LD=g++

CFLAGS=  fPIC O3 g0 Wall std=c++1z
LFLAGS=
LIBS= m glfw GLU X11 GLEW GL
PATH_INCS=
PATH_LIBS=
PATH_DLIB=

PATH_OBJ= build
PATH_SRC= src

BIN_NAME= build
#end of user settings

SRCS=$(shell find $(PATH_SRC) -name "*.cpp")
OBJS=$(SRCS:$(PATH_SRC)/%.cpp=$(PATH_OBJ)/%.o)
DEPS=$(SRCS:$(PATH_SRC)/%.cpp=$(PATH_OBJ)/%.d)

COMPILE_CPP=$(CC) -MMD -c $(patsubst %, -%,$(CFLAGS)) $(patsubst %, -I%,$(PATH_INCS)) 
LINK_CPP=$(LD) -o $@ $^ $(patsubst %,-rpath %,$(PATH_DLIB)) $(patsubst %, -L%, $(PATH_LIBS)) $(patsubst %, -l%, $(LIBS)) $(patsubst %, -%, $(LFLAGS))

all:$(PATH_OBJ)/$(BIN_NAME)

clean:
	rm -rf $(PATH_OBJ)

$(PATH_OBJ):
	@mkdir -p $@ 

$(PATH_OBJ)/$(BIN_NAME):$(OBJS)
	@echo "Building target" $@
	@echo "Invoking" $(LD) on $^
	@$(LINK_CPP)
	@echo "Building target" $@ "Complete"

$(PATH_OBJ)/%.o: $(PATH_SRC)/%.cpp ./makefile | $(PATH_OBJ)
	@echo "Building target" $@
	@echo "Invoking" $(CC) on $<
	@mkdir -p $(@D)
	@$(COMPILE_CPP) -o $@ $<
	@echo "Building target" $@ "Complete"

.PHONY: all clean

$(DEPS):

-include $(DEPS)
