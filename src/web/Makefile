COMPILER := emcc

KEYWORD_BUILD := build
DIR_PROJECT_ROOT := ../..
DIR_OUTPUT := $(DIR_PROJECT_ROOT)/output
DIR_BUILD_WEB := $(DIR_PROJECT_ROOT)/$(KEYWORD_BUILD)/web

INCLUDES := -I $(DIR_PROJECT_ROOT)/include

ifeq ($(OS),Windows_NT)
	CMD_CPPCHECK := C:\Program Files\Cppcheck\cppcheck.exe
	CMD_MKDIR_OUTPUT := if not exist "$(DIR_OUTPUT)" md "$(DIR_OUTPUT)"
	CMD_MKDIR_BUILD_WEB := if not exist "$(DIR_BUILD_WEB)" md "$(DIR_BUILD_WEB)"
else
	CMD_CPPCHECK := cppcheck
	CMD_MKDIR_OUTPUT := mkdir -p $(DIR_OUTPUT)
	CMD_MKDIR_BUILD_WEB := mkdir -p "$(DIR_BUILD_WEB)"
endif

BUILD_TARGETS := $(DIR_BUILD_WEB)/%.o
BUILD_DEPS := ./%.c

SOURCES_WEB := $(wildcard ./*.c)
OBJECTS_WEB := $(patsubst ./%,$(DIR_BUILD_WEB)/%,$(SOURCES_WEB:.c=.o))

all: $(OBJECTS_WEB) build_rng build_core
	@echo
	@echo " линковка"
	$(CMD_MKDIR_OUTPUT)
	$(COMPILER) $(wildcard $(DIR_PROJECT_ROOT)/$(KEYWORD_BUILD)/**/*.o) -s ASYNCIFY -s ASYNCIFY_IMPORTS=[print] --shell-file shell.html -lm -o $(DIR_OUTPUT)/app.html

$(BUILD_TARGETS): $(BUILD_DEPS)
	@echo
	@echo " проверка" $<
	$(CMD_CPPCHECK) -q --enable=all --inconclusive --suppress=missingIncludeSystem --suppress=unusedFunction $(INCLUDES) $<

	@echo
	@echo " сборка" $@
	$(CMD_MKDIR_BUILD_WEB)
	$(COMPILER) -Wall -Wextra -pedantic -Wno-infinite-recursion -Wno-unused-variable -Wno-tautological-overlap-compare -Wno-extra-semi $(INCLUDES) -c -o $@ $<

build_rng:
	+$(MAKE) -C ../xorshift web

build_core:
	+$(MAKE) -C .. web
