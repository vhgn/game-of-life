#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GRID_SIZE 10

bool grid[GRID_SIZE][GRID_SIZE][2];
bool current;

void init_board(void);
bool wait_for_input(void);
void update_board(void);
void repaint_board(void);

int main(void) {
  init_board();

  while (true) {
    bool stop = wait_for_input();
    if (stop) {
      break;
    }

    update_board();
    repaint_board();
  }

  return 0;
}

void init_board(void) {
  srand(time(NULL));

  current = 0;
  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      grid[current][i][j] = rand() % 2;
    }
  }
}

bool wait_for_input(void) {
  char input[2];
  fgets(input, 2, stdin);

  return input[0] == 'q';
}

void update_board(void) {
  bool next = !current;

  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      int sum = 0;

      for (int r = -1; r <= 1; r++) {
        int row = i + r;
        if (row == -1 || row == GRID_SIZE) {
          continue;
        }

        for (int c = -1; c <= 1; c++) {
          int col = j + c;
          if (col == -1 || col == GRID_SIZE) {
            continue;
          }

          if (row == i && col == j) {
            continue;
          }

          sum += grid[row][col][current];
        }
      }

      bool cell = grid[i][j][current];
      bool* future_cell = &grid[i][j][next];

      if (cell) {
        /* Any living cell with less than 2 live neighbors dies */
        /* Any living cell with 2 or 3 live neighbors continues to be alive */
        /* Any living cell with more than 3 live neighbors dies */
        *future_cell = sum == 2 || sum == 3;
      } else {
        /* Any dead cell with 3 live neighbors becomes a live cell */
        *future_cell = sum == 3;
      }
    }
  }

  current = next;
}

#define CLEAR_SCREEN "\033[2J\033[1;1H"
#define LIVE_CELL 'x'
#define DEAD_CELL ' '

void repaint_board(void) {
  printf(CLEAR_SCREEN);

  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      printf("%c", grid[current][i][j] ? LIVE_CELL : DEAD_CELL);
    }
    printf("\n");
  }
}

