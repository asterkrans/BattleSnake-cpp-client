#include "../c_snakes/random_snake.h"

#include "c_api/snake_c_utils.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

// ////////////////////////////////////////////////////////////////////////////
// Callback called when the game starts.
static void snake_start(
  void * const pUserData,
  const char * const pGameId,
  const int width,
  const int height,
  StartOutputT * const pStartOutput
) {
  printf("Started game %s with width %d and height %d!\r\n", pGameId, width, height);

  // Fill in the snake info
  strncpy(pStartOutput->color, "blue", SNAKE_STRLEN);
  strncpy(pStartOutput->secondary_color, "red", SNAKE_STRLEN);
  strncpy(pStartOutput->name, "Unpredictable C Trump", SNAKE_STRLEN);
  strncpy(pStartOutput->taunt, "I change my mind a lot!", SNAKE_STRLEN);

  pStartOutput->head_type = SH_TONGUE;
  pStartOutput->tail_type = ST_FRECKLED;

}


// ////////////////////////////////////////////////////////////////////////////
static int checkHeading(int heading, bool canGoUp, bool canGoDown, bool canGoLeft, bool canGoRight) {
  if ((heading == DIR_UP) && (!canGoUp)) {
    heading = -1;
  }
  else if ((heading == DIR_DOWN) && (!canGoDown)) {
    heading = -1;
  }
  else if ((heading == DIR_LEFT) && (!canGoLeft)) {
    heading = -1;
  }
  else if ((heading == DIR_RIGHT) && (!canGoRight)) {
    heading = -1;
  }
  return heading;
}

// ////////////////////////////////////////////////////////////////////////////
// Callback called when it's time to make a new move.
static void snake_move(
  void * const pUserData,
  const char * const pGameId,
  const MoveInput * const pMoveInput,
  MoveOutput * const pMoveOutput) {
  int heading = -1;
  const int width = pMoveInput->width;
  const int height = pMoveInput->height;

  printf("Got move for game %s!\r\n", pGameId);

  SnakeT * const pMe = &pMoveInput->snakesArr[pMoveInput->yourSnakeIdx];
  const Coords head = pMe->coordsArr[0];
  const Coords tail = pMe->coordsArr[1];
  const bool goingLeft = head.x < tail.x;
  const bool goingRight = head.x > tail.x;
  const bool goingUp = head.y < tail.y;
  const bool goingDown = head.y > tail.y;
  const bool canGoDown = (head.y < (height - 1)) && (!goingUp);
  const bool canGoUp = (head.y > 0) && (!goingDown);
  const bool canGoRight = (head.x < (width - 1)) && (!goingLeft);
  const bool canGoLeft = (head.x > 0) && (!goingRight);
  while (heading < 0) {
    heading = rand() % 4;
    heading = checkHeading(heading, canGoUp, canGoDown, canGoLeft, canGoRight);
  }
  SnakeDoMove(pMoveOutput, heading, "I decided this.");
}

const SnakeCallbacks random_snake = {
  snake_start,
  snake_move
};

#ifdef __cplusplus
}
#endif
