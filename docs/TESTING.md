# SoundLab v3.4 — test plan

This checklist is for reproducible community tests. Distinguish static checks, browser-only checks and physical-device checks. Do not use irreplaceable sound banks or an unbacked-up instrument.

## Automated checks
Run:
```sh
python3 scripts/check_html.py
node scripts/test_parsers.js
node scripts/test_persistence.js
node scripts/test_audio_inspector.js
python3 - <<'PY'
from pathlib import Path
html = Path("index.html").read_text(encoding="utf-8")
js = html.split("<script>", 1)[1].split("</script>", 1)[0]
Path("/tmp/soundlab.js").write_text(js, encoding="utf-8")
PY
node --check /tmp/soundlab.js
python3 scripts/package_portable.py
```
GitHub Actions runs the same checks and uploads the portable ZIP artifact.

## Browser test matrix
- [ ] Open the standalone file in Chrome / Edge.
- [ ] Import one WAV and verify playback, waveform and WAV export.
- [ ] Import one supported compressed audio file; record any browser/codec failure.
- [ ] Verify audio facts show duration, sample rate, channel count and sampled peak/RMS.
- [ ] Change waveform zoom and horizontal position; verify the visible window changes.
- [ ] Change monitoring gain during playback; verify loudness changes while exported WAV remains source-level.
- [ ] Import one AFSND and one DNSND; verify proxy-only preview.
- [ ] Change attack, release, width and reverb separately; regenerate and confirm the proxy changes.
- [ ] Link a real audio file to a native sound; verify Play and WAV export use that recording.
- [ ] Capture a short audio input and verify the exported extension matches the recording format.
- [ ] Select at least three playable items and test sequential audition.
- [ ] Import the same path twice; verify duplicate detection.
- [ ] Import a small ZIP with stored and deflate entries; verify CRC and nested archive handling.
- [ ] Verify encrypted, ZIP64, oversized and malformed ZIPs are rejected.
- [ ] Import a SysEx file; verify raw messages are not marked as audio-previewable.
- [ ] Verify explicit target selection and acknowledgement are required before sending.

## IndexedDB persistence checks
- [ ] Save a library containing one native sound, one audio file, a favourite, an audio link and a capture.
- [ ] Reload on the same browser profile and exact same origin; restore.
- [ ] Verify binaries, metadata, favourites, links and capture are restored.
- [ ] Delete the persistent backup; verify the open session remains.
- [ ] Repeat with storage disabled/quota exhausted; verify a useful error appears.

## Hardware validation — optional, not implied by CI
Only use a backed-up instrument and a known-safe, model-specific test message. Verify the receive mode and exact destination. Test one message first. Browser queueing alone is not a pass.

## Report format
Include SoundLab commit, instrument/model and OS version, computer OS, browser version, MIDI/audio interface, file extension and size, steps, expected result, observed result and sanitized logs. Never attach commercial sound packs, firmware, private dumps, serial numbers or personal data.
