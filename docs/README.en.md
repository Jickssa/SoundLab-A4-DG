# Elektron SoundLab — Analog Four & Digitone

A local-first sound library, audition workstation and cautious SysEx utility for the Analog Four MKI / Analog Keys and Digitone MK1.

[Français](README.fr.md) · [Installation](INSTALLATION.md) · [Limitations](LIMITATIONS.md) · [Testing](TESTING.md) · [Sound SysEx format](SYSEX_SOUND_FORMAT.md) · [Roadmap](../ROADMAP.md) · [Contributing](../CONTRIBUTING.md) · [Security](../SECURITY.md)

> **Version 3.6 — experimental; community testing required.** Independent project, not affiliated with Elektron. SoundLab is not a replacement for Elektron Transfer.

## Quick start
Open `index.html` in a recent Chromium browser. Audio and local file inspection work without a server. For Web MIDI/SysEx and audio-input capture on Windows, run `scripts/Lancer_WebMIDI_Chrome_Edge.bat` (Python 3 required), then open `http://localhost:8765`.

## Features
- Inventory .afsnd, .dnsnd, .syx, supported audio, ZIP archives and project files.
- Extract accessible AFSND manifests and tags.
- Structured inspection of A4 / Digitone Sound SysEx frames: model, slot, name, tags, checksum and length.
- Browser audio playback, analog/FM/percussion proxy synthesis and WAV export.
- Link imported audio files or direct machine input captures to native sounds.
- **A/B audition**: A plays the real linked recording/capture; B plays the deterministic native-sound proxy. WAV export follows the active mode.
- Audio inspector: duration, sample rate, channel count and sampled peak/RMS estimates.
- Waveform zoom and horizontal navigation; separate monitoring gain.
- Filtering, favourites, sequential audition, JSON inventory and MIDI input monitoring.
- Queue only recognized, validated Sound SysEx frames, with an exact match between the message model and selected target. Other SysEx messages remain non-transferable.
- Optional IndexedDB persistence for imported files, metadata, favourites, audio references and captured audio.

## A/B comparison
After linking an imported recording or recording the instrument's audio output directly, use **A · Real capture** to audition that actual audio and **B · Proxy** to hear SoundLab's generated approximation. A direct capture is preferred for A; otherwise the linked audio file is used. B is enabled only for native AFSND/DNSND items.

Raw SysEx is data, not sound, and is never given an arbitrary proxy tone. If a SysEx item has a linked recording, only that real audio can be played in A mode.

## Local persistence
Use **Save locally**, **Restore** and **Delete backup** to manage the browser's IndexedDB copy. No files are uploaded. Restore from the same origin and browser profile. Clearing site data or the browser profile may delete this local copy; retain original source files and independent backups.

## Important limitations
- Proprietary .afsnd/.dnsnd parameters are not decoded. Proxy playback is an approximation, **not an instrument emulator**.
- A-mode audio is a user-provided recording/capture, not a decode of the proprietary patch.
- Peak/RMS figures are sampled estimates, not exhaustive offline measurements.
- SysEx inspection extracts Sound metadata only (model, slot, name, tags); it does not decode synthesis parameters.
- SysEx messages other than recognized individual Sound frames are not offered for sending. Checksum and length checks do not certify hardware compatibility.
- Elektron Transfer's native USB-MIDI protocol is not implemented. Native .afsnd/.dnsnd containers are not transferred as raw SysEx.
- Web MIDI queueing does not prove that the instrument received, accepted or stored a dump.
- Project and firmware transfer are unsupported.
- IndexedDB is local browser storage, not cloud sync or a guaranteed archival backup.

Read [Limitations](LIMITATIONS.md) and [Testing](TESTING.md) before sending SysEx. Do not publish copyrighted sound banks, firmware, private dumps, serial numbers or personal data.
