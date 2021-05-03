include $(bao_demos)/guests/freertos/make.mk

freertos_image1:=$(wrkdir_demo_imgs)/freertos1.bin
freertos_image2:=$(wrkdir_demo_imgs)/freertos2.bin
$(eval $(call build-freertos1, $(freertos_image1)))
$(eval $(call build-freertos2, $(freertos_image2)))

guest_images:=$(freertos_image1) $(freertos_image2)