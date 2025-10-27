#!/bin/bash

OPEN_INFILE_CALL=9
OPEN_OUTFILE_CALL=10

check() {
    local exit_code=$1
    local expected_code=$2
    local file_exists=$3
    local file_not_exists=$4
    local msg=$5

    echo -n "Тест: $msg... "

    if [ "$exit_code" -ne "$expected_code" ]; then
        echo "НЕУДАЧА (неверный код выхода: $exit_code, ожидался: $expected_code)"
        return 1
    fi

    if [ -n "$file_exists" ] && [ ! -f "$file_exists" ]; then
        echo "НЕУДАЧА (файл '$file_exists' должен был остаться)"
        return 1
    fi

    if [ -n "$file_not_exists" ] && [ -f "$file_not_exists" ]; then
        echo "НЕУДАЧА (файл '$file_not_exists' должен был быть удален)"
        return 1
    fi

    echo "УСПЕХ"
}

echo "=== Запуск тестов с strace ==="
rm -f infile outfile infile_PROTECT

strace -e fault=openat:error=EACCES:when=$OPEN_INFILE_CALL ./move infile outfile > /dev/null 2>&1
check $? 2 "" "" "ошибка открытия исходного файла"
touch infile

strace -e fault=openat:error=EACCES:when=$OPEN_OUTFILE_CALL ./move infile outfile > /dev/null 2>&1
check $? 4 "infile" "outfile" "ошибка создания целевого файла"
rm -f outfile

echo "data" > infile
strace -e fault=read:error=EIO:when=1 ./move infile outfile > /dev/null 2>&1
check $? 6 "infile" "outfile" "ошибка чтения"
rm -f outfile

echo "test" > infile
strace -e fault=write:error=ENOSPC:when=1 ./move infile outfile > /dev/null 2>&1
check $? 7 "infile" "outfile" "ошибка записи"
rm -f outfile

# Обычно первый close() - это infile, второй - outfile. Поэтому when=2
echo "test" > infile
strace -e fault=close:error=EIO:when=2 ./move infile outfile > /dev/null 2>&1
check $? 8 "infile" "outfile" "ошибка закрытия целевого файла"
rm -f infile outfile

echo "test" > infile
strace -e fault=unlinkat:error=EPERM:when=1 ./move infile outfile > /dev/null 2>&1
check $? 9 "infile" "" "ошибка удаления исходного файла"
rm -f infile outfile

# --- Тест с LD_PRELOAD ---
echo ""
echo "=== Запуск теста с LD_PRELOAD ==="

touch infile_PROTECT
echo "data" > infile_PROTECT

LD_PRELOAD=./protect.so ./move infile_PROTECT outfile > /dev/null 2>&1
code=$?

check $code 9 "infile_PROTECT" "" "защита файла от удаления"

rm -f infile_PROTECT outfile
