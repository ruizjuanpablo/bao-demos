# Bao Hypervisor Demo with two FreeRTOS

This is a forked repository from: https://github.com/bao-project/bao-demos

This repository runs two FreeRTOS on the top of Bao Hypervisor. Each FreeRTOS
print in a different virtual serial port on Qemu. 

## -1. Install dependencies

```
sudo apt install ninja-build u-boot-tools pandoc
```

## 0. Download and setup the toolchain

b) For RISC-V, use the **riscv64-unknown-elf-** toolchain.

Download it from [SiFive's Freedom Tools][riscv-toolchains] github reposiroty.

Install the toolchain. Then, set the **CROSS_COMPILE** environment variable 
with the reference toolchain prefix path:

```
export CROSS_COMPILE=/path/to/toolchain/install/dir/bin/your-toolchain-prefix-
```

## 1. Setup base environment

Clone this repo and cd to it:

```
git clone https://github.com/ruizjuanpablo/bao-demos.git
cd bao-demos
```

Setup your target platform for RISC-V, your demo for two FreeRTOS and
the architecture:

```
export PLATFORM=qemu-riscv64-virt
export DEMO=freertos+freertos
export ARCH=riscv
```

## 2. Use automated make

Just execute:

```
make -j$(nproc)
```

And all the needed source and images will be automatically downloaded and built. 
The makefiles will also print some instructions for you to carry out when it is 
not possible to automate a given step for some reason (e.g. download behind 
authentication wall). It will also print the instructions on how to deploy the
images on your target platform. To quiet instructions pass `NO_INSTRUCTIONS=1` 
to make.

---

**WARNING**

The makefiles will automatically accept end-user license agreements (EULAs) on 
your behalf for some of the downloaded firmware. If you wish to be prompted 
to accept them manually, pass `ALWAYS_ASK=1` to make.

---

## 3. Run Qemu with the compiled image


Execute the following command to run Qemu with the compiled image. 

```
wrkdir/srcs/qemu/build/qemu-system-riscv64 -nographic \
    -M virt -cpu rv64,priv_spec=v1.10.0,x-h=true -m 4G -smp 4 \
    -bios wrkdir/imgs/qemu-riscv64-virt/freertos+freertos/opensbi.elf \
    -S -serial pty -chardev pty,id=serial1 -serial chardev:serial1
```

When it started, it will print the char device serial port redirection. You can 
open two other terminals to get the serial port outputs. Then, continue the 
Qemu emulation by pressing Ctrl+A to enable qemu terminal, and then "c" Enter
to continue the emulation.  

To exit Qemu, press "q" Enter. 