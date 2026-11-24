# A4OF runtime simulator — validation

Local validation:

```sh
cd research/a4of-runtime-simulator
make clean test
make clean test CC=clang
```

A passing host test does not mean the program boots on the Analog Four. It does not validate MCF54415 instruction emulation, physical MMIO, DDR2 timing, FPGA protocol, panel wiring, codec routing or analog controls. No physical memory is written.
