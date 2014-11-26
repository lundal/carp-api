/*****************************************************************************
 * Rules
 *
 * Development rule definitions
 *
 * Asbjørn Djupdal 2003
 * Kjetil Aamodt 2005
 * Ola Martin Tiseth Støvneng 2014
 * Per Thomas Lundal 2014
 *****************************************************************************/

#ifndef RULES_H
#define RULES_H

#include <stdint.h>
#include <stdbool.h>

enum ruleTypes {
  CHANGE, GROWTH
};

enum directions {
  UP, DOWN, NORTH, SOUTH, EAST, WEST
};

struct precond {
  bool state_dc;
  bool state_value;
  bool type_dc;
  int type_value;
};

struct RuleStruct {
  bool valid;
  int type;

  struct precond north;
  struct precond south;
  struct precond east;
  struct precond west;
  struct precond center;

  bool dont_change_state;

  union {
    struct {
      bool state;
      int type;
    } change;
    int copyFrom;
  } result;
};

#endif

