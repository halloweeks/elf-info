#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <elf.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, const char *argv[]) {
	if (argc != 2) {
		printf("Usage ./program <executable>\n");
		return 1;
	}
	
    int fd = open(argv[1], O_RDONLY);
    
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    struct stat file_stat;
    if (fstat(fd, &file_stat) < 0) {
        perror("Error getting file stat");
        close(fd);
        return 1;
    }

    Elf64_Ehdr elf_header;
    if (read(fd, &elf_header, sizeof(Elf64_Ehdr)) != sizeof(Elf64_Ehdr)) {
        perror("Error reading ELF header");
        close(fd);
        return 1;
    }

    Elf64_Shdr section_header;
    off_t offset = elf_header.e_shoff + elf_header.e_shstrndx * elf_header.e_shentsize;

    if (pread(fd, &section_header, sizeof(Elf64_Shdr), offset) != sizeof(Elf64_Shdr)) {
        perror("Error reading section header");
        close(fd);
        return 1;
    }

    char *section_names = malloc(section_header.sh_size);
    
    if (!section_names) {
        perror("Error allocating memory");
        close(fd);
        return 1;
    }

    if (pread(fd, section_names, section_header.sh_size, section_header.sh_offset) != section_header.sh_size) {
        perror("Error reading section names");
        free(section_names);
        close(fd);
        return 1;
    }
    
    for (int i = 0; i < elf_header.e_shnum; i++) {
        if (pread(fd, &section_header, sizeof(Elf64_Shdr), elf_header.e_shoff + i * elf_header.e_shentsize) != sizeof(Elf64_Shdr)) {
            perror("Error reading section header");
            free(section_names);
            close(fd);
            return 1;
        }
        
        if (strcmp(section_names + section_header.sh_name, "") == 0) {
        	printf("section 'NULL' offset 0, size 0B\n");
        } else {
        	printf("section: '%s' offset: 0x%llX, size: %llu\n", section_names + section_header.sh_name, section_header.sh_offset, section_header.sh_size);
        }
    }
    
    free(section_names);
    close(fd);
    return 0;
}
