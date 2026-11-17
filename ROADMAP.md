# Roadmap

This roadmap separates practical improvements from unverified reverse-engineering work. Completed items refer to development branches, not hardware certification.

## Completed in v3.4
- [x] Show decoded buffer duration, sample rate and channel count.
- [x] Add sampled peak/RMS estimates with approximation clearly labelled.
- [x] Add waveform zoom and horizontal window navigation.
- [x] Add separate monitoring gain that does not alter exported source WAV data.

## Completed in v3.3
- [x] Optional manual IndexedDB save/restore/delete for library files, metadata, favourites, audio links and capture blobs.
- [x] Rebuild decoded AudioBuffers and capture object URLs after restore.
- [x] Report local storage entry counts and browser quota estimates where available.

## Completed in v3.2
- [x] Fix sequential audition and linked real-audio navigation.
- [x] Apply attack, release, width and reverb settings to the proxy renderer.
- [x] Stop presenting arbitrary SysEx data as audio.
- [x] Add an explicit target and safety acknowledgement before SysEx send.
- [x] Bound ZIP imports and decompression; check CRC, size, entry count and nesting.
- [x] Add duplicate file detection and MIDI input monitoring.
- [x] Add HTML / DOM and ZIP / SysEx regression checks to GitHub Actions.
- [x] Generate and upload a portable ZIP bundle from successful CI runs.

## Next practical work
- [ ] Click-to-seek and A/B audition for original versus reference capture.
- [ ] Audio comparison tools: loudness matching, polarity and delta/null preview.
- [ ] JSON metadata export/import with schema versioning and optional file manifest.
- [ ] Per-device MIDI routing profiles and incoming MIDI learn.
- [ ] Better AFSND manifest compatibility tests using lawful sample files.
- [ ] Regression fixtures for malformed ZIP, truncated SysEx and edge-case audio.
- [ ] Full French/English UI localization.

## Research track — only after evidence
- [ ] Document native Elektron Transfer protocol from lawful, reproducible observations.
- [ ] Build a read-only native sound parser with versioned fixtures and checksums.
- [ ] Determine whether any parameter subset can be mapped without copying proprietary firmware/DSP code.

## Not promised
- Bit-accurate Digitone / Analog Four emulation without validated DSP and parameter mappings.
- Native sound transfer without a verified protocol implementation and physical hardware tests.
- Project or firmware write support.
