#include "pci.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

#define STRING_SIZE 256

#define EXIT_WITH_ERROR(MESSAGE) \
  do { \
    fprintf(stderr, "Error in file %s at line %d: %s\n", \
    __FILE__, __LINE__, MESSAGE); exit(1); \
  } while(0)

void command_execute(char *result, char *command) {
  FILE *process = popen(command, "r");
  if (process == NULL) EXIT_WITH_ERROR("Could not open process");

  if (fgets(result, STRING_SIZE, process) == NULL) EXIT_WITH_ERROR("No result");

  result[strlen(result)-1] = 0; // Strips newline

  pclose(process);
}

void pci_resource_command(char *command, char *vendor_code, int base_address_register) {
  char *resource_command = "grep --include=vendor -rlwi /sys/devices/pci* -e \"%s\" | sed \"s/vendor/resource%d/\"";
  if (snprintf(command, STRING_SIZE, resource_command, vendor_code, base_address_register) < 0) EXIT_WITH_ERROR("Could not format command");
}

int pci_resource_open(char *vendor_code, int base_address_register) {
  char resource_command[STRING_SIZE];
  char resource_path[STRING_SIZE];

  pci_resource_command(resource_command, vendor_code, base_address_register);
  command_execute(resource_path, resource_command);

  int resource_file = open(resource_path, O_RDWR | O_SYNC);
  if (resource_file < 0) EXIT_WITH_ERROR("Could not open resource file. Got root?");

  return resource_file;
}

void *pci_resource_map(int resource_file, size_t map_size) {
  void *map_base = mmap(0, map_size, PROT_READ | PROT_WRITE, MAP_SHARED, resource_file, 0);
  if (map_base == MAP_FAILED) EXIT_WITH_ERROR("Map failed");

  return map_base;
}

void pci_resource_unmap(void *map_base) {
  if (munmap(map_base, MAP_SIZE) < 0) EXIT_WITH_ERROR("Unmap failed");
}

void pci_resource_close(int resource_file) {
  close(resource_file);
}

int main( int argc, char *argv[] )
{
  int resource_file;
  void *resource_base;
  resource_file = pci_resource_open("0xDACA", 0);
  resource_base = pci_resource_map(resource_file, 4096UL);
  pci_resource_unmap(resource_base);
  pci_resource_close(resource_file);
}

