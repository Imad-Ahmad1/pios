#include "sd.h"
#include "fat.h"
#include <string.h>
#include <stdio.h>

#define SECTOR_SIZE 512  

struct boot_sector *bs;
char bootSector[SECTOR_SIZE];
char fat_table[8 * SECTOR_SIZE];
unsigned int root_sector;
char rde_region[2048];  
struct root_directory_entry* rde;

int sd_init();
int sd_readblock();
int my_strncmp();
int my_strcmp();

int fatInit() {
        sd_readblock(0, (unsigned char*)bootSector, 1);
    bs = (struct boot_sector*)bootSector;

    if (bs->boot_signature != 0xAA55) {
        printf("Invalid boot: %04x\n", bs->boot_signature);
        return -1;
    }

    
    if (my_strncmp(bs->fs_type, "FAT12", 5) != 0) {
        printf("Incorrect filesystem type: %.5s\n", bs->fs_type);
        return -1;
    }

    
    unsigned int fat_start_sector = bs->num_reserved_sectors;
    sd_readblock(fat_start_sector, (unsigned char*)fat_table, bs->num_sectors_per_fat);

   
    root_sector = bs->num_reserved_sectors
                + (bs->num_fat_tables * bs->num_sectors_per_fat)
                + bs->num_hidden_sectors;

    // Load root directory entries into buffer
    sd_readblock(root_sector, (unsigned char*)rde_region, (bs->num_root_dir_entries * 32) / SECTOR_SIZE);

    return 0; 
}

int fatOpen(char* fname) {
    int i = 0;
    rde = (struct root_directory_entry *)&rde_region[i * sizeof(struct root_directory_entry)];
    while (my_strcmp(rde->file_name, fname) != 0) {
        i++;
        if (i >= 2048) {
            printf("Error: could not find file\n");
            return -1;
        }
        rde = (struct root_directory_entry *)&rde_region[i * sizeof(struct root_directory_entry)];
    }
    return 0;
}

int fatRead(char* buf, int n) {
    if (!rde) {
        printf("ERROR: No file opened\n");
        return -1;
    }

    int clsr = ((int)rde->cluster) - 2; 
    sd_readblock(root_sector + ((bs->num_root_dir_entries * 32) / SECTOR_SIZE) + 
                 (clsr * bs->num_sectors_per_cluster), (unsigned char *)buf, n / SECTOR_SIZE);
    return 0;
}


int my_strncmp(char* a, char* b, int num) {
    for (int i = 0; i < num; i++) {
        if (a[i] != b[i]) {
            return a[i] < b[i] ? -1 : 1;
        }
    }
    return 0;
}

int my_strcmp(char* a, char* b) {
    for (int i = 0; a[i] != ' '; i++) {
        if (a[i] != b[i]) {
            return a[i] < b[i] ? -1 : 1;
        }
    }
    return 0;
}

