#include <config.h>

VM_IMAGE(freertos_image1, XSTR(BAO_DEMOS_WRKDIR_IMGS/freertos1.bin));
VM_IMAGE(freertos_image2, XSTR(BAO_DEMOS_WRKDIR_IMGS/freertos2.bin));

struct config config = {
    
    CONFIG_HEADER

    .vmlist_size = 2,
    .vmlist = {
        {
            .image = {
                .base_addr = 0x80200000,
                .load_addr = VM_IMAGE_OFFSET(freertos_image1),
                .size = VM_IMAGE_SIZE(freertos_image1)
            },

            .entry = 0x80200000,

            .platform = {
                .cpu_num = 1,
                
                .region_num = 1,
                .regions =  (struct mem_region[]) {
                    {
                        .base = 0x80000000,
                        .size = 0x8000000
                    }
                },

                .dev_num = 1,
                .devs =  (struct dev_region[]) {
                    {
                        .pa = 0x10000000,   
                        .va = 0x10000000,  
                        .size = 0x1000, 
                        .interrupt_num = 1,
                        .interrupts = (uint64_t[]) {10}
                    },
                },

                .arch = {
                    .plic_base = 0xc000000,
                }
            },
        },
        { 
            .image = {
                .base_addr = 0x90200000,
                .load_addr = VM_IMAGE_OFFSET(freertos_image2),
                .size = VM_IMAGE_SIZE(freertos_image2)
            },

            .entry = 0x90200000,

            .platform = {
                .cpu_num = 1,
                
                .region_num = 1,
                .regions =  (struct mem_region[]) {
                    {
                        .base = 0x80000000,
                        .size = 0x80000000
                    }
                },

                .dev_num = 1,
                .devs =  (struct dev_region[]) {
                    {
                        .pa = 0x10002000,   
                        .va = 0x10002000,  
                        .size = 0x1000, 
                        .interrupt_num = 1,
                        .interrupts = (uint64_t[]) {12}
                    },
                },

                .arch = {
                    .plic_base = 0xc000000,
                }
            },
        },
    }
};
