# ELF Section Info Tool

This simple C program (`elf.c`) extracts information about ELF binary sections, specifically designed for ARM64 architecture. It prints section names, offsets, and sizes.

## Build Instructions

Ensure you have the necessary dependencies installed (e.g., `gcc`). Then, follow these steps to build the program:

```bash
gcc -o elf_section_info elf.c
```

## Usage

### ARM64 Binary Support

Make sure to use ARM64 ELF binaries with this tool.

### Example

Run the program with the ARM64 ELF binary as an argument:

```bash
./elf_section_info <your_arm64_binary>
```

The program will output information about each section, including section name, offset from the start of the binary, and size.

#### Note

If a section has an empty name (""), it will be displayed as:

```bash
section 'NULL' offset 0, size 0
```

## Example Output

```
section: '<section_name>' offset: 0x<offset>, size: <size>
section: 'text' offset: 0x1000, size: 4096
section: 'data' offset: 0x5000, size: 1024
section 'NULL' offset 0, size 0
...
