# Список исполняемых файлов, которые нужно собрать
bin_PROGRAMS = rhasher

# Исходные файлы для rhasher
rhasher_SOURCES = rhasher.c

# Библиотеки, с которыми нужно линковать rhasher
# -lrhash добавляется через LIBS в configure.ac, если найдена
rhasher_LDADD = $(LIBS)

# Добавляем CFLAGS, чтобы компилятор видел наш #define
rhasher_CPPFLAGS = $(DEFS)

# Секция для тестов
TESTS = tests/test_md5.sh tests/test_sha1.sh
check_PROGRAMS =

# Добавляем тестовые скрипты в дистрибутив
EXTRA_DIST = tests/test_md5.sh tests/test_sha1.sh tests/test_file.txt

gitclean:
	git clean -df
	rm *.o
