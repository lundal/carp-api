#ifndef RULES_H
#define RULES_H

#include "types.h"

enum ruleTypes {
  CHANGE, GROWTH
};

enum directions {
  UP, DOWN, NORTH, SOUTH, EAST, WEST
};

struct precond {
  bool_t state_dc;
  bool_t state_value;
  bool_t type_dc;
  int type_value;
};

struct RuleStruct {
  bool_t valid;
  int type;

  struct precond up;
  struct precond down;
  struct precond north;
  struct precond south;
  struct precond east;
  struct precond west;
  struct precond center;

  bool_t dont_change_state;

  union {
    struct {
      bool_t state;
      int type;
    } change;
    int copyFrom;
  } result;
};

#endif

