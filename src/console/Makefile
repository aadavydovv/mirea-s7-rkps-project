COMPILER := gcc

KEYWORD_BUILD := build
DIR_PROJECT_ROOT := ../..
DIR_OUTPUT := $(DIR_PROJECT_ROOT)/output
DIR_BUILD_CONSOLE := $(DIR_PROJECT_ROOT)/$(KEYWORD_BUILD)/console

INCLUDES := -I $(DIR_PROJECT_ROOT)/include

ifeq ($(OS),Windows_NT)
	CMD_CPPCHECK := C:\Program Files\Cppcheck\cppcheck.exe
	CMD_MKDIR_OUTPUT := if not exist "$(DIR_OUTPUT)" md "$(DIR_OUTPUT)"
	CMD_MKDIR_BUILD_CONSOLE := if not exist "$(DIR_BUILD_CONSOLE)" md "$(DIR_BUILD_CONSOLE)"
else
	CMD_CPPCHECK := cppcheck
	CMD_MKDIR_OUTPUT := mkdir -p $(DIR_OUTPUT)
	CMD_MKDIR_BUILD_CONSOLE := mkdir -p "$(DIR_BUILD_CONSOLE)"
endif

BUILD_TARGETS := $(DIR_BUILD_CONSOLE)/%.o
BUILD_DEPS := ./%.c

SOURCES_CONSOLE := $(wildcard ./*.c)
OBJECTS_CONSOLE := $(patsubst ./%,$(DIR_BUILD_CONSOLE)/%,$(SOURCES_CONSOLE:.c=.o))

all: $(OBJECTS_CONSOLE) build_rng build_core
	@echo
	@echo " линковка"
	$(CMD_MKDIR_OUTPUT)
	$(COMPILER) $(wildcard $(DIR_PROJECT_ROOT)/$(KEYWORD_BUILD)/**/*.o) -lm -o $(DIR_OUTPUT)/run

$(BUILD_TARGETS): $(BUILD_DEPS)
	@echo
	@echo " проверка" $<
	$(CMD_CPPCHECK) -q --enable=all --inconclusive --suppress=missingIncludeSystem --suppress=unusedFunction $(INCLUDES) $<

	@echo
	@echo " сборка" $@
	$(CMD_MKDIR_BUILD_CONSOLE)
	$(COMPILER) -Wall -Wextra -pedantic -Wno-infinite-recursion -Wno-unused-variable -Wno-tautological-overlap-compare $(INCLUDES) -c -o $@ $<

build_rng:
	+$(MAKE) -C ../xorshift normal

build_core:
	+$(MAKE) -C .. normal
