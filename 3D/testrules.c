#include "testrules.h"

struct RuleStruct create_rule_grow_x (void) {
  struct RuleStruct rule;

  rule.valid = TRUE;
  rule.type = GROWTH;

  // precondition
  rule.up.state_dc = TRUE;
  rule.up.state_value = FALSE;
  rule.up.type_dc = TRUE;
  rule.up.type_value = 0;

  rule.down.state_dc = TRUE;
  rule.down.state_value = FALSE;
  rule.down.type_dc = TRUE;
  rule.down.type_value = 0;

  rule.north.state_dc = TRUE;
  rule.north.state_value = FALSE;
  rule.north.type_dc = TRUE;
  rule.north.type_value = 0;

  rule.south.state_dc = TRUE;
  rule.south.state_value = FALSE;
  rule.south.type_dc = TRUE;
  rule.south.type_value = 0;

  rule.east.state_dc = TRUE;
  rule.east.state_value = FALSE;
  rule.east.type_dc = TRUE;
  rule.east.type_value = 0;

  rule.west.state_dc = TRUE;
  rule.west.state_value = FALSE;
  rule.west.type_dc = FALSE;
  rule.west.type_value = 2;

  rule.center.state_dc = TRUE;
  rule.center.state_value = FALSE;
  rule.center.type_dc = FALSE;
  rule.center.type_value = 0;

  // result
  rule.dont_change_state = TRUE;
  rule.result.copyFrom = WEST;

  return rule;
}

struct RuleStruct create_rule_grow_y (void) {
  struct RuleStruct rule;

  rule.valid = TRUE;
  rule.type = GROWTH;

  // precondition
  rule.up.state_dc = TRUE;
  rule.up.state_value = FALSE;
  rule.up.type_dc = TRUE;
  rule.up.type_value = 0;

  rule.down.state_dc = TRUE;
  rule.down.state_value = FALSE;
  rule.down.type_dc = TRUE;
  rule.down.type_value = 0;

  rule.north.state_dc = TRUE;
  rule.north.state_value = FALSE;
  rule.north.type_dc = FALSE;
  rule.north.type_value = 3;

  rule.south.state_dc = TRUE;
  rule.south.state_value = FALSE;
  rule.south.type_dc = TRUE;
  rule.south.type_value = 0;

  rule.east.state_dc = TRUE;
  rule.east.state_value = FALSE;
  rule.east.type_dc = TRUE;
  rule.east.type_value = 0;

  rule.west.state_dc = TRUE;
  rule.west.state_value = FALSE;
  rule.west.type_dc = TRUE;
  rule.west.type_value = 0;

  rule.center.state_dc = TRUE;
  rule.center.state_value = FALSE;
  rule.center.type_dc = FALSE;
  rule.center.type_value = 0;

  // result
  rule.dont_change_state = TRUE;
  rule.result.copyFrom = NORTH;

  return rule;
}

struct RuleStruct create_rule_change (void) {
  struct RuleStruct rule;

  rule.valid = TRUE;
  rule.type = CHANGE;

  // precondition
  rule.up.state_dc = TRUE;
  rule.up.state_value = FALSE;
  rule.up.type_dc = TRUE;
  rule.up.type_value = 0;

  rule.down.state_dc = TRUE;
  rule.down.state_value = FALSE;
  rule.down.type_dc = TRUE;
  rule.down.type_value = 0;

  rule.north.state_dc = TRUE;
  rule.north.state_value = FALSE;
  rule.north.type_dc = TRUE;
  rule.north.type_value = 0;

  rule.south.state_dc = TRUE;
  rule.south.state_value = FALSE;
  rule.south.type_dc = TRUE;
  rule.south.type_value = 0;

  rule.east.state_dc = TRUE;
  rule.east.state_value = FALSE;
  rule.east.type_dc = FALSE;
  rule.east.type_value = 2;

  rule.west.state_dc = TRUE;
  rule.west.state_value = FALSE;
  rule.west.type_dc = FALSE;
  rule.west.type_value = 2;

  rule.center.state_dc = TRUE;
  rule.center.state_value = FALSE;
  rule.center.type_dc = FALSE;
  rule.center.type_value = 1;

  // result
  rule.dont_change_state = FALSE;
  rule.result.change.type = 3;
  rule.result.change.state = 1;

  return rule;
}

struct RuleStruct create_rule_empty (void) {
  struct RuleStruct rule;

  rule.valid = FALSE;

  return rule;
}

struct RuleStruct create_rule_change_a (void) {
  struct RuleStruct rule;

  rule.valid = TRUE;
  rule.type = CHANGE;

  // precondition
  rule.up.state_dc = TRUE;
  rule.up.state_value = FALSE;
  rule.up.type_dc = TRUE;
  rule.up.type_value = 0;

  rule.down.state_dc = TRUE;
  rule.down.state_value = FALSE;
  rule.down.type_dc = TRUE;
  rule.down.type_value = 0;

  rule.north.state_dc = TRUE;
  rule.north.state_value = FALSE;
  rule.north.type_dc = FALSE;
  rule.north.type_value = 2;

  rule.south.state_dc = TRUE;
  rule.south.state_value = FALSE;
  rule.south.type_dc = FALSE;
  rule.south.type_value = 0;

  rule.east.state_dc = TRUE;
  rule.east.state_value = FALSE;
  rule.east.type_dc = TRUE;
  rule.east.type_value = 0;

  rule.west.state_dc = TRUE;
  rule.west.state_value = FALSE;
  rule.west.type_dc = TRUE;
  rule.west.type_value = 0;

  rule.center.state_dc = TRUE;
  rule.center.state_value = FALSE;
  rule.center.type_dc = TRUE;
  rule.center.type_value = 0;

  // result
  rule.dont_change_state = TRUE;
  rule.result.change.type = 1;
  rule.result.change.state = 0;

  return rule;
}

struct RuleStruct create_rule_change_b (voidr) {
  struct RuleStruct rule;

  rule.valid = TRUE;
  rule.type = CHANGE;

  // precondition
  rule.up.state_dc = TRUE;
  rule.up.state_value = FALSE;
  rule.up.type_dc = TRUE;
  rule.up.type_value = 0;

  rule.down.state_dc = TRUE;
  rule.down.state_value = FALSE;
  rule.down.type_dc = TRUE;
  rule.down.type_value = 0;

  rule.north.state_dc = TRUE;
  rule.north.state_value = FALSE;
  rule.north.type_dc = TRUE;
  rule.north.type_value = 0;

  rule.south.state_dc = TRUE;
  rule.south.state_value = FALSE;
  rule.south.type_dc = FALSE;
  rule.south.type_value = 2;

  rule.east.state_dc = TRUE;
  rule.east.state_value = FALSE;
  rule.east.type_dc = TRUE;
  rule.east.type_value = 0;

  rule.west.state_dc = TRUE;
  rule.west.state_value = FALSE;
  rule.west.type_dc = FALSE;
  rule.west.type_value = 1;

  rule.center.state_dc = TRUE;
  rule.center.state_value = FALSE;
  rule.center.type_dc = TRUE;
  rule.center.type_value = 0;

  // result
  rule.dont_change_state = TRUE;
  rule.result.change.type = 0;
  rule.result.change.state = 0;

  return rule;
}

struct RuleStruct create_rule_grow_north (void) {
  struct RuleStruct rule;

  rule.valid = TRUE;
  rule.type = GROWTH;

  // precondition
  rule.up.state_dc = TRUE;
  rule.up.state_value = FALSE;
  rule.up.type_dc = TRUE;
  rule.up.type_value = 0;

  rule.down.state_dc = TRUE;
  rule.down.state_value = FALSE;
  rule.down.type_dc = TRUE;
  rule.down.type_value = 0;

  rule.north.state_dc = TRUE;
  rule.north.state_value = FALSE;
  rule.north.type_dc = TRUE;
  rule.north.type_value = 0;

  rule.south.state_dc = TRUE;
  rule.south.state_value = FALSE;
  rule.south.type_dc = TRUE;
  rule.south.type_value = 0;

  rule.east.state_dc = TRUE;
  rule.east.state_value = FALSE;
  rule.east.type_dc = TRUE;
  rule.east.type_value = 0;

  rule.west.state_dc = TRUE;
  rule.west.state_value = FALSE;
  rule.west.type_dc = TRUE;
  rule.west.type_value = 0;

  rule.center.state_dc = TRUE;
  rule.center.state_value = FALSE;
  rule.center.type_dc = FALSE;
  rule.center.type_value = 0;

  // result
  rule.dont_change_state = TRUE;
  rule.result.copyFrom = NORTH;

  return rule;
}

struct RuleStruct create_rule_grow_south (void) {
  struct RuleStruct rule;

  rule.valid = TRUE;
  rule.type = GROWTH;

  // precondition
  rule.up.state_dc = TRUE;
  rule.up.state_value = FALSE;
  rule.up.type_dc = TRUE;
  rule.up.type_value = 0;

  rule.down.state_dc = TRUE;
  rule.down.state_value = FALSE;
  rule.down.type_dc = TRUE;
  rule.down.type_value = 0;

  rule.north.state_dc = TRUE;
  rule.north.state_value = FALSE;
  rule.north.type_dc = TRUE;
  rule.north.type_value = 0;

  rule.south.state_dc = TRUE;
  rule.south.state_value = FALSE;
  rule.south.type_dc = TRUE;
  rule.south.type_value = 0;

  rule.east.state_dc = TRUE;
  rule.east.state_value = FALSE;
  rule.east.type_dc = TRUE;
  rule.east.type_value = 0;

  rule.west.state_dc = TRUE;
  rule.west.state_value = FALSE;
  rule.west.type_dc = TRUE;
  rule.west.type_value = 0;

  rule.center.state_dc = TRUE;
  rule.center.state_value = FALSE;
  rule.center.type_dc = FALSE;
  rule.center.type_value = 0;

  // result
  rule.dont_change_state = TRUE;
  rule.result.copyFrom = SOUTH;

  return rule;
}

struct RuleStruct create_rule_grow_east (void) {
  struct RuleStruct rule;

  rule.valid = TRUE;
  rule.type = GROWTH;

  // precondition 
  rule.up.state_dc = TRUE;
  rule.up.state_value = FALSE;
  rule.up.type_dc = TRUE;
  rule.up.type_value = 0;

  rule.down.state_dc = TRUE;
  rule.down.state_value = FALSE;
  rule.down.type_dc = TRUE;
  rule.down.type_value = 0;

  rule.north.state_dc = TRUE;
  rule.north.state_value = FALSE;
  rule.north.type_dc = TRUE;
  rule.north.type_value = 0;

  rule.south.state_dc = TRUE;
  rule.south.state_value = FALSE;
  rule.south.type_dc = TRUE;
  rule.south.type_value = 0;

  rule.east.state_dc = TRUE;
  rule.east.state_value = FALSE;
  rule.east.type_dc = TRUE;
  rule.east.type_value = 0;

  rule.west.state_dc = TRUE;
  rule.west.state_value = FALSE;
  rule.west.type_dc = TRUE;
  rule.west.type_value = 0;

  rule.center.state_dc = TRUE;
  rule.center.state_value = FALSE;
  rule.center.type_dc = FALSE;
  rule.center.type_value = 0;

  // result
  rule.dont_change_state = TRUE;
  rule.result.copyFrom = EAST;

  return rule;
}

struct RuleStruct create_rule_grow_west (void) {
  struct RuleStruct rule;

  rule.valid = TRUE;
  rule.type = GROWTH;

  // precondition
  rule.up.state_dc = TRUE;
  rule.up.state_value = FALSE;
  rule.up.type_dc = TRUE;
  rule.up.type_value = 0;

  rule.down.state_dc = TRUE;
  rule.down.state_value = FALSE;
  rule.down.type_dc = TRUE;
  rule.down.type_value = 0;

  rule.north.state_dc = TRUE;
  rule.north.state_value = FALSE;
  rule.north.type_dc = TRUE;
  rule.north.type_value = 0;

  rule.south.state_dc = TRUE;
  rule.south.state_value = FALSE;
  rule.south.type_dc = TRUE;
  rule.south.type_value = 0;

  rule.east.state_dc = TRUE;
  rule.east.state_value = FALSE;
  rule.east.type_dc = TRUE;
  rule.east.type_value = 0;
  rule.west.state_dc = TRUE;
  rule.west.state_value = FALSE;
  rule.west.type_dc = TRUE;
  rule.west.type_value = 0;

  rule.center.state_dc = TRUE;
  rule.center.state_value = FALSE;
  rule.center.type_dc = FALSE;
  rule.center.type_value = 0;

  // result
  rule.dont_change_state = TRUE;
  rule.result.copyFrom = WEST;

  return rule;
}

struct RuleStruct create_rule_grow_west_1 (void) {
  struct RuleStruct rule;

  rule.valid = TRUE;
  rule.type = CHANGE;

  // precondition
  rule.up.state_dc = TRUE;
  rule.up.state_value = FALSE;
  rule.up.type_dc = TRUE;
  rule.up.type_value = 0;

  rule.down.state_dc = TRUE;
  rule.down.state_value = FALSE;
  rule.down.type_dc = TRUE;
  rule.down.type_value = 0;

  rule.north.state_dc = TRUE;
  rule.north.state_value = FALSE;
  rule.north.type_dc = TRUE;
  rule.north.type_value = 0;

  rule.south.state_dc = TRUE;
  rule.south.state_value = FALSE;
  rule.south.type_dc = TRUE;
  rule.south.type_value = 0;

  rule.east.state_dc = TRUE;
  rule.east.state_value = FALSE;
  rule.east.type_dc = TRUE;
  rule.east.type_value = 0;

  rule.west.state_dc = TRUE;
  rule.west.state_value = FALSE;
  rule.west.type_dc = FALSE;
  rule.west.type_value = 1;

  rule.center.state_dc = TRUE;
  rule.center.state_value = FALSE;
  rule.center.type_dc = FALSE;
  rule.center.type_value = 0;

  // result
  rule.dont_change_state = TRUE;
  rule.result.change.type = 1;
  rule.result.change.state = 0;

  return rule;
}

struct RuleStruct create_rule_grow_north_1 (void) {
  struct RuleStruct rule;

  rule.valid = TRUE;
  rule.type = CHANGE;

  // precondition
  rule.up.state_dc = TRUE;
  rule.up.state_value = FALSE;
  rule.up.type_dc = TRUE;
  rule.up.type_value = 0;

  rule.down.state_dc = TRUE;
  rule.down.state_value = FALSE;
  rule.down.type_dc = TRUE;
  rule.down.type_value = 0;

  rule.north.state_dc = TRUE;
  rule.north.state_value = FALSE;
  rule.north.type_dc = FALSE;
  rule.north.type_value = 1;

  rule.south.state_dc = TRUE;
  rule.south.state_value = FALSE;
  rule.south.type_dc = TRUE;
  rule.south.type_value = 0;

  rule.east.state_dc = TRUE;
  rule.east.state_value = FALSE;
  rule.east.type_dc = TRUE;
  rule.east.type_value = 0;

  rule.west.state_dc = TRUE;
  rule.west.state_value = FALSE;
  rule.west.type_dc = TRUE;
  rule.west.type_value = 0;

  rule.center.state_dc = TRUE;
  rule.center.state_value = FALSE;
  rule.center.type_dc = FALSE;
  rule.center.type_value = 0;

  // result
  rule.dont_change_state = TRUE;
  rule.result.change.type = 1;
  rule.result.change.state = 0;

  return rule;
}
struct RuleStruct create_rule_grow_east_1 (void) {
  struct RuleStruct rule;

  rule.valid = TRUE;
  rule.type = CHANGE;

  // precondition
  rule.up.state_dc = TRUE;
  rule.up.state_value = FALSE;
  rule.up.type_dc = TRUE;
  rule.up.type_value = 0;

  rule.down.state_dc = TRUE;
  rule.down.state_value = FALSE;
  rule.down.type_dc = TRUE;
  rule.down.type_value = 0;

  rule.north.state_dc = TRUE;
  rule.north.state_value = FALSE;
  rule.north.type_dc = TRUE;
  rule.north.type_value = 0;

  rule.south.state_dc = TRUE;
  rule.south.state_value = FALSE;
  rule.south.type_dc = TRUE;
  rule.south.type_value = 0;

  rule.east.state_dc = TRUE;
  rule.east.state_value = FALSE;
  rule.east.type_dc = FALSE;
  rule.east.type_value = 1;

  rule.west.state_dc = TRUE;
  rule.west.state_value = FALSE;
  rule.west.type_dc = TRUE;
  rule.west.type_value = 0;

  rule.center.state_dc = TRUE;
  rule.center.state_value = FALSE;
  rule.center.type_dc = FALSE;
  rule.center.type_value = 0;

  // result
  rule.dont_change_state = TRUE;
  rule.result.change.type = 1;
  rule.result.change.state = 0;

  return rule;
}

struct RuleStruct create_rule_grow_south_1 (void) {
  struct RuleStruct rule;

  rule.valid = TRUE;
  rule.type = CHANGE;

  // precondition
  rule.up.state_dc = TRUE;
  rule.up.state_value = FALSE;
  rule.up.type_dc = TRUE;
  rule.up.type_value = 0;

  rule.down.state_dc = TRUE;
  rule.down.state_value = FALSE;
  rule.down.type_dc = TRUE;
  rule.down.type_value = 0;

  rule.north.state_dc = TRUE;
  rule.north.state_value = FALSE;
  rule.north.type_dc = TRUE;
  rule.north.type_value = 0;

  rule.south.state_dc = TRUE;
  rule.south.state_value = FALSE;
  rule.south.type_dc = FALSE;
  rule.south.type_value = 1;

  rule.east.state_dc = TRUE;
  rule.east.state_value = FALSE;
  rule.east.type_dc = TRUE;
  rule.east.type_value = 0;

  rule.west.state_dc = TRUE;
  rule.west.state_value = FALSE;
  rule.west.type_dc = TRUE;
  rule.west.type_value = 0;

  rule.center.state_dc = TRUE;
  rule.center.state_value = FALSE;
  rule.center.type_dc = FALSE;
  rule.center.type_value = 0;

  // result
  rule.dont_change_state = TRUE;
  rule.result.change.type = 1;
  rule.result.change.state = 0;

  return rule;
}
struct RuleStruct create_rule_grow_west_2 (void) {
  struct RuleStruct rule;

  rule.valid = TRUE;
  rule.type = CHANGE;

  // precondition
  rule.up.state_dc = TRUE;
  rule.up.state_value = FALSE;
  rule.up.type_dc = TRUE;
  rule.up.type_value = 0;

  rule.down.state_dc = TRUE;
  rule.down.state_value = FALSE;
  rule.down.type_dc = TRUE;
  rule.down.type_value = 0;

  rule.north.state_dc = TRUE;
  rule.north.state_value = FALSE;
  rule.north.type_dc = TRUE;
  rule.north.type_value = 0;

  rule.south.state_dc = TRUE;
  rule.south.state_value = FALSE;
  rule.south.type_dc = TRUE;
  rule.south.type_value = 0;

  rule.east.state_dc = TRUE;
  rule.east.state_value = FALSE;
  rule.east.type_dc = TRUE;
  rule.east.type_value = 0;

  rule.west.state_dc = TRUE;
  rule.west.state_value = FALSE;
  rule.west.type_dc = FALSE;
  rule.west.type_value = 2;

  rule.center.state_dc = TRUE;
  rule.center.state_value = FALSE;
  rule.center.type_dc = FALSE;
  rule.center.type_value = 0;

  // result
  rule.dont_change_state = TRUE;
  rule.result.change.type = 2;
  rule.result.change.state = 0;

  return rule;
}

struct RuleStruct create_rule_grow_north_2 (void) {
  struct RuleStruct rule;

  rule.valid = TRUE;
  rule.type = CHANGE;

  // precondition
  rule.up.state_dc = TRUE;
  rule.up.state_value = FALSE;
  rule.up.type_dc = TRUE;
  rule.up.type_value = 0;

  rule.down.state_dc = TRUE;
  rule.down.state_value = FALSE;
  rule.down.type_dc = TRUE;
  rule.down.type_value = 0;

  rule.north.state_dc = TRUE;
  rule.north.state_value = FALSE;
  rule.north.type_dc = FALSE;
  rule.north.type_value = 2;

  rule.south.state_dc = TRUE;
  rule.south.state_value = FALSE;
  rule.south.type_dc = TRUE;
  rule.south.type_value = 0;

  rule.east.state_dc = TRUE;
  rule.east.state_value = FALSE;
  rule.east.type_dc = TRUE;
  rule.east.type_value = 0;

  rule.west.state_dc = TRUE;
  rule.west.state_value = FALSE;
  rule.west.type_dc = TRUE;
  rule.west.type_value = 0;

  rule.center.state_dc = TRUE;
  rule.center.state_value = FALSE;
  rule.center.type_dc = FALSE;
  rule.center.type_value = 0;

  // result
  rule.dont_change_state = TRUE;
  rule.result.change.type = 2;
  rule.result.change.state = 0;

  return rule;
}
struct RuleStruct create_rule_grow_east_2 (void) {
  struct RuleStruct rule;

  rule.valid = TRUE;
  rule.type = CHANGE;

  // precondition
  rule.up.state_dc = TRUE;
  rule.up.state_value = FALSE;
  rule.up.type_dc = TRUE;
  rule.up.type_value = 0;

  rule.down.state_dc = TRUE;
  rule.down.state_value = FALSE;
  rule.down.type_dc = TRUE;
  rule.down.type_value = 0;

  rule.north.state_dc = TRUE;
  rule.north.state_value = FALSE;
  rule.north.type_dc = TRUE;
  rule.north.type_value = 0;

  rule.south.state_dc = TRUE;
  rule.south.state_value = FALSE;
  rule.south.type_dc = TRUE;
  rule.south.type_value = 0;

  rule.east.state_dc = TRUE;
  rule.east.state_value = FALSE;
  rule.east.type_dc = FALSE;
  rule.east.type_value = 2;

  rule.west.state_dc = TRUE;
  rule.west.state_value = FALSE;
  rule.west.type_dc = TRUE;
  rule.west.type_value = 0;

  rule.center.state_dc = TRUE;
  rule.center.state_value = FALSE;
  rule.center.type_dc = FALSE;
  rule.center.type_value = 0;

  // result
  rule.dont_change_state = TRUE;
  rule.result.change.type = 2;
  rule.result.change.state = 0;

  return rule;
}

struct RuleStruct create_rule_grow_south_2 (void) {
  struct RuleStruct rule;

  rule.valid = TRUE;
  rule.type = CHANGE;

  // precondition
  rule.up.state_dc = TRUE;
  rule.up.state_value = FALSE;
  rule.up.type_dc = TRUE;
  rule.up.type_value = 0;

  rule.down.state_dc = TRUE;
  rule.down.state_value = FALSE;
  rule.down.type_dc = TRUE;
  rule.down.type_value = 0;

  rule.north.state_dc = TRUE;
  rule.north.state_value = FALSE;
  rule.north.type_dc = TRUE;
  rule.north.type_value = 0;

  rule.south.state_dc = TRUE;
  rule.south.state_value = FALSE;
  rule.south.type_dc = FALSE;
  rule.south.type_value = 2;

  rule.east.state_dc = TRUE;
  rule.east.state_value = FALSE;
  rule.east.type_dc = TRUE;
  rule.east.type_value = 0;

  rule.west.state_dc = TRUE;
  rule.west.state_value = FALSE;
  rule.west.type_dc = TRUE;
  rule.west.type_value = 0;

  rule.center.state_dc = TRUE;
  rule.center.state_value = FALSE;
  rule.center.type_dc = FALSE;
  rule.center.type_value = 0;

  // result
  rule.dont_change_state = TRUE;
  rule.result.change.type = 2;
  rule.result.change.state = 0;

  return rule;
}

struct RuleStruct create_rule_change_a_1 (void) {
  struct RuleStruct rule;

  rule.valid = TRUE;
  rule.type = CHANGE;

  // precondition
  rule.up.state_dc = TRUE;
  rule.up.state_value = FALSE;
  rule.up.type_dc = TRUE;
  rule.up.type_value = 0;

  rule.down.state_dc = TRUE;
  rule.down.state_value = FALSE;
  rule.down.type_dc = TRUE;
  rule.down.type_value = 0;

  rule.north.state_dc = TRUE;
  rule.north.state_value = FALSE;
  rule.north.type_dc = FALSE;
  rule.north.type_value = 2;

  rule.south.state_dc = TRUE;
  rule.south.state_value = FALSE;
  rule.south.type_dc = FALSE;
  rule.south.type_value = 0;

  rule.east.state_dc = TRUE;
  rule.east.state_value = FALSE;
  rule.east.type_dc = TRUE;
  rule.east.type_value = 0;

  rule.west.state_dc = TRUE;
  rule.west.state_value = FALSE;
  rule.west.type_dc = TRUE;
  rule.west.type_value = 0;

  rule.center.state_dc = TRUE;
  rule.center.state_value = FALSE;
  rule.center.type_dc = FALSE;
  rule.center.type_value = 1;

  // result
  rule.dont_change_state = TRUE;
  rule.result.change.type = 1;
  rule.result.change.state = 0;

  return rule;
}

struct RuleStruct create_rule_change_a_2 (void) {
  struct RuleStruct rule;

  rule.valid = TRUE;
  rule.type = CHANGE;

  // precondition
  rule.up.state_dc = TRUE;
  rule.up.state_value = FALSE;
  rule.up.type_dc = TRUE;
  rule.up.type_value = 0;

  rule.down.state_dc = TRUE;
  rule.down.state_value = FALSE;
  rule.down.type_dc = TRUE;
  rule.down.type_value = 0;

  rule.north.state_dc = TRUE;
  rule.north.state_value = FALSE;
  rule.north.type_dc = FALSE;
  rule.north.type_value = 2;

  rule.south.state_dc = TRUE;
  rule.south.state_value = FALSE;
  rule.south.type_dc = FALSE;
  rule.south.type_value = 0;

  rule.east.state_dc = TRUE;
  rule.east.state_value = FALSE;
  rule.east.type_dc = TRUE;
  rule.east.type_value = 0;

  rule.west.state_dc = TRUE;
  rule.west.state_value = FALSE;
  rule.west.type_dc = TRUE;
  rule.west.type_value = 0;

  rule.center.state_dc = TRUE;
  rule.center.state_value = FALSE;
  rule.center.type_dc = FALSE;
  rule.center.type_value = 2;

  // result
  rule.dont_change_state = TRUE;
  rule.result.change.type = 1;
  rule.result.change.state = 0;

  return rule;
}

struct RuleStruct create_rule_change_b_1 (voidr) {
  struct RuleStruct rule;

  rule.valid = TRUE;
  rule.type = CHANGE;

  // precondition
  rule.up.state_dc = TRUE;
  rule.up.state_value = FALSE;
  rule.up.type_dc = TRUE;
  rule.up.type_value = 0;

  rule.down.state_dc = TRUE;
  rule.down.state_value = FALSE;
  rule.down.type_dc = TRUE;
  rule.down.type_value = 0;

  rule.north.state_dc = TRUE;
  rule.north.state_value = FALSE;
  rule.north.type_dc = TRUE;
  rule.north.type_value = 0;

  rule.south.state_dc = TRUE;
  rule.south.state_value = FALSE;
  rule.south.type_dc = FALSE;
  rule.south.type_value = 2;

  rule.east.state_dc = TRUE;
  rule.east.state_value = FALSE;
  rule.east.type_dc = TRUE;
  rule.east.type_value = 0;

  rule.west.state_dc = TRUE;
  rule.west.state_value = FALSE;
  rule.west.type_dc = FALSE;
  rule.west.type_value = 1;

  rule.center.state_dc = TRUE;
  rule.center.state_value = FALSE;
  rule.center.type_dc = FALSE;
  rule.center.type_value = 1;

  // result
  rule.dont_change_state = TRUE;
  rule.result.change.type = 0;
  rule.result.change.state = 0;

  return rule;
}

struct RuleStruct create_rule_change_b_2 (voidr) {
  struct RuleStruct rule;

  rule.valid = TRUE;
  rule.type = CHANGE;

  // precondition
  rule.up.state_dc = TRUE;
  rule.up.state_value = FALSE;
  rule.up.type_dc = TRUE;
  rule.up.type_value = 0;

  rule.down.state_dc = TRUE;
  rule.down.state_value = FALSE;
  rule.down.type_dc = TRUE;
  rule.down.type_value = 0;

  rule.north.state_dc = TRUE;
  rule.north.state_value = FALSE;
  rule.north.type_dc = TRUE;
  rule.north.type_value = 0;

  rule.south.state_dc = TRUE;
  rule.south.state_value = FALSE;
  rule.south.type_dc = FALSE;
  rule.south.type_value = 2;

  rule.east.state_dc = TRUE;
  rule.east.state_value = FALSE;
  rule.east.type_dc = TRUE;
  rule.east.type_value = 0;

  rule.west.state_dc = TRUE;
  rule.west.state_value = FALSE;
  rule.west.type_dc = FALSE;
  rule.west.type_value = 1;

  rule.center.state_dc = TRUE;
  rule.center.state_value = FALSE;
  rule.center.type_dc = FALSE;
  rule.center.type_value = 2;

  // result
  rule.dont_change_state = TRUE;
  rule.result.change.type = 0;
  rule.result.change.state = 0;

  return rule;
}

