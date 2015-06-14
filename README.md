## Cellular Automata Research Platform - API

This repository contains the software API for my work on the Cellular Automata Research Platform at the Norwegian University of Science and Technology.

#### How to run tests
1. $ make test

#### How to create a program
1. Create programs/yourprogram.c
2. Include carp.h and optionally print.h
3. Add a main function with your code
4. $ make
5. $ sudo programs/yourprogram.carp

#### Requirements
* FPGA connected to PCI Express implementing the CARP design.
* Root access (to connect to board).
