COMPILER := gcc

KEYWORD_BUILD := build
DIR_PROJECT_ROOT := ..
DIR_OUTPUT := $(DIR_PROJECT_ROOT)/output
DIR_BUILD_TESTING := $(DIR_PROJECT_ROOT)/$(KEYWORD_BUILD)/testing

INCLUDES := -I $(DIR_PROJECT_ROOT)/include

ifeq ($(OS),Windows_NT)
	CMD_CPPCHECK := C:\Program Files\Cppcheck\cppcheck.exe
	CMD_MKDIR_OUTPUT := if not exist "$(DIR_OUTPUT)" md "$(DIR_OUTPUT)"
	CMD_MKDIR_BUILD_TESTING := if not exist "$(DIR_BUILD_TESTING)" md "$(DIR_BUILD_TESTING)"
else
	CMD_CPPCHECK := cppcheck
	CMD_MKDIR_OUTPUT := mkdir -p $(DIR_OUTPUT)
	CMD_MKDIR_BUILD_TESTING := mkdir -p "$(DIR_BUILD_TESTING)"
endif

BUILD_TARGETS := $(DIR_BUILD_TESTING)/%.o
BUILD_DEPS := ./%.c

SOURCES_TESTING := $(wildcard ./*.c)
OBJECTS_TESTING := $(patsubst ./%,$(DIR_BUILD_TESTING)/%,$(SOURCES_TESTING:.c=.o))

all: build_rng build_console
	scripts/run_testing.sh

build_rng:
	+$(MAKE) -C rng

build_console:
	+$(MAKE) -C ../src/console testing
