#include "testrules.h"

struct RuleStruct create_rule_grow_x (void) {
  struct RuleStruct rule;

  rule.valid = true;
  rule.type = GROWTH;

  // precondition
  rule.up.state_dc = true;
  rule.up.state_value = false;
  rule.up.type_dc = true;
  rule.up.type_value = 0;

  rule.down.state_dc = true;
  rule.down.state_value = false;
  rule.down.type_dc = true;
  rule.down.type_value = 0;

  rule.north.state_dc = true;
  rule.north.state_value = false;
  rule.north.type_dc = true;
  rule.north.type_value = 0;

  rule.south.state_dc = true;
  rule.south.state_value = false;
  rule.south.type_dc = true;
  rule.south.type_value = 0;

  rule.east.state_dc = true;
  rule.east.state_value = false;
  rule.east.type_dc = true;
  rule.east.type_value = 0;

  rule.west.state_dc = true;
  rule.west.state_value = false;
  rule.west.type_dc = false;
  rule.west.type_value = 2;

  rule.center.state_dc = true;
  rule.center.state_value = false;
  rule.center.type_dc = false;
  rule.center.type_value = 0;

  // result
  rule.dont_change_state = true;
  rule.result.copyFrom = WEST;

  return rule;
}

struct RuleStruct create_rule_grow_y (void) {
  struct RuleStruct rule;

  rule.valid = true;
  rule.type = GROWTH;

  // precondition
  rule.up.state_dc = true;
  rule.up.state_value = false;
  rule.up.type_dc = true;
  rule.up.type_value = 0;

  rule.down.state_dc = true;
  rule.down.state_value = false;
  rule.down.type_dc = true;
  rule.down.type_value = 0;

  rule.north.state_dc = true;
  rule.north.state_value = false;
  rule.north.type_dc = false;
  rule.north.type_value = 3;

  rule.south.state_dc = true;
  rule.south.state_value = false;
  rule.south.type_dc = true;
  rule.south.type_value = 0;

  rule.east.state_dc = true;
  rule.east.state_value = false;
  rule.east.type_dc = true;
  rule.east.type_value = 0;

  rule.west.state_dc = true;
  rule.west.state_value = false;
  rule.west.type_dc = true;
  rule.west.type_value = 0;

  rule.center.state_dc = true;
  rule.center.state_value = false;
  rule.center.type_dc = false;
  rule.center.type_value = 0;

  // result
  rule.dont_change_state = true;
  rule.result.copyFrom = NORTH;

  return rule;
}

struct RuleStruct create_rule_change (void) {
  struct RuleStruct rule;

  rule.valid = true;
  rule.type = CHANGE;

  // precondition
  rule.up.state_dc = true;
  rule.up.state_value = false;
  rule.up.type_dc = true;
  rule.up.type_value = 0;

  rule.down.state_dc = true;
  rule.down.state_value = false;
  rule.down.type_dc = true;
  rule.down.type_value = 0;

  rule.north.state_dc = true;
  rule.north.state_value = false;
  rule.north.type_dc = true;
  rule.north.type_value = 0;

  rule.south.state_dc = true;
  rule.south.state_value = false;
  rule.south.type_dc = true;
  rule.south.type_value = 0;

  rule.east.state_dc = true;
  rule.east.state_value = false;
  rule.east.type_dc = false;
  rule.east.type_value = 2;

  rule.west.state_dc = true;
  rule.west.state_value = false;
  rule.west.type_dc = false;
  rule.west.type_value = 2;

  rule.center.state_dc = true;
  rule.center.state_value = false;
  rule.center.type_dc = false;
  rule.center.type_value = 1;

  // result
  rule.dont_change_state = false;
  rule.result.change.type = 3;
  rule.result.change.state = 1;

  return rule;
}

struct RuleStruct create_rule_empty (void) {
  struct RuleStruct rule;

  rule.valid = false;

  return rule;
}

struct RuleStruct create_rule_change_a (void) {
  struct RuleStruct rule;

  rule.valid = true;
  rule.type = CHANGE;

  // precondition
  rule.up.state_dc = true;
  rule.up.state_value = false;
  rule.up.type_dc = true;
  rule.up.type_value = 0;

  rule.down.state_dc = true;
  rule.down.state_value = false;
  rule.down.type_dc = true;
  rule.down.type_value = 0;

  rule.north.state_dc = true;
  rule.north.state_value = false;
  rule.north.type_dc = false;
  rule.north.type_value = 2;

  rule.south.state_dc = true;
  rule.south.state_value = false;
  rule.south.type_dc = false;
  rule.south.type_value = 0;

  rule.east.state_dc = true;
  rule.east.state_value = false;
  rule.east.type_dc = true;
  rule.east.type_value = 0;

  rule.west.state_dc = true;
  rule.west.state_value = false;
  rule.west.type_dc = true;
  rule.west.type_value = 0;

  rule.center.state_dc = true;
  rule.center.state_value = false;
  rule.center.type_dc = true;
  rule.center.type_value = 0;

  // result
  rule.dont_change_state = true;
  rule.result.change.type = 1;
  rule.result.change.state = 0;

  return rule;
}

struct RuleStruct create_rule_change_b (void) {
  struct RuleStruct rule;

  rule.valid = true;
  rule.type = CHANGE;

  // precondition
  rule.up.state_dc = true;
  rule.up.state_value = false;
  rule.up.type_dc = true;
  rule.up.type_value = 0;

  rule.down.state_dc = true;
  rule.down.state_value = false;
  rule.down.type_dc = true;
  rule.down.type_value = 0;

  rule.north.state_dc = true;
  rule.north.state_value = false;
  rule.north.type_dc = true;
  rule.north.type_value = 0;

  rule.south.state_dc = true;
  rule.south.state_value = false;
  rule.south.type_dc = false;
  rule.south.type_value = 2;

  rule.east.state_dc = true;
  rule.east.state_value = false;
  rule.east.type_dc = true;
  rule.east.type_value = 0;

  rule.west.state_dc = true;
  rule.west.state_value = false;
  rule.west.type_dc = false;
  rule.west.type_value = 1;

  rule.center.state_dc = true;
  rule.center.state_value = false;
  rule.center.type_dc = true;
  rule.center.type_value = 0;

  // result
  rule.dont_change_state = true;
  rule.result.change.type = 0;
  rule.result.change.state = 0;

  return rule;
}

struct RuleStruct create_rule_grow_north (void) {
  struct RuleStruct rule;

  rule.valid = true;
  rule.type = GROWTH;

  // precondition
  rule.up.state_dc = true;
  rule.up.state_value = false;
  rule.up.type_dc = true;
  rule.up.type_value = 0;

  rule.down.state_dc = true;
  rule.down.state_value = false;
  rule.down.type_dc = true;
  rule.down.type_value = 0;

  rule.north.state_dc = true;
  rule.north.state_value = false;
  rule.north.type_dc = true;
  rule.north.type_value = 0;

  rule.south.state_dc = true;
  rule.south.state_value = false;
  rule.south.type_dc = true;
  rule.south.type_value = 0;

  rule.east.state_dc = true;
  rule.east.state_value = false;
  rule.east.type_dc = true;
  rule.east.type_value = 0;

  rule.west.state_dc = true;
  rule.west.state_value = false;
  rule.west.type_dc = true;
  rule.west.type_value = 0;

  rule.center.state_dc = true;
  rule.center.state_value = false;
  rule.center.type_dc = false;
  rule.center.type_value = 0;

  // result
  rule.dont_change_state = true;
  rule.result.copyFrom = NORTH;

  return rule;
}

struct RuleStruct create_rule_grow_south (void) {
  struct RuleStruct rule;

  rule.valid = true;
  rule.type = GROWTH;

  // precondition
  rule.up.state_dc = true;
  rule.up.state_value = false;
  rule.up.type_dc = true;
  rule.up.type_value = 0;

  rule.down.state_dc = true;
  rule.down.state_value = false;
  rule.down.type_dc = true;
  rule.down.type_value = 0;

  rule.north.state_dc = true;
  rule.north.state_value = false;
  rule.north.type_dc = true;
  rule.north.type_value = 0;

  rule.south.state_dc = true;
  rule.south.state_value = false;
  rule.south.type_dc = true;
  rule.south.type_value = 0;

  rule.east.state_dc = true;
  rule.east.state_value = false;
  rule.east.type_dc = true;
  rule.east.type_value = 0;

  rule.west.state_dc = true;
  rule.west.state_value = false;
  rule.west.type_dc = true;
  rule.west.type_value = 0;

  rule.center.state_dc = true;
  rule.center.state_value = false;
  rule.center.type_dc = false;
  rule.center.type_value = 0;

  // result
  rule.dont_change_state = true;
  rule.result.copyFrom = SOUTH;

  return rule;
}

struct RuleStruct create_rule_grow_east (void) {
  struct RuleStruct rule;

  rule.valid = true;
  rule.type = GROWTH;

  // precondition 
  rule.up.state_dc = true;
  rule.up.state_value = false;
  rule.up.type_dc = true;
  rule.up.type_value = 0;

  rule.down.state_dc = true;
  rule.down.state_value = false;
  rule.down.type_dc = true;
  rule.down.type_value = 0;

  rule.north.state_dc = true;
  rule.north.state_value = false;
  rule.north.type_dc = true;
  rule.north.type_value = 0;

  rule.south.state_dc = true;
  rule.south.state_value = false;
  rule.south.type_dc = true;
  rule.south.type_value = 0;

  rule.east.state_dc = true;
  rule.east.state_value = false;
  rule.east.type_dc = true;
  rule.east.type_value = 0;

  rule.west.state_dc = true;
  rule.west.state_value = false;
  rule.west.type_dc = true;
  rule.west.type_value = 0;

  rule.center.state_dc = true;
  rule.center.state_value = false;
  rule.center.type_dc = false;
  rule.center.type_value = 0;

  // result
  rule.dont_change_state = true;
  rule.result.copyFrom = EAST;

  return rule;
}

struct RuleStruct create_rule_grow_west (void) {
  struct RuleStruct rule;

  rule.valid = true;
  rule.type = GROWTH;

  // precondition
  rule.up.state_dc = true;
  rule.up.state_value = false;
  rule.up.type_dc = true;
  rule.up.type_value = 0;

  rule.down.state_dc = true;
  rule.down.state_value = false;
  rule.down.type_dc = true;
  rule.down.type_value = 0;

  rule.north.state_dc = true;
  rule.north.state_value = false;
  rule.north.type_dc = true;
  rule.north.type_value = 0;

  rule.south.state_dc = true;
  rule.south.state_value = false;
  rule.south.type_dc = true;
  rule.south.type_value = 0;

  rule.east.state_dc = true;
  rule.east.state_value = false;
  rule.east.type_dc = true;
  rule.east.type_value = 0;
  rule.west.state_dc = true;
  rule.west.state_value = false;
  rule.west.type_dc = true;
  rule.west.type_value = 0;

  rule.center.state_dc = true;
  rule.center.state_value = false;
  rule.center.type_dc = false;
  rule.center.type_value = 0;

  // result
  rule.dont_change_state = true;
  rule.result.copyFrom = WEST;

  return rule;
}

struct RuleStruct create_rule_grow_west_1 (void) {
  struct RuleStruct rule;

  rule.valid = true;
  rule.type = CHANGE;

  // precondition
  rule.up.state_dc = true;
  rule.up.state_value = false;
  rule.up.type_dc = true;
  rule.up.type_value = 0;

  rule.down.state_dc = true;
  rule.down.state_value = false;
  rule.down.type_dc = true;
  rule.down.type_value = 0;

  rule.north.state_dc = true;
  rule.north.state_value = false;
  rule.north.type_dc = true;
  rule.north.type_value = 0;

  rule.south.state_dc = true;
  rule.south.state_value = false;
  rule.south.type_dc = true;
  rule.south.type_value = 0;

  rule.east.state_dc = true;
  rule.east.state_value = false;
  rule.east.type_dc = true;
  rule.east.type_value = 0;

  rule.west.state_dc = true;
  rule.west.state_value = false;
  rule.west.type_dc = false;
  rule.west.type_value = 1;

  rule.center.state_dc = true;
  rule.center.state_value = false;
  rule.center.type_dc = false;
  rule.center.type_value = 0;

  // result
  rule.dont_change_state = true;
  rule.result.change.type = 1;
  rule.result.change.state = 0;

  return rule;
}

struct RuleStruct create_rule_grow_north_1 (void) {
  struct RuleStruct rule;

  rule.valid = true;
  rule.type = CHANGE;

  // precondition
  rule.up.state_dc = true;
  rule.up.state_value = false;
  rule.up.type_dc = true;
  rule.up.type_value = 0;

  rule.down.state_dc = true;
  rule.down.state_value = false;
  rule.down.type_dc = true;
  rule.down.type_value = 0;

  rule.north.state_dc = true;
  rule.north.state_value = false;
  rule.north.type_dc = false;
  rule.north.type_value = 1;

  rule.south.state_dc = true;
  rule.south.state_value = false;
  rule.south.type_dc = true;
  rule.south.type_value = 0;

  rule.east.state_dc = true;
  rule.east.state_value = false;
  rule.east.type_dc = true;
  rule.east.type_value = 0;

  rule.west.state_dc = true;
  rule.west.state_value = false;
  rule.west.type_dc = true;
  rule.west.type_value = 0;

  rule.center.state_dc = true;
  rule.center.state_value = false;
  rule.center.type_dc = false;
  rule.center.type_value = 0;

  // result
  rule.dont_change_state = true;
  rule.result.change.type = 1;
  rule.result.change.state = 0;

  return rule;
}
struct RuleStruct create_rule_grow_east_1 (void) {
  struct RuleStruct rule;

  rule.valid = true;
  rule.type = CHANGE;

  // precondition
  rule.up.state_dc = true;
  rule.up.state_value = false;
  rule.up.type_dc = true;
  rule.up.type_value = 0;

  rule.down.state_dc = true;
  rule.down.state_value = false;
  rule.down.type_dc = true;
  rule.down.type_value = 0;

  rule.north.state_dc = true;
  rule.north.state_value = false;
  rule.north.type_dc = true;
  rule.north.type_value = 0;

  rule.south.state_dc = true;
  rule.south.state_value = false;
  rule.south.type_dc = true;
  rule.south.type_value = 0;

  rule.east.state_dc = true;
  rule.east.state_value = false;
  rule.east.type_dc = false;
  rule.east.type_value = 1;

  rule.west.state_dc = true;
  rule.west.state_value = false;
  rule.west.type_dc = true;
  rule.west.type_value = 0;

  rule.center.state_dc = true;
  rule.center.state_value = false;
  rule.center.type_dc = false;
  rule.center.type_value = 0;

  // result
  rule.dont_change_state = true;
  rule.result.change.type = 1;
  rule.result.change.state = 0;

  return rule;
}

struct RuleStruct create_rule_grow_south_1 (void) {
  struct RuleStruct rule;

  rule.valid = true;
  rule.type = CHANGE;

  // precondition
  rule.up.state_dc = true;
  rule.up.state_value = false;
  rule.up.type_dc = true;
  rule.up.type_value = 0;

  rule.down.state_dc = true;
  rule.down.state_value = false;
  rule.down.type_dc = true;
  rule.down.type_value = 0;

  rule.north.state_dc = true;
  rule.north.state_value = false;
  rule.north.type_dc = true;
  rule.north.type_value = 0;

  rule.south.state_dc = true;
  rule.south.state_value = false;
  rule.south.type_dc = false;
  rule.south.type_value = 1;

  rule.east.state_dc = true;
  rule.east.state_value = false;
  rule.east.type_dc = true;
  rule.east.type_value = 0;

  rule.west.state_dc = true;
  rule.west.state_value = false;
  rule.west.type_dc = true;
  rule.west.type_value = 0;

  rule.center.state_dc = true;
  rule.center.state_value = false;
  rule.center.type_dc = false;
  rule.center.type_value = 0;

  // result
  rule.dont_change_state = true;
  rule.result.change.type = 1;
  rule.result.change.state = 0;

  return rule;
}
struct RuleStruct create_rule_grow_west_2 (void) {
  struct RuleStruct rule;

  rule.valid = true;
  rule.type = CHANGE;

  // precondition
  rule.up.state_dc = true;
  rule.up.state_value = false;
  rule.up.type_dc = true;
  rule.up.type_value = 0;

  rule.down.state_dc = true;
  rule.down.state_value = false;
  rule.down.type_dc = true;
  rule.down.type_value = 0;

  rule.north.state_dc = true;
  rule.north.state_value = false;
  rule.north.type_dc = true;
  rule.north.type_value = 0;

  rule.south.state_dc = true;
  rule.south.state_value = false;
  rule.south.type_dc = true;
  rule.south.type_value = 0;

  rule.east.state_dc = true;
  rule.east.state_value = false;
  rule.east.type_dc = true;
  rule.east.type_value = 0;

  rule.west.state_dc = true;
  rule.west.state_value = false;
  rule.west.type_dc = false;
  rule.west.type_value = 2;

  rule.center.state_dc = true;
  rule.center.state_value = false;
  rule.center.type_dc = false;
  rule.center.type_value = 0;

  // result
  rule.dont_change_state = true;
  rule.result.change.type = 2;
  rule.result.change.state = 0;

  return rule;
}

struct RuleStruct create_rule_grow_north_2 (void) {
  struct RuleStruct rule;

  rule.valid = true;
  rule.type = CHANGE;

  // precondition
  rule.up.state_dc = true;
  rule.up.state_value = false;
  rule.up.type_dc = true;
  rule.up.type_value = 0;

  rule.down.state_dc = true;
  rule.down.state_value = false;
  rule.down.type_dc = true;
  rule.down.type_value = 0;

  rule.north.state_dc = true;
  rule.north.state_value = false;
  rule.north.type_dc = false;
  rule.north.type_value = 2;

  rule.south.state_dc = true;
  rule.south.state_value = false;
  rule.south.type_dc = true;
  rule.south.type_value = 0;

  rule.east.state_dc = true;
  rule.east.state_value = false;
  rule.east.type_dc = true;
  rule.east.type_value = 0;

  rule.west.state_dc = true;
  rule.west.state_value = false;
  rule.west.type_dc = true;
  rule.west.type_value = 0;

  rule.center.state_dc = true;
  rule.center.state_value = false;
  rule.center.type_dc = false;
  rule.center.type_value = 0;

  // result
  rule.dont_change_state = true;
  rule.result.change.type = 2;
  rule.result.change.state = 0;

  return rule;
}
struct RuleStruct create_rule_grow_east_2 (void) {
  struct RuleStruct rule;

  rule.valid = true;
  rule.type = CHANGE;

  // precondition
  rule.up.state_dc = true;
  rule.up.state_value = false;
  rule.up.type_dc = true;
  rule.up.type_value = 0;

  rule.down.state_dc = true;
  rule.down.state_value = false;
  rule.down.type_dc = true;
  rule.down.type_value = 0;

  rule.north.state_dc = true;
  rule.north.state_value = false;
  rule.north.type_dc = true;
  rule.north.type_value = 0;

  rule.south.state_dc = true;
  rule.south.state_value = false;
  rule.south.type_dc = true;
  rule.south.type_value = 0;

  rule.east.state_dc = true;
  rule.east.state_value = false;
  rule.east.type_dc = false;
  rule.east.type_value = 2;

  rule.west.state_dc = true;
  rule.west.state_value = false;
  rule.west.type_dc = true;
  rule.west.type_value = 0;

  rule.center.state_dc = true;
  rule.center.state_value = false;
  rule.center.type_dc = false;
  rule.center.type_value = 0;

  // result
  rule.dont_change_state = true;
  rule.result.change.type = 2;
  rule.result.change.state = 0;

  return rule;
}

struct RuleStruct create_rule_grow_south_2 (void) {
  struct RuleStruct rule;

  rule.valid = true;
  rule.type = CHANGE;

  // precondition
  rule.up.state_dc = true;
  rule.up.state_value = false;
  rule.up.type_dc = true;
  rule.up.type_value = 0;

  rule.down.state_dc = true;
  rule.down.state_value = false;
  rule.down.type_dc = true;
  rule.down.type_value = 0;

  rule.north.state_dc = true;
  rule.north.state_value = false;
  rule.north.type_dc = true;
  rule.north.type_value = 0;

  rule.south.state_dc = true;
  rule.south.state_value = false;
  rule.south.type_dc = false;
  rule.south.type_value = 2;

  rule.east.state_dc = true;
  rule.east.state_value = false;
  rule.east.type_dc = true;
  rule.east.type_value = 0;

  rule.west.state_dc = true;
  rule.west.state_value = false;
  rule.west.type_dc = true;
  rule.west.type_value = 0;

  rule.center.state_dc = true;
  rule.center.state_value = false;
  rule.center.type_dc = false;
  rule.center.type_value = 0;

  // result
  rule.dont_change_state = true;
  rule.result.change.type = 2;
  rule.result.change.state = 0;

  return rule;
}

struct RuleStruct create_rule_change_a_1 (void) {
  struct RuleStruct rule;

  rule.valid = true;
  rule.type = CHANGE;

  // precondition
  rule.up.state_dc = true;
  rule.up.state_value = false;
  rule.up.type_dc = true;
  rule.up.type_value = 0;

  rule.down.state_dc = true;
  rule.down.state_value = false;
  rule.down.type_dc = true;
  rule.down.type_value = 0;

  rule.north.state_dc = true;
  rule.north.state_value = false;
  rule.north.type_dc = false;
  rule.north.type_value = 2;

  rule.south.state_dc = true;
  rule.south.state_value = false;
  rule.south.type_dc = false;
  rule.south.type_value = 0;

  rule.east.state_dc = true;
  rule.east.state_value = false;
  rule.east.type_dc = true;
  rule.east.type_value = 0;

  rule.west.state_dc = true;
  rule.west.state_value = false;
  rule.west.type_dc = true;
  rule.west.type_value = 0;

  rule.center.state_dc = true;
  rule.center.state_value = false;
  rule.center.type_dc = false;
  rule.center.type_value = 1;

  // result
  rule.dont_change_state = true;
  rule.result.change.type = 1;
  rule.result.change.state = 0;

  return rule;
}

struct RuleStruct create_rule_change_a_2 (void) {
  struct RuleStruct rule;

  rule.valid = true;
  rule.type = CHANGE;

  // precondition
  rule.up.state_dc = true;
  rule.up.state_value = false;
  rule.up.type_dc = true;
  rule.up.type_value = 0;

  rule.down.state_dc = true;
  rule.down.state_value = false;
  rule.down.type_dc = true;
  rule.down.type_value = 0;

  rule.north.state_dc = true;
  rule.north.state_value = false;
  rule.north.type_dc = false;
  rule.north.type_value = 2;

  rule.south.state_dc = true;
  rule.south.state_value = false;
  rule.south.type_dc = false;
  rule.south.type_value = 0;

  rule.east.state_dc = true;
  rule.east.state_value = false;
  rule.east.type_dc = true;
  rule.east.type_value = 0;

  rule.west.state_dc = true;
  rule.west.state_value = false;
  rule.west.type_dc = true;
  rule.west.type_value = 0;

  rule.center.state_dc = true;
  rule.center.state_value = false;
  rule.center.type_dc = false;
  rule.center.type_value = 2;

  // result
  rule.dont_change_state = true;
  rule.result.change.type = 1;
  rule.result.change.state = 0;

  return rule;
}

struct RuleStruct create_rule_change_b_1 (void) {
  struct RuleStruct rule;

  rule.valid = true;
  rule.type = CHANGE;

  // precondition
  rule.up.state_dc = true;
  rule.up.state_value = false;
  rule.up.type_dc = true;
  rule.up.type_value = 0;

  rule.down.state_dc = true;
  rule.down.state_value = false;
  rule.down.type_dc = true;
  rule.down.type_value = 0;

  rule.north.state_dc = true;
  rule.north.state_value = false;
  rule.north.type_dc = true;
  rule.north.type_value = 0;

  rule.south.state_dc = true;
  rule.south.state_value = false;
  rule.south.type_dc = false;
  rule.south.type_value = 2;

  rule.east.state_dc = true;
  rule.east.state_value = false;
  rule.east.type_dc = true;
  rule.east.type_value = 0;

  rule.west.state_dc = true;
  rule.west.state_value = false;
  rule.west.type_dc = false;
  rule.west.type_value = 1;

  rule.center.state_dc = true;
  rule.center.state_value = false;
  rule.center.type_dc = false;
  rule.center.type_value = 1;

  // result
  rule.dont_change_state = true;
  rule.result.change.type = 0;
  rule.result.change.state = 0;

  return rule;
}

struct RuleStruct create_rule_change_b_2 (void) {
  struct RuleStruct rule;

  rule.valid = true;
  rule.type = CHANGE;

  // precondition
  rule.up.state_dc = true;
  rule.up.state_value = false;
  rule.up.type_dc = true;
  rule.up.type_value = 0;

  rule.down.state_dc = true;
  rule.down.state_value = false;
  rule.down.type_dc = true;
  rule.down.type_value = 0;

  rule.north.state_dc = true;
  rule.north.state_value = false;
  rule.north.type_dc = true;
  rule.north.type_value = 0;

  rule.south.state_dc = true;
  rule.south.state_value = false;
  rule.south.type_dc = false;
  rule.south.type_value = 2;

  rule.east.state_dc = true;
  rule.east.state_value = false;
  rule.east.type_dc = true;
  rule.east.type_value = 0;

  rule.west.state_dc = true;
  rule.west.state_value = false;
  rule.west.type_dc = false;
  rule.west.type_value = 1;

  rule.center.state_dc = true;
  rule.center.state_value = false;
  rule.center.type_dc = false;
  rule.center.type_value = 2;

  // result
  rule.dont_change_state = true;
  rule.result.change.type = 0;
  rule.result.change.state = 0;

  return rule;
}

struct RuleStruct create_rule_1_to_2 (void) {
  struct RuleStruct rule;

  rule.valid = true;
  rule.type = CHANGE;

  // precondition
  rule.up.state_dc = true;
  rule.up.state_value = false;
  rule.up.type_dc = true;
  rule.up.type_value = 0;

  rule.down.state_dc = true;
  rule.down.state_value = false;
  rule.down.type_dc = true;
  rule.down.type_value = 0;

  rule.north.state_dc = true;
  rule.north.state_value = false;
  rule.north.type_dc = true;
  rule.north.type_value = 0;

  rule.south.state_dc = true;
  rule.south.state_value = false;
  rule.south.type_dc = true;
  rule.south.type_value = 0;

  rule.east.state_dc = true;
  rule.east.state_value = false;
  rule.east.type_dc = true;
  rule.east.type_value = 0;

  rule.west.state_dc = true;
  rule.west.state_value = false;
  rule.west.type_dc = true;
  rule.west.type_value = 0;

  rule.center.state_dc = true;
  rule.center.state_value = false;
  rule.center.type_dc = false;
  rule.center.type_value = 1;

  // result
  rule.dont_change_state = false;
  rule.result.change.type = 2;
  rule.result.change.state = 0;

  return rule;
}

struct RuleStruct create_rule_2_to_3 (void) {
  struct RuleStruct rule;

  rule.valid = true;
  rule.type = CHANGE;

  // precondition
  rule.up.state_dc = true;
  rule.up.state_value = false;
  rule.up.type_dc = true;
  rule.up.type_value = 0;

  rule.down.state_dc = true;
  rule.down.state_value = false;
  rule.down.type_dc = true;
  rule.down.type_value = 0;

  rule.north.state_dc = true;
  rule.north.state_value = false;
  rule.north.type_dc = true;
  rule.north.type_value = 0;

  rule.south.state_dc = true;
  rule.south.state_value = false;
  rule.south.type_dc = true;
  rule.south.type_value = 0;

  rule.east.state_dc = true;
  rule.east.state_value = false;
  rule.east.type_dc = true;
  rule.east.type_value = 0;

  rule.west.state_dc = true;
  rule.west.state_value = false;
  rule.west.type_dc = true;
  rule.west.type_value = 0;

  rule.center.state_dc = true;
  rule.center.state_value = false;
  rule.center.type_dc = false;
  rule.center.type_value = 2;

  // result
  rule.dont_change_state = false;
  rule.result.change.type = 3;
  rule.result.change.state = 0;

  return rule;
}

