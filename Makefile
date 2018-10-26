CXX = g++
CPP = cpp
CFLAGS = -Wall -Werror -g -std=c++17

SRC_DIR = src
OBJ_DIR = bin
DEP_DIR = dep

_SRCS = $(patsubst $(SRC_DIR)/%, %, $(wildcard $(SRC_DIR)/*.cpp))
_OBJS = $(_SRCS:.cpp=.o)
_DEPS = $(_OBJS:.o=.d)

SRCS = $(patsubst %, $(SRC_DIR)/%, $(_SRCS))
OBJS = $(patsubst %, $(OBJ_DIR)/%, $(_OBJS))
DEPS = $(patsubst %, $(DEP_DIR)/%, $(_DEPS))

DIR_GUARD = @mkdir -p $(@D)

jrnl: $(OBJS)
	$(CXX) $(CFLAGS) $^ -o $@

-include $(DEPS)

$(DEP_DIR)/%.d: $(SRC_DIR)/%.cpp
	$(DIR_GUARD)
	@$(CPP) $(CFLAGS) $< -MM -MT $(OBJ_DIR)/$(@F:.d=.o) > $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(DIR_GUARD)
	$(CXX) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJS) jrnl

.PHONY: cleandep
cleandep:
	rm -f $(DEPS)
