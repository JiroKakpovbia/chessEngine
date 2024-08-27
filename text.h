#ifndef TEXT_H
#define TEXT_H

#include "observer.h"
#include "game.h"
#include "tile.h"

class Text : public Observer {
  Game* game;
  
 public:
  Text(Game* game);
  void notify() override;
};

#endif
