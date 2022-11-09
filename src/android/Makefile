DIR_PROJECT := project

ifeq ($(OS),Windows_NT)
	CMD_GRADLEW := gradlew
else
	CMD_GRADLEW := ./gradlew
endif


info:
	@echo "доступные команды: install, apk, clean"

install:
	cd $(DIR_PROJECT); \
	$(CMD_GRADLEW) installDebug

apk:
	cd $(DIR_PROJECT); \
	$(CMD_GRADLEW) assembleDebug

clean:
	cd $(DIR_PROJECT); \
	$(CMD_GRADLEW) clean
