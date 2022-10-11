# Консоль

## Требования
- _для linux:_ gcc
- _для windows:_ mingw

## Makefile

### Сборка
`make console`

### Очистка
`make clean`

## Запуск

### Linux
`> ./run_linux_console`

### Windows
`> run_win_console`

# Web

## Требования
- Emscripten

## Makefile

### Сборка
`make web`

## Запуск

### Linux
`> ./run_linux_web`

### Windows
`> run_win_web`

# Android

## Требования
- Android SDK
- Android NDK
- Gradle

## Makefile

### Создание .apk
`make android_build`

### Установка на подключенный смартфон
_предварительное создание .apk - не требуется_

`make android`

### Очистка
`make clean_android`