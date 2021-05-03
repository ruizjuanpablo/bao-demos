freertos_src:=$(wrkdir_src)/freertos+freertos
#freertos_src:=$(wrkdir_src)/freertos
freertos_repo:=https://github.com/ruizjuanpablo/freertos-over-bao.git

$(freertos_src):
	git clone --recursive --shallow-submodules --branch demo $(freertos_repo)\
		$(freertos_src)

freertos_bin:=$(freertos_src)/build/$(PLATFORM)/freertos.bin
freertos_bin1:=$(freertos_src)/build/$(PLATFORM)/freertos1.bin
freertos_bin2:=$(freertos_src)/build/$(PLATFORM)/freertos2.bin

freertos $(freertos_bin): $(freertos_src)
	$(MAKE) -C $(freertos_src) PLATFORM=$(PLATFORM)

freertos1 $(freertos_bin1): $(freertos_src)
	@echo 
	@echo Building $@
	$(MAKE) -C $(freertos_src) clean
	$(MAKE) -C $(freertos_src) PLATFORM=$(PLATFORM) NAME=freertos1 \
	GUEST_MACHINE_NUMBER="0" \
	VIRT_UART16550_ADDR="0x10000000" \
	VIRT_UART16550_INTERRUPT="10"

freertos2 $(freertos_bin2): $(freertos_src)
	@echo 
	@echo Building $@
	$(MAKE) -C $(freertos_src) clean
	$(MAKE) -C $(freertos_src) PLATFORM=$(PLATFORM) NAME=freertos2 \
	GUEST_MACHINE_NUMBER="1" \
	VIRT_UART16550_ADDR="0x10002000" \
	VIRT_UART16550_INTERRUPT="12"
	
define build-freertos
$(strip $1): $(freertos_bin)
	cp $$< $$@
endef

define build-freertos1
$(strip $1): $(freertos_bin1)
	cp $$< $$@
endef

define build-freertos2
$(strip $1): $(freertos_bin2)
	cp $$< $$@
endef
