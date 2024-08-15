#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Observer {
  int x;
  int y;
 public:
  virtual void notify() = 0;
  virtual ~Observer() = default;
};

#endif
