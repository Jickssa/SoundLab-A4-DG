# Technical limitations and safe-use notes

## Three kinds of preview
1. **Real audio**: decoded and played by the browser, depending on codec support.
2. **Native sounds (.afsnd/.dnsnd)**: container/payload inspection plus deterministic proxy synthesis. Proprietary synth parameters are not reconstructed.
3. **SysEx**: transport/data, not inherently audio. In v3.6 only one individual Sound subtype is structurally recognized for A4 and Digitone; the parser extracts model, slot, name and tags after frame, checksum and length checks. It does not decode synthesis parameters. Other SysEx messages remain raw data and are not assigned synthetic audio previews. A verified audio recording can be linked manually to an item.

For accurate audition, load the sound into the physical instrument using its supported workflow, connect its audio output to an interface, and record a reference. SoundLab can link that recording to the library item or retain a direct input capture on the selected patch.

## A/B audition in v3.5
- **A / Real reference** uses a direct capture associated with the selected native item when available; otherwise it uses the linked imported audio file.
- **B / Proxy** uses the generic deterministic proxy renderer for native AFSND/DNSND items only.
- Exported WAV follows the selected A/B source. A is a user-provided recording, not a decode of the patch.
- Ordinary audio files always play as their original audio.
- Raw SysEx has no proxy audio mode. If a SysEx item has an associated recording, only the real recording is audible.
- Direct capture and imported audio references remain local; persistence is opt-in via IndexedDB.

## Visual audio editor in v3.7
- Editing applies to a private in-memory AudioBuffer copy of the selected audio source; source files, capture blobs and native payloads are not overwritten.
- Available sources are decoded audio files, A/reference recordings and B/proxy render buffers. For native AFSND/DNSND, only the generated proxy waveform is edited; native synthesis parameters are not decoded or changed.
- One working buffer is limited to 128 MiB, undo/redo history is capped at 128 MiB, and all working buffers plus history across the session are capped at 256 MiB. Use **Libérer mémoire** to discard an unexported edit, or create an edited WAV copy (which releases the prior working buffer). Large files may need to be shortened or converted before editing.
- PCM WAV export is 16-bit and clamps samples outside ±1. SoundLab warns when processing creates peaks above 0 dBFS; normalize before export to avoid hard clipping.
- Session edit history is memory-only. Export the result or create a new WAV copy in the library, then save the library if persistence is required.
- Envelope drawing is a sampled linear interpolation of user-drawn points, not an automation lane or parametric envelope in the instrument.

## Audio inspector in v3.4
- Duration, sample rate and channel count describe the decoded AudioBuffer presented to the browser; resampling may have occurred during decoding.
- Peak and RMS are sampled estimates (up to 250,000 frames per channel), not a full precision forensic measurement.
- Waveform zoom and position only change the displayed window.
- Monitoring gain changes playback level only. It does not modify the source blob, decoded buffer or exported WAV.

## Transfer boundaries
- Elektron Transfer's native AFSND/DNSND USB-MIDI protocol is not implemented.
- Native sound payloads are never sent as raw SysEx.
- Project and firmware transfer are excluded.
- Web MIDI `send()` only queues data in the browser/OS MIDI path; it is not a hardware acknowledgement.
- v3.6 recognizes one Sound SysEx subtype only; this does not validate Patterns, Projects, firmware, global dumps or every other Elektron SysEx subtype.
- Only a recognized Sound frame can be queued; its embedded model ID must match the selected target. This is still not a hardware compatibility certification.
- Selecting Analog Four or Digitone is a user declaration, and the browser queue is not a hardware receipt.

## SysEx safeguards in v3.2–v3.6
- An explicit Analog Four / Digitone target must be selected.
- The operator must tick the acknowledgement checkbox and confirm the operation.
- Messages larger than 8 KiB and batches larger than 128 messages are refused.
- Obvious firmware/OS/bootloader names are blocked heuristically, but this cannot detect every firmware payload. **Never send unidentified, firmware, OS or bootloader data.**
- v3.6 further restricts sending to Sound frames with a recognized model ID, Sound prefix, 8-in-7 payload, checksum and length. Non-Sound messages are inventory-only.
- These gates reduce accidental sending; they do not prove that a dump is safe, compatible, or correctly addressed.

## Local persistence in v3.3
- Optional manual save/restore uses IndexedDB in the current browser profile and origin.
- No sound data is sent to GitHub, a server or a cloud service by these controls.
- Browser storage can be cleared, evicted or made unavailable by browser settings; quotas vary.
- A local IndexedDB copy is not a guaranteed archive and does not replace the original source files or independent backups.
- Use the same origin and browser profile to restore (for example, do not switch between `file://` and `http://localhost:8765`).
- Captured audio blobs are persisted as source blobs; decoded AudioBuffer caches and object URLs are rebuilt.

## Before sending SysEx
1. Back up the receiving instrument and relevant banks.
2. Verify the source and exact target model independently.
3. Check MIDI output and routing.
4. Put the instrument explicitly into the appropriate receive mode and choose a safe destination.
5. Start with one known-safe, model-specific message.
6. Verify on the instrument that data arrived and existing data was not overwritten.

## ZIP and file import limits
- ZIP archives: maximum 128 MiB.
- ZIP entries: maximum 2,048; individual expanded entry maximum 64 MiB.
- Cumulative expanded data per import batch: maximum 256 MiB.
- Suspicious compression ratios are rejected; CRC and declared expanded size are checked.
- ZIP64, encrypted ZIP entries and unsupported compression methods are not supported.
- Source files are limited to 256 MiB each and a 512 MiB selection batch.

These are defensive client-side bounds, not a guarantee that every malformed archive is harmless. Import files only from sources you trust.

## Privacy
Imported files, captures and saved library records stay in the browser's local storage mechanisms; there is no upload backend. Do not import untrusted archives or treat browser storage as a secure backup.
