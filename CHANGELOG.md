# Changelog

## 3.6 — Sound SysEx inspection
- Identify the supported individual Elektron Sound SysEx frame subtype for Analog Four / Analog Keys and Digitone MK1.
- Validate manufacturer/model IDs, Sound prefix, 8-in-7 payload, checksum and length before exposing Sound metadata.
- Extract Sound slot, name and model-specific tags without claiming synthesis-parameter decoding.
- Restrict MIDI queueing to validated Sound frames whose model matches the selected target; other SysEx remains inventory-only.
- Add synthetic parser regression fixtures for A4 and Digitone, including malformed and mismatched frames.
- Document the observed format, external research references and hardware-validation boundary.

## 3.5 — A/B audition
- Add A/B audition between a direct instrument input capture or linked imported audio (A) and the native sound proxy (B).
- Prefer a direct capture attached to the selected patch; fall back to its linked audio file.
- Keep the A/B source selection consistent in playback and WAV export.
- Restore A/B reference mode when IndexedDB restores an item with a link or direct capture.
- Keep raw SysEx as non-audible data; if a real recording is attached, only A mode is available.
- Add dedicated A/B routing regression tests.

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
- Keep persistence manual and browser-origin/profile scoped.

## 3.2 — reliability, audition and transfer safeguards
- Fix sequential audition and add SysEx/ZIP validation safeguards.
- Add MIDI input monitoring, explicit target selection and acknowledgement.
- Add HTML/DOM static audit and ZIP/SysEx regression tests to GitHub Actions.

## 3.1 — initial public repository port
- Publish standalone local-first HTML application and bilingual documentation.

Proxy audio remains approximate. No physical Analog Four or Digitone transfer has been certified by these releases.
