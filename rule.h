/*****************************************************************************
 * Rule
 *
 * Types describing development rules
 *
 * Asbjørn Djupdal 2003
 * Kjetil Aamodt 2005
 * Ola Martin Tiseth Støvneng 2014
 * Per Thomas Lundal 2015
 *****************************************************************************/

#ifndef RULE_H
#define RULE_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
  bool state_check;
  bool state_value;
  bool type_check;
  uint32_t type_value;
} condition_t;

typedef struct {
  bool state_change;
  bool state_value;
  bool type_change;
  uint32_t type_value;
} result_t;

typedef struct {
  condition_t z_negative;
  condition_t z_positive;
  condition_t y_negative;
  condition_t y_positive;
  condition_t x_negative;
  condition_t x_positive;
  result_t result;
} rule_t;

#endif
