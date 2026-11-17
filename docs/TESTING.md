# SoundLab v3.2 — test plan

This checklist is for reproducible community tests. Distinguish static checks, browser-only checks and physical-device checks. Do not use irreplaceable sound banks or an unbacked-up instrument.

## Automated checks
Run:
```sh
python3 scripts/check_html.py
python3 - <<'PY'
from pathlib import Path
html = Path("index.html").read_text(encoding="utf-8")
js = html.split("<script>", 1)[1].split("</script>", 1)[0]
Path("/tmp/soundlab.js").write_text(js, encoding="utf-8")
PY
node --check /tmp/soundlab.js
```
GitHub Actions runs the same checks on pushes and pull requests.

## Browser test matrix
- [ ] Open the standalone file in Chrome / Edge.
- [ ] Import one WAV and verify playback, waveform and WAV export.
- [ ] Import one supported compressed audio file; record any browser/codec failure.
- [ ] Import one AFSND and one DNSND; verify they are listed as native sounds and rendered as proxy previews only.
- [ ] Change attack, release, width and reverb separately; regenerate and confirm the preview changes.
- [ ] Link a real audio file to a native sound; verify Play and WAV export use that recording.
- [ ] Capture a short audio input and verify the exported extension matches the recording format.
- [ ] Select at least three playable items and test sequential audition; confirm it advances until the end.
- [ ] Import the same path twice; verify duplicate detection.
- [ ] Import a small ZIP with stored and deflate entries; verify CRC and nested archive handling.
- [ ] Verify encrypted, ZIP64, oversized and malformed ZIPs are rejected with a useful log.
- [ ] Import a SysEx file; verify raw messages are not marked as audio-previewable.
- [ ] Verify an explicit target and the acknowledgement checkbox are required before sending.
- [ ] Test MIDI IN event summaries with a harmless controller or keyboard.

## Hardware validation — optional, not implied by CI
Only use a backed-up instrument and a known-safe, model-specific test message. Verify the instrument receive menu and exact destination. Test one message first. Record whether the instrument itself confirms receipt and whether the expected data appears. Browser queueing alone is not a pass.

## Report format
Include SoundLab commit, instrument/model and OS version, computer OS, browser version, MIDI/audio interface, file extension and size, steps, expected result, observed result and sanitized logs. Never attach commercial sound packs, firmware, private dumps, serial numbers or personal data.
