DIR_BUILD := build
DIR_OUTPUT := output
LINKS := -lm

ifeq ($(OS),Windows_NT)
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

DIR_SOURCE := src
SOURCES_EXT := c

KEYWORD_CONSOLE := console
DIR_CONSOLE := $(DIR_SOURCE)/$(KEYWORD_CONSOLE)
DIR_SOURCE_CONSOLE := $(DIR_CONSOLE)
DIR_BUILD_CONSOLE := $(DIR_BUILD)/$(KEYWORD_CONSOLE)

KEYWORD_WEB := web
DIR_WEB := $(DIR_SOURCE)/$(KEYWORD_WEB)
DIR_SOURCE_WEB := $(DIR_WEB)
DIR_BUILD_WEB := $(DIR_BUILD)/$(KEYWORD_WEB)

DIR_ANDROID := $(DIR_SOURCE)/android/project

INCLUDES := -I include

FLAGS_COMPILER := -Wall -Wextra -pedantic
FLAGS_COMPILER_SUPPRESS := -Wno-infinite-recursion -Wno-unused-variable -Wno-tautological-overlap-compare
FLAGS_COMPILER += $(FLAGS_COMPILER_SUPPRESS)

FLAGS_CPPCHECK := -q --enable=all --inconclusive $(INCLUDES)
FLAGS_CPPCHECK_SUPPRESS := --suppress=missingIncludeSystem --suppress=incorrectLogicOperator --suppress=unusedFunction
FLAGS_CPPCHECK += $(FLAGS_CPPCHECK_SUPPRESS)

SOURCES_MAIN := $(wildcard $(DIR_SOURCE)/*.$(SOURCES_EXT))
SOURCES_CONSOLE := $(wildcard $(DIR_SOURCE_CONSOLE)/*.$(SOURCES_EXT))
SOURCES_WEB := $(wildcard $(DIR_SOURCE_WEB)/*.$(SOURCES_EXT))

OBJECTS_MAIN := $(patsubst $(DIR_SOURCE)/%,$(DIR_BUILD)/%,$(SOURCES_MAIN:.$(SOURCES_EXT)=.o))
OBJECTS_CONSOLE := $(patsubst $(DIR_SOURCE_CONSOLE)/%,$(DIR_BUILD_CONSOLE)/%,$(SOURCES_CONSOLE:.$(SOURCES_EXT)=.o))
OBJECTS_WEB := $(patsubst $(DIR_SOURCE_WEB)/%,$(DIR_BUILD_WEB)/%,$(SOURCES_WEB:.$(SOURCES_EXT)=.o))

BUILD_DEPS_MAIN := $(DIR_SOURCE)/%.$(SOURCES_EXT)

BUILD_TARGETS_MAIN := $(DIR_BUILD)/%.o
BUILD_TARGETS_CONSOLE := $(DIR_BUILD_CONSOLE)/%.o
BUILD_TARGETS_WEB := $(DIR_BUILD_WEB)/%.o

TARGET_CONSOLE := $(DIR_OUTPUT)/run
TARGET_WEB := $(DIR_OUTPUT)/app.html


info:
	@echo "доступные команды: console, web, android_install, android_apk, clean, clean_android"


clean:
	$(CMD_RM) $(DIR_BUILD) $(DIR_OUTPUT)

clean_android:
	cd $(DIR_ANDROID); \
	$(CMD_GRADLEW) clean


$(BUILD_TARGETS_MAIN): $(BUILD_DEPS_MAIN)
	@echo
	@echo " проверка" $<
	$(CMD_CPPCHECK) $(FLAGS_CPPCHECK) $(INCLUDES_DEFAULT) $<
	@echo
	@echo " сборка" $@
	$(CMD_MKDIR_BUILD)
	$(COMPILER) $(FLAGS_COMPILER) $(INCLUDES) -save-temps=obj -c -o $@ $<

$(BUILD_TARGETS_CONSOLE):
	+$(MAKE) -C $(DIR_CONSOLE)

$(BUILD_TARGETS_WEB):
	+$(MAKE) -C $(DIR_WEB)


console: COMPILER = gcc
console: $(OBJECTS_CONSOLE) $(OBJECTS_MAIN)
	@echo
	@echo " линковка"
	$(CMD_MKDIR_OUTPUT)
	$(COMPILER) $^ $(LINKS) -o $(TARGET_CONSOLE)

web: COMPILER = emcc
web: $(OBJECTS_WEB) $(OBJECTS_MAIN)
	@echo
	@echo " линковка"
	$(CMD_MKDIR_OUTPUT)
	$(COMPILER) $^ -s ASYNCIFY -s ASYNCIFY_IMPORTS=[print] --shell-file $(DIR_SOURCE_WEB)/shell.html $(LINKS) -o $(TARGET_WEB)

android:
	cd $(DIR_ANDROID); \
	$(CMD_GRADLEW) installDebug

android_apk:
	cd $(DIR_ANDROID); \
	$(CMD_GRADLEW) assembleDebug


.PHONY: clean
.PHONY: clean_android

.PHONY: console

.PHONY: web

.PHONY: android
.PHONY: android_apk
