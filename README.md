# Консоль
![console](https://user-images.githubusercontent.com/70647779/200965233-ab41d867-b18a-4e4c-af03-255c62c705dc.png)

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
![web](https://user-images.githubusercontent.com/70647779/200965660-0ac6d4f9-a05c-4ca2-b0e0-abce5060dd20.png)

## Требования
- emscripten

## Makefile

### Сборка
`make web`

### Очистка
`make clean`

## Запуск

### Linux
`> ./run_linux_web`

### Windows
`> run_win_web`

# Android
<img src="https://user-images.githubusercontent.com/70647779/200965836-0d352fa8-205c-45ed-814d-3bd9fc0781fb.png" width="50%">

## Требования
- android SDK
- android NDK
- gradle

## Makefile

### Создание .apk
`make android_apk`

### Установка на подключенный смартфон
_предварительное создание .apk - не требуется_

`make android`

### Очистка
`make android_clean`

# Тестирование

## Требования
- linux
- gcc
- bash
- diff
- vintage BASIC

## Makefile

### Запуск
`make testing`
