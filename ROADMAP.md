# Roadmap

This roadmap separates practical improvements from unverified reverse-engineering work. Completed items below refer to the v3.2 public branch, not to hardware certification.

## Completed in v3.2
- [x] Fix sequential audition and linked real-audio navigation.
- [x] Apply attack, release, width and reverb settings to the proxy renderer.
- [x] Stop presenting arbitrary SysEx data as audio.
- [x] Add an explicit target and safety acknowledgement before SysEx send.
- [x] Bound ZIP imports and decompression; check CRC, size, entry count and nesting.
- [x] Add duplicate file detection and MIDI input monitoring.
- [x] Add static HTML / DOM checks to GitHub Actions.

## Next practical work
- [ ] IndexedDB library persistence with explicit backup/export and privacy controls.
- [ ] Audio metadata panel (duration, sample rate, channels, peak/RMS) after decode.
- [ ] Waveform zoom, audition gain, keyboard shortcuts and accessible controls.
- [ ] Per-device MIDI routing profiles and incoming MIDI learn.
- [ ] Better AFSND manifest compatibility tests using lawful sample files.
- [ ] Regression fixtures for malformed ZIP, truncated SysEx and edge-case audio.
- [ ] More detailed queue log with source file, byte count, target and user confirmation.
- [ ] Full French/English UI localization.

## Research track — only after evidence
- [ ] Document native Elektron Transfer protocol from lawful, reproducible observations.
- [ ] Build a read-only native sound parser with versioned fixtures and checksums.
- [ ] Determine whether any parameter subset can be mapped without copying proprietary firmware/DSP code.
- [ ] Evaluate modular architecture if the standalone app becomes difficult to test.

## Not promised
- Bit-accurate Digitone / Analog Four emulation without validated DSP and parameter mappings.
- Native sound transfer without a verified protocol implementation and physical hardware tests.
- Project or firmware write support.
