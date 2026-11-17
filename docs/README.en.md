# Elektron SoundLab — Analog Four & Digitone

A local-first sound library, audition workstation and cautious SysEx utility for the Analog Four MKI / Analog Keys and Digitone MK1.

[Français](README.fr.md) · [Installation](INSTALLATION.md) · [Limitations](LIMITATIONS.md) · [Testing](TESTING.md) · [Roadmap](../ROADMAP.md) · [Contributing](../CONTRIBUTING.md) · [Security](../SECURITY.md)

> **Version 3.4 — experimental; community testing required.** Independent project, not affiliated with Elektron. SoundLab is not a replacement for Elektron Transfer.

## Quick start
Open `index.html` in a recent Chromium browser. Audio and local file inspection work without a server. For Web MIDI/SysEx and audio-input capture on Windows, run `scripts/Lancer_WebMIDI_Chrome_Edge.bat` (Python 3 required), then open `http://localhost:8765`.

## Features
- Inventory .afsnd, .dnsnd, .syx, supported audio, ZIP archives and project files.
- Extract accessible AFSND manifests and tags.
- Browser audio playback, analog/FM/percussion proxy synthesis and WAV export.
- Link real recordings to native sounds and capture external audio.
- Audio inspector: duration, sample rate, channel count and sampled peak/RMS estimates.
- Waveform zoom and horizontal navigation.
- Monitoring gain separate from the source file; WAV export is not altered by the audition gain.
- Filtering, favourites, sequential audition, JSON inventory and MIDI input monitoring.
- Guarded SysEx queueing with explicit target selection, user acknowledgement, confirmation and size limits.
- Optional IndexedDB persistence for imported files, metadata, favourites, audio references and captured audio.

## Local persistence
Use **Save locally**, **Restore** and **Delete backup** to manage the browser's IndexedDB copy. No files are uploaded. Restore from the same origin and browser profile. Clearing site data or the browser profile may delete this local copy; retain original source files and independent backups.

## Important limitations
- Proprietary .afsnd/.dnsnd parameters are not decoded. Proxy playback is an approximation, **not an instrument emulator**.
- Peak/RMS figures are sampled estimates, not exhaustive offline measurements.
- Elektron Transfer's native USB-MIDI protocol is not implemented. Native sounds are not sent as raw SysEx.
- Raw SysEx messages are not presented as audible previews.
- Web MIDI queueing does not prove that the instrument received, accepted or stored a dump.
- Project and firmware transfer are unsupported.
- IndexedDB is local browser storage, not cloud sync or a guaranteed archival backup.

Read [Limitations](LIMITATIONS.md) and [Testing](TESTING.md) before sending SysEx. Do not publish copyrighted sound banks, firmware, private dumps, serial numbers or personal data.
