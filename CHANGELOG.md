# Changelog

## 3.4 — audio inspection and audition controls
- Add decoded-buffer duration, sample rate and channel count display.
- Add sampled peak/RMS estimates, labelled as approximate.
- Add waveform zoom and horizontal window navigation.
- Add separate monitoring gain; source WAV export remains unchanged.
- Add audio-inspector regression tests and portable v3.4 CI artifact.

## 3.3 — persistent local library
- Add optional IndexedDB save, restore and delete controls.
- Persist imported source blobs, typed-array payloads, metadata, tags, favourites, linked audio IDs and recorded capture blobs.
- Rebuild decoded audio buffers, proxy previews and capture object URLs after restore.
- Keep persistence manual and browser-origin/profile scoped; display local entry counts and quota estimates where supported.
- Expand CI required-control audit and regression invariants for local persistence.

## 3.2 — reliability, audition and transfer safeguards
- Fix sequential audition state so queue playback advances through the selected items.
- Apply attack, release, stereo width and a feedback-delay reverb stage to proxy rendering.
- Stop treating arbitrary SysEx messages as audible preview items; real audio references can still be linked.
- Require an explicit Analog Four / Digitone target and a safety acknowledgement before individual or batch SysEx queueing.
- Limit SysEx message size and batch size; keep firmware / OS and project transfer unsupported.
- Add bounded ZIP parsing and decompression, duplicate import detection and MIDI input monitoring.
- Add HTML/DOM static audit and ZIP/SysEx regression tests to GitHub Actions.
- Generate and upload a portable ZIP bundle from successful CI runs.

## 3.1 — initial public repository port
- Publish standalone local-first HTML application and bilingual documentation.

Proxy audio remains approximate. No physical Analog Four or Digitone transfer has been certified by these releases.
