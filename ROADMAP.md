# Roadmap

This roadmap separates practical product improvements from unverified reverse-engineering work.

## Near term — realistic
- [ ] Automated test fixtures for ZIP, AFSND manifests, SysEx framing and audio-decode errors.
- [ ] Improve AFSND/DNSND metadata extraction from legally obtained samples and documented schemas.
- [ ] IndexedDB library persistence with explicit backup/export and privacy controls.
- [ ] Waveform zoom, audition gain, shortcuts and accessible controls.
- [ ] Per-device routing profiles and safer single-message send preview.
- [ ] Batch reports distinguishing MIDI-queued from hardware-confirmed.
- [ ] Audio-reference management and offline audio metadata analysis.
- [ ] Full French/English UI localization.

## Research track — only after evidence
- [ ] Document native Elektron Transfer protocol from lawful, reproducible observations.
- [ ] Build a read-only native sound parser with versioned fixtures and checksums.
- [ ] Determine whether any parameter subset can be mapped without copying proprietary firmware/DSP code.
- [ ] Evaluate modular architecture if single-file app becomes difficult to test.

## Not promised
- Bit-accurate Digitone / Analog Four emulation without validated DSP and parameter mapping.
- Native sound transfer without verified protocol implementation and physical hardware tests.
- Project or firmware write support.
