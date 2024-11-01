#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include "fat.h"

// File descriptor for the disk image
int fd = 0;
char sector_buf[512];

void init() {
    // Open the disk image for reading
    fd = open("disk.img", O_RDONLY);
    if (fd < 0) {
        perror("open");
        fprintf(stderr, "open() failed\n");
        exit(-1);
    }
}

// Reads the contents of one sector into the provided buffer
void readSector(unsigned int sector, char *buf) {
	 // Move file pointer to the start of the requested sector
    off_t offset = lseek(fd, 512 * sector, SEEK_SET);
    if (offset == -1) {
        perror("lseek");
        fprintf(stderr, "lseek() failed\n");
        exit(-1);
    }

    // Read sector into buffer
    ssize_t n = read(fd, buf, 512);
    if (n == -1) {
        perror("read");
        fprintf(stderr, "read() failed\n");
	 exit(-1);
    }
}

int main() {
    struct boot_sector *bs = (struct boot_sector*)sector_buf;
    init();
    readSector(0, sector_buf);

    // Print the first 16 bytes of the boot sector for inspection
    for (int k = 0; k < 16; k++) {
        printf("%02x ", sector_buf[k]);
    }
    printf("\n");

    // Access and print some key fields from the boot sector
    printf("Bytes per sector = %d\n", bs->bytes_per_sector);
    printf("Sectors per cluster = %d\n", bs->num_sectors_per_cluster);
    printf("Reserved sectors = %d\n", bs->num_reserved_sectors);
    printf("Number of FATs = %d\n", bs->num_fat_tables);
    printf("Number of root directory entries = %d\n", bs->num_root_dir_entries);
close(fd); // Clean up file descriptor
    return 0;
}

