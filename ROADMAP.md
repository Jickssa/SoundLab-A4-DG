# Roadmap

This roadmap separates practical improvements from unverified reverse-engineering work. Completed items refer to development branches, not hardware certification.

## Completed in v3.7
- [x] Add visual waveform editor with zoom-aware mouse/touch range selection.
- [x] Add drawn gain envelope with selected-range or visible-range scope.
- [x] Add gain, fades, −1 dBFS normalization, reverse, silence and trim.
- [x] Add bounded undo/redo, selection playback, WAV export and editable-copy creation.
- [x] Keep source files/captures/native payloads unchanged and separate A/B edit states.
- [x] Add regression coverage for source isolation, edit scope, multichannel operations and history.

## Completed in v3.6
- [x] Recognize the individual Sound SysEx subtype for Analog Four / Analog Keys and Digitone MK1.
- [x] Validate model, Sound prefix, 8-in-7 payload, checksum and length before extracting slot/name/tags.
- [x] Restrict SysEx queueing to valid Sound frames whose model matches the selected target.
- [x] Add synthetic A4/Digitone parser fixtures and malformed-frame regression tests.
- [x] Document format scope and non-goals; no proprietary synthesis parameters or Transfer protocol are claimed.

## Completed in v3.5
- [x] Add A/B selection between direct machine capture / linked audio reference and native proxy synthesis.
- [x] Prefer a direct capture attached to a native patch; fall back to the linked audio file.
- [x] Export the active A/B source to a correspondingly named WAV.
- [x] Keep raw SysEx as data; allow only a real recording reference in A, never an arbitrary proxy tone.

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
