# Technical limitations and safe-use notes

## Three kinds of preview
1. **Real audio**: decoded and played by the browser, depending on codec support.
2. **Native sounds (.afsnd/.dnsnd)**: container/payload inspection plus deterministic proxy synthesis. Proprietary synth parameters are not reconstructed.
3. **SysEx**: transport/data, not inherently audio. Raw SysEx messages are not assigned synthetic audio previews. A verified audio recording can be linked manually to an item.

For accurate audition, load the sound into the physical instrument using its supported workflow, connect its audio output to an interface, and record a reference. SoundLab can link that recording to the library item.

## Transfer boundaries
- Elektron Transfer's native AFSND/DNSND USB-MIDI protocol is not implemented.
- Native sound payloads are never sent as raw SysEx.
- Project and firmware transfer are excluded.
- Web MIDI `send()` only queues data in the browser/OS MIDI path; it is not a hardware acknowledgement.
- Manufacturer and 7-bit checks are not complete semantic validation of every Elektron SysEx subtype.
- Selecting Analog Four or Digitone is a user declaration. SoundLab cannot infer the exact target model from every SysEx message.

## SysEx safeguards in v3.2
- An explicit Analog Four / Digitone target must be selected.
- The operator must tick the acknowledgement checkbox and confirm the operation.
- Messages larger than 8 KiB and batches larger than 128 messages are refused.
- Obvious firmware/OS/bootloader names are blocked heuristically, but this cannot detect every firmware payload. **Never send unidentified, firmware, OS or bootloader data.**
- These gates reduce accidental sending; they do not prove that a dump is safe, compatible, or correctly addressed.

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
Processing is local in the current browser tab; there is no upload backend. Imported files and temporary recordings may be lost when the tab is refreshed or closed. Do not import untrusted archives.
