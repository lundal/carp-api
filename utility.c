/*****************************************************************************
 * Utility
 *
 * Various utility functions
 *
 * Asbjørn Djupdal 2003
 * Kjetil Aamodt 2005
 * Ola Martin Tiseth Støvneng 2014
 * Per Thomas Lundal 2015
 *****************************************************************************/

#include "utility.h"

int div_ceil(int dividend, int divisor) {
  return (dividend % divisor) ? dividend / divisor + 1 : dividend / divisor;
}
