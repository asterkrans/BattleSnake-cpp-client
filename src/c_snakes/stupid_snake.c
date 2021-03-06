#include "../c_snakes/stupid_snake.h"

#include "c_api/snake_c_utils.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

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
  strncpy(pStartOutput->name, "Dorky C McDumberface", SNAKE_STRLEN);
  strncpy(pStartOutput->taunt, "I'm a gonna getcha!", SNAKE_STRLEN);

  pStartOutput->head_type = SH_TONGUE;
  pStartOutput->tail_type = ST_FRECKLED;

}

// ////////////////////////////////////////////////////////////////////////////
// Callback called when it's time to make a new move.
static void snake_move(
  void * const pUserData,
  const char * const pGameId,
  const MoveInput * const pMoveInput,
  MoveOutput * const pMoveOutput) {

  printf("Got move for game %s!\r\n", pGameId);

  if (pMoveInput->numFood <= 0) {
    SnakeDoMove(pMoveOutput, DIR_DOWN, "No food!  Let's go DOOOWN!");
  }
  else {

    SnakeT * const pMe = &pMoveInput->snakesArr[pMoveInput->yourSnakeIdx];
    const Coords head = pMe->coordsArr[0];
    const Coords food0 = pMoveInput->foodArr[0];

    printf("my pos: [%d,%d] food:[%d,%d]\r\n",
      head.x, head.y, food0.x, food0.y);

    // Print the current battlefield.
    Battlefield * const pB = SnakeBattlefieldAllocAndUpdate(pMoveInput);
    SnakeBattlefieldPrint(pB);
    SnakeBattlefieldFree(pB);

    if (food0.y > head.y) {
      SnakeDoMove(pMoveOutput, DIR_DOWN, "Watch out! Going down!!!");
    }
    else if (food0.y < head.y) {
      SnakeDoMove(pMoveOutput, DIR_UP, "Going up up up!!!");
    }
    else if (food0.x < head.x) {
      SnakeDoMove(pMoveOutput, DIR_LEFT, "Left we go!!!");
    }
    else {
      SnakeDoMove(pMoveOutput, DIR_RIGHT, "Food!!! Yummy!");
    }
  }
}

const SnakeCallbacks stupid_snake = {
  snake_start,
  snake_move
};

#ifdef __cplusplus
}
#endif
