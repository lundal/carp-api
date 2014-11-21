#ifndef PCI_H
#define PCI_H

void command_execute(char *result, char *command);

void pci_resource_command(char *command, char *vendor_code, int base_address_register);
int pci_resource_open(char *vendor_code, int base_address_register);
void *pci_resource_map(int resource_file);
void pci_resource_unmap(void *map_base);
void pci_resource_close(int resource_file);

#endif

