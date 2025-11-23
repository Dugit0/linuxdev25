#include <stdio.h>
#include <stdlib.h>


void print_maze(char** maze, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%c", maze[i][j]);
        }
        printf("\n");
    }
}


void break_walls(char** maze, int num_rooms, char space) {
    int directions[2][2] = {{-1, 0}, {0, 1}};
    for (int i = 0; i < num_rooms; i++) {
        for (int j = 0; j < num_rooms; j++) {
            int new_direct[2] = {};
            int new_direct_num = 0;
            for (int k = 0; k < 2; k++) {
                int ni = i + directions[k][0];
                int nj = j + directions[k][1];
                if (0 <= ni && ni < num_rooms && 0 <= nj && nj < num_rooms) {
                    new_direct[new_direct_num] = k;
                    new_direct_num += 1;
                }
            }
            if (new_direct_num == 0) {
                continue;
            }
            int rand_dir = new_direct[rand() % new_direct_num];
            maze[i * 2 + 1 + directions[rand_dir][0]][j * 2 + 1 + directions[rand_dir][1]] = space;
        }
    }
    return;
}


int main(void) {
    int seed = 42;
    char wall = '#';
    char space = '.';
    int num_rooms = 4;

    srand(seed);

    int size = num_rooms * 2 + 1;

    char** maze = calloc(size, sizeof(*maze));
    for (int i = 0; i < size; i++) {
        maze[i] = calloc(size, sizeof(*maze[i]));
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i % 2 == 0 || j % 2 == 0) {
                maze[i][j] = wall;
            } else {
                maze[i][j] = space;
            }
        }
    }

    break_walls(maze, num_rooms, space);
    print_maze(maze, size);

    for (int i = 0; i < size; i++) {
        free(maze[i]);
    }
    free(maze);

    return 0;
}
