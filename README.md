## SCAPES

## Authors:
  Amanda Niyonkuru 100938974
  Michael Rabbai 101009342
  Jimmy Woo 100823301

## Introduction
The School of Computer science Assembly Programming Environment System (SCAPES) is a development environment that allows a user to write, compile, and execute basic programs written in the School of Computer science Assembly Programming Language (SCAPL) language.

## Compile:
  - prerequisite: be in the source directory of the  (i.e. /SCAPES/source/)
  - set PATH variable using command: export PATH=$PATH:~/Qt/5.13.0/gcc_64/bin
  execute in terminal: make

## Run:
- prerequisite: be in the source directory of the  (i.e. /SCAPES/source/)
  execute in terminal: ./scapes

## Design Pattern Used:
- factory method used to delegate creation of statement objects to the factory class
- allows program class to create statement objects without knowing the exact subclsas type
- separates object creation from program class
