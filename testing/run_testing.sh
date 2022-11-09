#!/bin/bash

echo
echo
echo "начало тестирования..."
echo

mkdir -p log/c log/vintbas

scripts/run_vintbas.sh
scripts/run_c.sh

DO_LOGS_DIFFER=0

for log in log/vintbas/*; do
  echo
  echo
  echo "проверка $(basename "$log")..."
  echo
  diff "$log" "$(echo "$log" | sed -r 's/log\/vintbas\//log\/c\//g')"
  if [[ $? -ne 0 ]]; then
    DO_LOGS_DIFFER=1
  fi
done

if [[ DO_LOGS_DIFFER -eq 0 ]]; then
  echo
  echo
  echo "результат тестирования: логи совпадают!"
  echo
else
  echo
  echo
  echo "Результат тестирования: логи НЕ СОВПАДАЮТ"
  echo
fi
