/*****************************************************************************
 * PCI interface
 *
 * Allows communication with PCI devices by memory-mapping the resource file
 * automaticly created by the Linux kernel. A driver is thus unnecessary.
 *
 * Per Thomas Lundal 2014
 *****************************************************************************/

#ifndef PCI_H
#define PCI_H

/* Executes a command and returns the first line */
void command_execute(char *result, char *command);

/* Returns a command that will print the path of specified resource */
void pci_resource_command(char *command, char *vendor_code, int base_address_register);

/* External interface */
int pci_resource_open(char *vendor_code, int base_address_register);
void *pci_resource_map(int resource_file);
void pci_resource_unmap(void *map_base);
void pci_resource_close(int resource_file);

#endif

