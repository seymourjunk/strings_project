# Simple Strings Utility
A lightweight educational implementation of the classic `strings` utility. Scans binary files for sequences of printable ASCII characters and prints them to standard output.

## Features
- Scans file for printable ASCII strings
- Configurable minimum string length (default: 4)

## Usage
`./program <file> [min_length]`
- <file> -- path to the file to scan
- [min_length] -- optional minimum string length (default: 4)

## Educational Purpose
This project was created to practice:
1. File I/O operations in C
2. Memory buffer management
3. Error handling and input validation

## TODO
- [ ] file section detection (PE/ELF)
- [ ] stdin support
- [ ] different encoding support
- [ ] add -n flag for configurable minimum length
- [ ] print byte offset of strings
- [ ] print length of strings
- [ ] print size of strings
