# Changelog

## 3.2 — reliability, audition and transfer safeguards
- Fix sequential audition state so queue playback advances through the selected items.
- Apply attack, release, stereo width and a feedback-delay reverb stage to proxy rendering.
- Stop treating arbitrary SysEx messages as audible preview items; real audio references can still be linked.
- Require an explicit Analog Four / Digitone target and a safety acknowledgement before individual or batch SysEx queueing.
- Limit SysEx message size and batch size; keep firmware / OS and project transfer unsupported.
- Add bounded ZIP parsing and decompression: archive, entry, count, cumulative expansion and compression-ratio limits.
- Add duplicate file detection within the current library and a MIDI input event monitor.
- Fix capture export extension so it follows the browser's actual recording MIME type.
- Add HTML/DOM static audit and ZIP/SysEx regression tests to GitHub Actions.
- Generate and upload a portable ZIP bundle from every successful CI run.

## 3.1 — initial public repository port
- Publish standalone local-first HTML application and bilingual documentation.
- Inventory AFSND / DNSND / SYX / audio / ZIP / project files.
- Add proxy preview, audio-reference linking, capture and WAV export.
- Add conservative SysEx framing checks and Web MIDI queueing.
- Document the unimplemented native Elektron Transfer protocol and proxy/emulation boundary.

Proxy audio remains approximate. No physical Analog Four or Digitone hardware transfer has been certified by this release.
