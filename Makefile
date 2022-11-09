ifeq ($(OS),Windows_NT)
	CMD_RM := rd /s /q
else
	CMD_RM := rm -rf
endif


info:
	@echo "доступные команды: console, web, android, android_apk, android_clean, testing, clean"

clean:
	$(CMD_RM) build output testing/output testing/log

console: clean
	+$(MAKE) -C src/console normal

web: clean
	+$(MAKE) -C src/web

android:
	+$(MAKE) -C src/android install

android_apk:
	+$(MAKE) -C src/android apk

android_clean:
	+$(MAKE) -C src/android clean

testing: clean
	+$(MAKE) -C testing
