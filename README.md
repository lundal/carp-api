## Cellular Automata Research Platform - API

This repository contains the software api for my work on the Cellular Automata Reasearch Platform at the Norwegian University of Science and Technology.

#### How to run tests
1. Run make to compile the library and test file
2. Execute sudo programs/test <test_number>

#### How to create a program
1. Create programs/yourprogram.c
2. Include carp.h and optionally print.h
3. Add a main function with your code
4. Run make
5. Execute sudo programs/yourprogram

#### Requirements
* FPGA connected to PCI Express implementing the carp design.
* Root access (to connect to board).
