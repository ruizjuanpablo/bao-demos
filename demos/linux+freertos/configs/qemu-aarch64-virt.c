#include <config.h>

VM_IMAGE(linux_image, XSTR(BAO_DEMOS_WRKDIR_IMGS/linux.bin));
VM_IMAGE(freertos_image, XSTR(BAO_DEMOS_WRKDIR_IMGS/freertos.bin));

struct config config = {
    
    CONFIG_HEADER

    .shmemlist_size = 1,
    .shmemlist = (struct shmem[]) {
        [0] = { .size = 0x00010000, }
    },

    .vmlist_size = 2,
    .vmlist = {
        { 
            .image = {
                .base_addr = 0x60000000,
                .load_addr = VM_IMAGE_OFFSET(linux_image),
                .size = VM_IMAGE_SIZE(linux_image)
            },

            .entry = 0x60000000,

            .platform = {
                .cpu_num = 3,
                
                .region_num = 1,
                .regions =  (struct mem_region[]) {
                    {
                        .base = 0x60000000,
                        .size = 0x40000000,
                        .place_phys = true,
                        .phys = 0x60000000
                    }
                },

                .ipc_num = 1,
                .ipcs = (struct ipc[]) {
                    {
                        .base = 0xf0000000,
                        .size = 0x00010000,
                        .shmem_id = 0,
                        .interrupt_num = 1,
                        .interrupts = (uint64_t[]) {52}
                    }
                },

                .dev_num = 2,
                .devs =  (struct dev_region[]) {
                    {
                        /* virtio devices */
                        .pa = 0xa003000,   
                        .va = 0xa003000,  
                        .size = 0x1000,
                        .interrupt_num = 8,
                        .interrupts = (uint64_t[]) {72,73,74,75,76,77,78,79}
                    },
                    {   
                        /* Arch timer interrupt */
                        .interrupt_num = 1,
                        .interrupts = (uint64_t[]) {27}                         
                    }
                },

                .arch = {
                    .gic = {
                       .gicd_addr = 0x8000000,
                       .gicr_addr = 0x80A0000
                    }
                }
            },
        },
        { 
            .image = {
                .base_addr = 0x00000000,
                .load_addr = VM_IMAGE_OFFSET(freertos_image),
                .size = VM_IMAGE_SIZE(freertos_image)
            },

            .entry = 0x00000000,

            .platform = {
                .cpu_num = 1,
                
                .region_num = 1,
                .regions =  (struct mem_region[]) {
                    {
                        .base = 0x00000000,
                        .size = 0x8000000 
                    }
                },

               .ipc_num = 1,
                .ipcs = (struct ipc[]) {
                    {
                        .base = 0x70000000,
                        .size = 0x00010000,
                        .shmem_id = 0,
                        .interrupt_num = 1,
                        .interrupts = (uint64_t[]) {52}
                    }
                },

                .dev_num = 2,
                .devs =  (struct dev_region[]) {
                    {   
                        /* PL011 */
                        .pa = 0x9000000,
                        .va = 0xFF010000,
                        .size = 0x10000, 
                        .interrupt_num = 1,
                        .interrupts = (uint64_t[]) {33}                         
                    },
                    {   
                        .interrupt_num = 1,
                        .interrupts = (uint64_t[]) {27}                         
                    }
               },

                .arch = {
                    .gic = {
                        .gicd_addr = 0xF9010000,
                        .gicr_addr = 0xF9020000,
                    }
                }
            },
        }

    },
};
