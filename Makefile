DIR_BUILD := build
DIR_OUTPUT := output
LINKS := -lm

ifeq ($(OS),Windows_NT)
	#LINKS += -lmingw32

	CMD_CPPCHECK := C:\Program Files\Cppcheck\cppcheck.exe
	CMD_GRADLEW := gradlew

	CMD_RM := rd /s /q
	CMD_MKDIR_OUTPUT := if not exist "$(DIR_OUTPUT)" md "$(DIR_OUTPUT)"
	CMD_MKDIR_BUILD := if not exist "$(DIR_BUILD)" md "$(DIR_BUILD)"
else
	CMD_CPPCHECK := cppcheck
	CMD_GRADLEW := ./gradlew

	CMD_RM := rm -rf
	CMD_MKDIR_OUTPUT := mkdir -p $(DIR_OUTPUT)
	CMD_MKDIR_BUILD := mkdir -p $(DIR_BUILD)
endif

COMPILER := gcc
COMPILER_WEB := emcc

DIR_SOURCE := src
SOURCES_EXT := c

KEYWORD_CONSOLE := console
DIR_CONSOLE := $(DIR_SOURCE)/$(KEYWORD_CONSOLE)
DIR_SOURCE_CONSOLE := $(DIR_CONSOLE)/$(DIR_SOURCE)
DIR_BUILD_CONSOLE := $(DIR_BUILD)/$(KEYWORD_CONSOLE)
DIRS_OF_CONSOLE_MAKEFILES := . $(DIR_CONSOLE)
CLEAN_DIRS_CONSOLE := $(addsuffix clean_console,$(DIRS_OF_CONSOLE_MAKEFILES))

KEYWORD_WEB := web
DIR_WEB := $(DIR_SOURCE)/$(KEYWORD_WEB)
DIR_SOURCE_WEB := $(DIR_WEB)/$(DIR_SOURCE)
DIR_BUILD_WEB := $(DIR_BUILD)/$(KEYWORD_WEB)
DIRS_OF_WEB_MAKEFILES := . $(DIR_WEB)
CLEAN_DIRS_WEB := $(addsuffix clean_web,$(DIRS_OF_WEB_MAKEFILES))

DIR_ANDROID := $(DIR_SOURCE)/android/project

INCLUDES := -I include

FLAGS_COMPILER := -std=c99 -Wall -Wextra -pedantic
FLAGS_COMPILER_SUPPRESS := -Wno-infinite-recursion
FLAGS_COMPILER += $(FLAGS_COMPILER_SUPPRESS)

FLAGS_CPPCHECK := -q --std=c99 --enable=all --inconclusive $(INCLUDES)
FLAGS_CPPCHECK_SUPPRESS := --suppress=missingIncludeSystem --suppress=incorrectLogicOperator --suppress=unusedFunction
FLAGS_CPPCHECK += $(FLAGS_CPPCHECK_SUPPRESS)

SOURCES_MAIN := $(wildcard $(DIR_SOURCE)/*.$(SOURCES_EXT))
SOURCES_CONSOLE := $(wildcard $(DIR_SOURCE_CONSOLE)/*.$(SOURCES_EXT))
SOURCES_WEB := $(wildcard $(DIR_SOURCE_WEB)/*.$(SOURCES_EXT))

OBJECTS_CONSOLE := $(patsubst $(DIR_SOURCE)/%,$(DIR_BUILD)/%,$(SOURCES_MAIN:.$(SOURCES_EXT)=.o))
OBJECTS_CONSOLE += $(patsubst $(DIR_SOURCE_CONSOLE)/%,$(DIR_BUILD_CONSOLE)/%,$(SOURCES_CONSOLE:.$(SOURCES_EXT)=.o))
OBJECTS_WEB := $(patsubst $(DIR_SOURCE_WEB)/%,$(DIR_BUILD_WEB)/%,$(SOURCES_WEB:.$(SOURCES_EXT)=.o)) build/web/main.o

BUILD_DEPS_MAIN := $(DIR_SOURCE)/%.$(SOURCES_EXT)
BUILD_TARGETS_MAIN := $(DIR_BUILD)/%.o

BUILD_DEPS_WEB := $(DIR_SOURCE_WEB)/%.$(SOURCES_EXT)

TARGET_CONSOLE := $(DIR_OUTPUT)/run
TARGET_WEB := $(DIR_OUTPUT)/app.html


clean:
	$(CMD_RM) $(DIR_BUILD) $(DIR_OUTPUT)

clean_android:
	cd $(DIR_ANDROID); \
	$(CMD_GRADLEW) clean


$(BUILD_TARGETS_MAIN): $(BUILD_DEPS_MAIN)
	+$(MAKE) -C $(DIR_CONSOLE)

	@echo
	@echo " проверка" $<
	$(CMD_CPPCHECK) $(FLAGS_CPPCHECK) $(INCLUDES_DEFAULT) $<
	@echo
	@echo " сборка" $@
	$(CMD_MKDIR_BUILD)
	$(COMPILER) $(FLAGS_COMPILER) $(INCLUDES) -c -o $@ $< -save-temps

web_build:
	+$(MAKE) -C $(DIR_WEB)

	@echo
	@echo " проверка" src/main.c
	$(CMD_CPPCHECK) $(FLAGS_CPPCHECK) $(INCLUDES_DEFAULT) src/main.c
	@echo
	@echo " сборка" build/web/main.o
	$(COMPILER_WEB) $(FLAGS_COMPILER) -Wno-tautological-overlap-compare $(INCLUDES) -c -o build/web/main.o src/main.c

android_build:
	cd $(DIR_ANDROID); \
	$(CMD_GRADLEW) assembleDebug


console: $(OBJECTS_CONSOLE)
	@echo
	@echo " линковка"
	$(CMD_MKDIR_OUTPUT)
	$(COMPILER) $^ -o $(TARGET_CONSOLE) $(LINKS)

web: web_build
	@echo
	@echo " линковка"
	$(CMD_MKDIR_OUTPUT)
	$(COMPILER_WEB) $(OBJECTS_WEB) -s ASYNCIFY -s ASYNCIFY_IMPORTS=[print] --shell-file $(DIR_SOURCE_WEB)/shell.html $(LINKS) -o $(TARGET_WEB)

android:
	cd $(DIR_ANDROID); \
	$(CMD_GRADLEW) installDebug


.PHONY: clean
.PHONY: clean_console

.PHONY: console

.PHONY: web
.PHONY: web_build

.PHONY: android
.PHONY: android_build
