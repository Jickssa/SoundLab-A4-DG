# SoundLab v3.7 — test plan

This checklist is for reproducible community tests. Distinguish static checks, browser-only checks and physical-device checks. Do not use irreplaceable sound banks or an unbacked-up instrument.

## Automated checks
Run:
```sh
python3 scripts/check_html.py
node scripts/test_parsers.js
node scripts/test_elektron_sound_sysex.js
node scripts/test_persistence.js
node scripts/test_audio_inspector.js
node scripts/test_visual_editor.js
node scripts/test_ab_audition.js
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
- [ ] Import a WAV and verify playback, waveform and WAV export.
- [ ] Verify audio facts show duration, sample rate, channel count and sampled peak/RMS.
- [ ] Change waveform zoom and horizontal position; verify the visible window changes.
- [ ] Change monitoring gain during playback; verify loudness changes while exported WAV remains source-level.
- [ ] Import one AFSND and one DNSND; verify proxy-only preview.
- [ ] Change attack, release, width and reverb separately; regenerate and confirm the proxy changes.
- [ ] Link a real audio file to a native sound; press A then B; verify the first uses the linked recording and the second uses the native proxy.
- [ ] Capture machine audio directly while a native sound is selected; verify the capture becomes available in A and B remains the proxy.
- [ ] Export A and B separately; verify distinct filenames and that A contains the recording while B contains proxy audio.
- [ ] Reload from the same browser origin, restore IndexedDB and verify the direct capture is still selectable in A.
- [ ] Open the visual editor on an imported WAV; drag-select a short region and verify the selection time readout follows zoom/pan.
- [ ] Apply gain to a selection and verify samples outside it do not change; undo and redo the operation.
- [ ] Draw an envelope with no selection and verify it affects only the visible waveform range; repeat with a selection to constrain it.
- [ ] Test fade in/out, normalization to −1 dBFS, reverse, silence and trim; verify undo restores the prior samples and trim length.
- [ ] Play the edited track and selection; export the edited WAV and create an edited library copy.
- [ ] Verify the original imported file remains available unchanged; save and restore the newly created edited copy through IndexedDB.
- [ ] Verify A/reference edits and B/proxy edits stay separate when switching A/B.
- [ ] Confirm files above the 128 MiB editor cap are refused cleanly without partial edits.
- [ ] Verify a raw SysEx item is never proxy-auditionable; with a linked audio recording, only A should be available.
- [ ] Select at least three playable items and test sequential audition.
- [ ] Test ZIP CRC/size/expansion limits and duplicate import detection.
- [ ] Import a known A4 / Digitone Sound .syx bank; verify model, slot, name and tags are shown for the recognized individual Sound frames.
- [ ] Verify messages with a wrong model ID, prefix, checksum, length or 7-bit payload remain non-transferable.
- [ ] Select a different target model and verify a Sound frame cannot be queued to the mismatched device.
- [ ] Verify OS/firmware .syx files are not recognized as individual Sound frames and are never offered for sending.
- [ ] Verify explicit target selection and acknowledgement are required before sending a validated Sound SysEx frame.

## IndexedDB persistence checks
- [ ] Save a library with one native sound, one audio file, a favourite, an audio link and a direct capture.
- [ ] Reload on the same browser profile and exact same origin; restore.
- [ ] Verify source binaries, metadata, favourites, links and capture are restored, and A mode selects the direct capture.
- [ ] Delete the persistent backup; verify the open session remains.
- [ ] Repeat with storage disabled/quota exhausted; verify a useful error appears.

## Hardware validation — optional, not implied by CI
Only use a backed-up instrument and a known-safe, model-specific test message. Verify the receive mode and exact destination. Test one message first. Browser queueing alone is not a pass.

## Report format
Include SoundLab commit, instrument/model and OS version, computer OS, browser version, MIDI/audio interface, file extension and size, steps, expected result, observed result and sanitized logs. Never attach commercial sound packs, firmware, private dumps, serial numbers or personal data.
