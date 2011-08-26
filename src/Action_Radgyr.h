#ifndef INC_ACTION_RADGYR_H
#define INC_ACTION_RADGYR_H
/// Class: Radgyr
/// Action to calculate the radius of gyration of atoms within a mask.
#include "Action.h"
class Radgyr: public Action {
    DataSet *rog;
    DataSet *rogmax;
    AtomMask Mask1;
    bool calcRogmax;
  public:
    Radgyr();
    ~Radgyr();

    int init();
    int setup();
    int action();
};
#endif
