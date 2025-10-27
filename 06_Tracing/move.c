// move.c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Использование: %s <исходный_файл> <целевой_файл>\n", argv[0]);
        return 1;
    }

    const char *infile_path = argv[1];
    const char *outfile_path = argv[2];

    int infile_fd = open(infile_path, O_RDONLY);
    if (infile_fd < 0) {
        perror("Ошибка открытия исходного файла");
        return 2;
    }

    struct stat infile_stat;
    if (fstat(infile_fd, &infile_stat) < 0) {
        perror("Ошибка получения информации об исходном файле");
        close(infile_fd);
        return 3;
    }

    int outfile_fd = open(outfile_path, O_WRONLY | O_CREAT | O_TRUNC, infile_stat.st_mode);
    if (outfile_fd < 0) {
        perror("Ошибка открытия/создания целевого файла");
        close(infile_fd);
        return 4;
    }

    char *buffer = malloc(infile_stat.st_size);
    if (!buffer) {
        perror("Ошибка выделения памяти");
        close(infile_fd);
        close(outfile_fd);
        return 5;
    }

    ssize_t bytes_read = read(infile_fd, buffer, infile_stat.st_size);
    if (bytes_read < 0) {
        perror("Ошибка чтения из исходного файла");
        free(buffer);
        close(infile_fd);
        close(outfile_fd);
        unlink(outfile_path);
        return 6;
    }

    ssize_t bytes_written = write(outfile_fd, buffer, bytes_read);
    if (bytes_written != bytes_read) {
        perror("Ошибка записи в целевой файл");
        free(buffer);
        close(infile_fd);
        close(outfile_fd);
        unlink(outfile_path);
        return 7;
    }

    free(buffer);

    if (close(outfile_fd) < 0) {
        perror("Ошибка закрытия целевого файла");
        close(infile_fd);
        unlink(outfile_path);
        return 8;
    }

    close(infile_fd);

    if (unlink(infile_path) < 0) {
        perror("Ошибка удаления исходного файла");
        return 9;
    }

    return 0;
}
