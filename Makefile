COMPILER := gcc
SOURCES_EXT := c

DIR_SOURCE := src
DIR_BUILD := build
DIR_BIN := bin
DIR_WEB := web

#INCLUDES_DEFAULT := -I include

FLAGS_COMPILER_DEFAULT := -std=c99 -Wall -Wextra -pedantic
#FLAGS_COMPILER_SUPPRESS := -Wno-discarded-qualifiers
FLAGS_COMPILER := $(FLAGS_COMPILER_DEFAULT) $(FLAGS_COMPILER_SUPPRESS)

FLAGS_CPPCHECK_DEFAULT := -q --std=c99 --enable=all --inconclusive
FLAGS_CPPCHECK_SUPPRESS := --suppress=missingIncludeSystem
FLAGS_CPPCHECK := $(FLAGS_CPPCHECK_DEFAULT) $(FLAGS_CPPCHECK_SUPPRESS)

ifeq ($(OS),Windows_NT)
	SOURCES := $(wildcard $(DIR_SOURCE)/*.$(SOURCES_EXT))
	OBJECTS := $(patsubst $(DIR_SOURCE)/%,$(DIR_BUILD)/%,$(SOURCES:.$(SOURCES_EXT)=.o))

	LINKS := -lmingw32 -lm
#	INCLUDES := $(INCLUDES_DEFAULT)
#	FLAGS_COMPILER := $(FLAGS_COMPILER)

	CMD_CPPCHECK := C:\Program Files\Cppcheck\cppcheck.exe

	BUILD_TARGETS := $(DIR_BUILD)/%.o
	BUILD_DEPS := $(DIR_SOURCE)/%.$(SOURCES_EXT)
	TARGET := $(DIR_BIN)/run

	CMD_RM := rd /s /q
	CMD_MKDIR_BIN := if not exist "$(DIR_BIN)" md "$(DIR_BIN)"
	CMD_MKDIR_BUILD := if not exist "$(DIR_BUILD)" md "$(DIR_BUILD)"
else
	SOURCES := $(shell find $(DIR_SOURCE) -type f -name *.$(SOURCES_EXT))
	OBJECTS := $(patsubst $(DIR_SOURCE)/%,$(DIR_BUILD)/%,$(SOURCES:.$(SOURCES_EXT)=.o))

	LINKS := -lm
#	INCLUDES := $(INCLUDES_DEFAULT)
#	FLAGS_COMPILER := $(FLAGS_COMPILER)

	CMD_CPPCHECK := cppcheck

	BUILD_TARGETS := $(DIR_BUILD)/%.o
	BUILD_DEPS := $(DIR_SOURCE)/%.$(SOURCES_EXT)
	TARGET := $(DIR_BIN)/run

	CMD_RM := rm -rf
	CMD_MKDIR_BIN := mkdir -p $(DIR_BIN)
	CMD_MKDIR_BUILD := mkdir -p $(DIR_BUILD)
endif


$(TARGET): $(OBJECTS)
	@echo
	@echo " линковка"
	$(CMD_MKDIR_BIN)
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
	$(CMD_RM) $(DIR_BUILD) $(DIR_BIN) $(DIR_WEB)

web:
	mkdir -p $(DIR_WEB)
	emcc $(SOURCES) -pthread --shell-file $(DIR_SOURCE)/shell.html -o $(DIR_WEB)/app.html

.PHONY: clean
.PHONY: web
