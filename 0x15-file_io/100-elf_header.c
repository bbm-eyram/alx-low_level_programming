#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <elf.h>

#define BUFFER_SIZE 64

/**
 * error_exit - Print an error message to stderr and exit with status code 98.
 * @msg: The error message to print.
 */
void error_exit(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(98);
}

/**
 * print_elf_header_info - Print ELF header information.
 * @header: Pointer to the ELF header.
 */
void print_elf_header_info(Elf64_Ehdr *header) {
    printf("  Magic:   ");
    for (int i = 0; i < EI_NIDENT; i++) {
        printf("%02x ", header->e_ident[i]);
    }
    printf("\n");

    printf("  Class:                             %s\n", header->e_ident[EI_CLASS] == ELFCLASS64 ? "ELF64" : "ELF32");
    printf("  Data:                              %s\n", header->e_ident[EI_DATA] == ELFDATA2LSB ? "2's complement, little-endian" : "unknown");
    printf("  Version:                           %d (current)\n", header->e_ident[EI_VERSION]);
    printf("  OS/ABI:                            %d\n", header->e_ident[EI_OSABI]);
    printf("  ABI Version:                       %d\n", header->e_ident[EI_ABIVERSION]);

    printf("  Type:                              ");
    switch (header->e_type) {
        case ET_NONE:
            printf("NONE (None)\n");
            break;
        case ET_REL:
            printf("REL (Relocatable file)\n");
            break;
        case ET_EXEC:
            printf("EXEC (Executable file)\n");
            break;
        case ET_DYN:
            printf("DYN (Shared object file)\n");
            break;
        case ET_CORE:
            printf("CORE (Core file)\n");
            break;
        default:
            printf("<unknown: %x>\n", header->e_type);
            break;
    }

    printf("  Entry point address:               %#lx\n", (unsigned long)header->e_entry);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s elf_filename\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        error_exit("Error: Cannot open ELF file");
    }

    Elf64_Ehdr header;
    ssize_t read_bytes = read(fd, &header, sizeof(Elf64_Ehdr));
    if (read_bytes == -1) {
        close(fd);
        error_exit("Error: Cannot read ELF header");
    }

    if (read_bytes != sizeof(Elf64_Ehdr) ||
        header.e_ident[EI_MAG0] != ELFMAG0 ||
        header.e_ident[EI_MAG1] != ELFMAG1 ||
        header.e_ident[EI_MAG2] != ELFMAG2 ||
        header.e_ident[EI_MAG3] != ELFMAG3) {
        close(fd);
        error_exit("Error: Not an ELF file");
    }

    printf("ELF Header:\n");
    print_elf_header_info(&header);

    close(fd);
    return 0;
}
