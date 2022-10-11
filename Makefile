COMPILER := gcc
SOURCES_EXT := c

DIR_BUILD := build
DIR_SOURCE := src

KEYWORD_CONSOLE := console
DIR_CONSOLE := $(DIR_SOURCE)/$(KEYWORD_CONSOLE)
DIR_SOURCE_CONSOLE := $(DIR_CONSOLE)/$(DIR_SOURCE)
DIR_BUILD_CONSOLE := $(DIR_BUILD)/$(KEYWORD_CONSOLE)

KEYWORD_WEB := web
DIR_WEB := $(DIR_SOURCE)/$(KEYWORD_WEB)
DIR_SOURCE_WEB := $(DIR_WEB)/$(DIR_SOURCE)
DIR_BUILD_WEB := $(DIR_BUILD)/$(KEYWORD_WEB)

DIR_OUTPUT := output

INCLUDES := -I include
LINKS := -lm

FLAGS_COMPILER := -std=c99 -Wall -Wextra -pedantic
FLAGS_COMPILER_SUPPRESS := -Wno-infinite-recursion
FLAGS_COMPILER += $(FLAGS_COMPILER_SUPPRESS)

FLAGS_CPPCHECK := -q --std=c99 --enable=all --inconclusive $(INCLUDES)
FLAGS_CPPCHECK_SUPPRESS := --suppress=missingIncludeSystem --suppress=incorrectLogicOperator --suppress=unusedFunction
FLAGS_CPPCHECK += $(FLAGS_CPPCHECK_SUPPRESS)

SOURCES := $(wildcard $(DIR_SOURCE)/*.$(SOURCES_EXT))
SOURCES_CONSOLE := $(wildcard $(DIR_SOURCE_CONSOLE)/*.$(SOURCES_EXT))
SOURCES_WEB := $(wildcard $(DIR_SOURCE_WEB)/*.$(SOURCES_EXT))
OBJECTS := $(patsubst $(DIR_SOURCE)/%,$(DIR_BUILD)/%,$(SOURCES:.$(SOURCES_EXT)=.o))
OBJECTS += $(patsubst $(DIR_SOURCE_CONSOLE)/%,$(DIR_BUILD_CONSOLE)/%,$(SOURCES_CONSOLE:.$(SOURCES_EXT)=.o))

BUILD_TARGETS := $(DIR_BUILD)/%.o
BUILD_DEPS := $(DIR_SOURCE)/%.$(SOURCES_EXT)
TARGET := $(DIR_OUTPUT)/run

ifeq ($(OS),Windows_NT)
	LINKS += -lmingw32

	CMD_CPPCHECK := C:\Program Files\Cppcheck\cppcheck.exe

	CMD_RM := rd /s /q
	CMD_MKDIR_OUTPUT := if not exist "$(DIR_OUTPUT)" md "$(DIR_OUTPUT)"
	CMD_MKDIR_BUILD := if not exist "$(DIR_BUILD)" md "$(DIR_BUILD)"
else
	CMD_CPPCHECK := cppcheck

	CMD_RM := rm -rf
	CMD_MKDIR_OUTPUT := mkdir -p $(DIR_OUTPUT)
	CMD_MKDIR_BUILD := mkdir -p $(DIR_BUILD)
endif


$(TARGET): $(OBJECTS)
	@echo
	@echo " линковка"
	$(CMD_MKDIR_OUTPUT)
	$(COMPILER) $^ -o $(TARGET) $(LINKS)

$(BUILD_TARGETS): $(BUILD_DEPS)
	+$(MAKE) -C $(DIR_CONSOLE)

	@echo
	@echo " проверка" $<
	$(CMD_CPPCHECK) $(FLAGS_CPPCHECK) $(INCLUDES_DEFAULT) $<
	@echo
	@echo " сборка" $@
	$(CMD_MKDIR_BUILD)
	$(COMPILER) $(FLAGS_COMPILER) $(INCLUDES) -c -o $@ $< -save-temps

DIRS := . $(DIR_CONSOLE) $(DIR_WEB)
CLEAN_DIRS := $(addsuffix clean,$(DIRS))
clean: $(CLEAN_DIRS)
clean_dir:
	$(CMD_RM) $(DIR_BUILD) $(DIR_OUTPUT)
%clean: %
	$(MAKE) -C $< -f $(PWD)/Makefile clean_dir


WEB_OBJECTS := $(patsubst $(DIR_SOURCE_WEB)/%,$(DIR_BUILD_WEB)/%,$(SOURCES_WEB:.$(SOURCES_EXT)=.o)) build/web/main.o
WEB_COMPILER := emcc
WEB_TARGET := $(DIR_OUTPUT)/app.html
WEB_BUILD_DEPS := $(DIR_SOURCE_WEB)/%.$(SOURCES_EXT)

web_build:
	+$(MAKE) -C $(DIR_WEB)

	@echo
	@echo " проверка" src/main.c
	$(CMD_CPPCHECK) $(FLAGS_CPPCHECK) $(INCLUDES_DEFAULT) src/main.c
	@echo
	@echo " сборка" build/web/main.o
	$(WEB_COMPILER) $(FLAGS_COMPILER) -Wno-tautological-overlap-compare $(INCLUDES) -c -o build/web/main.o src/main.c

($WEB_TARGET): $(WEB_OBJECTS)
	@echo
	@echo " линковка"
	$(CMD_MKDIR_OUTPUT)
	$(WEB_COMPILER) $^ -s ASYNCIFY -s ASYNCIFY_IMPORTS=[print] --shell-file $(DIR_SOURCE_WEB)/shell.html $(LINKS) -o $(WEB_TARGET)

web: web_build ($WEB_TARGET)

.PHONY: clean
.PHONY: web
