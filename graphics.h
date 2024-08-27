#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "observer.h"
#include "game.h"
#include "window.h"
#include "tile.h"

class Graphics : public Observer {
  int x;
  int y;
  inline static bool displayed = false;
  const int tileSize = 75;
  const int border = 50;
  Game* game;
  Xwindow* window;
  void displayLabels();
  void displayTile();
 public:
  Graphics(int x, int y, Game* game, Xwindow* window);
  void notify() override;
};

#endif
