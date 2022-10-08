COMPILER := gcc
SOURCES_EXT := c

DIR_SOURCE := src
DIR_SOURCE_WEB := $(DIR_SOURCE)/web
DIR_BUILD := build
DIR_OUTPUT := output

#INCLUDES := -I include
LINKS := -lm

FLAGS_COMPILER := -std=c99 -Wall -Wextra -pedantic
#FLAGS_COMPILER_SUPPRESS :=
#FLAGS_COMPILER += $(FLAGS_COMPILER_SUPPRESS)

FLAGS_CPPCHECK := -q --std=c99 --enable=all --inconclusive
FLAGS_CPPCHECK_SUPPRESS := --suppress=missingIncludeSystem
FLAGS_CPPCHECK += $(FLAGS_CPPCHECK_SUPPRESS)

SOURCES := $(wildcard $(DIR_SOURCE)/*.$(SOURCES_EXT))
SOURCES_WEB := $(wildcard $(DIR_SOURCE_WEB)/*.$(SOURCES_EXT))
OBJECTS := $(patsubst $(DIR_SOURCE)/%,$(DIR_BUILD)/%,$(SOURCES:.$(SOURCES_EXT)=.o))

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
	@echo
	@echo " проверка" $<
	$(CMD_CPPCHECK) $(FLAGS_CPPCHECK) $(INCLUDES_DEFAULT) $<

	@echo
	@echo " сборка" $@
	$(CMD_MKDIR_BUILD)
	$(COMPILER) $(FLAGS_COMPILER) $(INCLUDES) -c -o $@ $< -save-temps

clean:
	$(CMD_RM) $(DIR_BUILD) $(DIR_OUTPUT)

web:
	mkdir -p $(DIR_OUTPUT)
	emcc $(SOURCES_WEB) -s ASYNCIFY -s ASYNCIFY_IMPORTS=[print] --shell-file $(DIR_SOURCE_WEB)/shell.html -o $(DIR_OUTPUT)/app.html

.PHONY: clean
.PHONY: web
