# Technical limitations and safe-use notes

## Three kinds of preview
1. **Real audio**: decoded and played by the browser, depending on codec support.
2. **Native sounds (.afsnd/.dnsnd)**: container/payload inspection plus deterministic proxy preview. Proprietary synth parameters are not reconstructed.
3. **SysEx**: a transport/data format, not inherently audio. A SysEx message is not automatically a sound patch.

For accurate audition, load the sound into the physical instrument using its supported workflow, connect its audio output to an interface, and record a reference. SoundLab can link that recording to the library item.

## Transfer boundaries
- Elektron Transfer's native AFSND/DNSND USB-MIDI protocol is not implemented.
- Native sound payloads are never sent as raw SysEx.
- Project and firmware transfer are excluded.
- Web MIDI `send()` only queues data in the browser/OS MIDI path; it is not a hardware acknowledgement.
- Manufacturer and 7-bit checks are not complete semantic validation of every Elektron SysEx subtype.

## Before sending SysEx
1. Back up the receiving instrument and relevant banks.
2. Verify origin and exact target model.
3. Check MIDI output and routing.
4. Put the instrument explicitly into the appropriate receive mode and choose a safe destination.
5. Send one known-safe test message before any batch.
6. Verify on the instrument that data arrived and existing data was not overwritten.

Do not send firmware, bootloader, OS, project or unidentified dumps through this tool.

## Privacy
Processing is local in the current browser tab; there is no upload backend. Imported files and temporary recordings may be lost when the tab is refreshed or closed. Do not import untrusted archives. Encrypted ZIP, ZIP64 and unsupported compression may be rejected.
