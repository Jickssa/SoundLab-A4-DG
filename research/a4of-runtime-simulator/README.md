# A4OF runtime simulator

Host-side research components for an independent Analog Four MK1 / Analog Keys MK1 firmware architecture.

This directory is deliberately isolated from the SoundLab browser application. It contains no Elektron firmware, copied proprietary routines, binary dumps, target image, or hardware pinout claims.

## Scope

- Configurable 32-bit address bus with RAM regions and MMIO callbacks.
- Big-endian 8/16/32-bit accesses, permissions, overlap/range/alignment checks.
- Generic 74HC373 logic model (not an asserted A4 wiring model).
- Fixed-capacity event ingress queue.
- Monotonic deterministic scheduler: deadline, priority, stable insertion order.
- Parameter registry with bounds and read-only metadata.
- C11 host tests; no dynamic allocation in runtime data structures.

## Build and test

From this directory:

```sh
make clean test
```

The default build uses strict C11 warnings as errors. Clang can be selected with `make CC=clang test`.

## Important boundaries

This is **not** a ColdFire instruction emulator, not a board-support package and not a bootable firmware. No physical A4 MMIO addresses are predefined. Test addresses are synthetic. The bus "cycle" counter is a synthetic transaction-byte counter, not a MCF54415 cycle model.

The 74HC373 model describes the generic component only. It does not prove that the A4 uses its latches for button scanning, nor does it define LE/OE nets, panel wiring or scan timing.

The event queue and scheduler are single-context data structures. They are not lock-free and are not ISR/thread safe. Do not call them concurrently without a target-specific synchronization layer.

No real hardware, flash, BDM/JTAG, FPGA configuration or analog control is accessed by this code.
