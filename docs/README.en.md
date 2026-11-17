# Elektron SoundLab — Analog Four & Digitone

A local-first sound library, audition workstation and cautious SysEx utility for the Analog Four MKI / Analog Keys and Digitone MK1.

[Français](README.fr.md) · [Installation](INSTALLATION.md) · [Limitations](LIMITATIONS.md) · [Testing](TESTING.md) · [Roadmap](../ROADMAP.md) · [Contributing](../CONTRIBUTING.md) · [Security](../SECURITY.md)

> **Version 3.2 — experimental; community testing required.** Independent project, not affiliated with Elektron. SoundLab is not a replacement for Elektron Transfer.

## Quick start
Open `index.html` in a recent Chromium browser. Audio and local file inspection work without a server. For Web MIDI/SysEx and audio-input capture on Windows, run `scripts/Lancer_WebMIDI_Chrome_Edge.bat` (Python 3 required), then open `http://localhost:8765`.

## Features
- Inventory .afsnd, .dnsnd, .syx, supported audio, ZIP archives and project files.
- Extract accessible AFSND manifests and tags.
- Split complete F0…F7 SysEx messages with conservative manufacturer / 7-bit checks.
- Browser audio playback, analog/FM/percussion proxy synthesis and WAV export.
- Effective proxy controls: attack, release, stereo width, modulation, brightness and delay-based reverb.
- Link a real recording to a native sound, capture external audio and audition a selected sequence.
- Filtering, favourites, JSON inventory and MIDI input monitoring.
- Guarded SysEx queueing with explicit target selection, user acknowledgement, confirmation and size limits.

## Important limitations
- Proprietary .afsnd/.dnsnd parameters are not decoded. Proxy playback is an approximation, **not an instrument emulator**.
- Elektron Transfer's native USB-MIDI protocol is not implemented. Native sounds are not sent as raw SysEx.
- Raw SysEx messages are not presented as audible previews. Link a real recording or load the patch on hardware.
- Web MIDI queueing does not prove that the instrument received, accepted or stored a dump.
- Project and firmware transfer are unsupported.

Read [Limitations](LIMITATIONS.md) and [Testing](TESTING.md) before sending SysEx. Do not publish copyrighted sound banks, firmware, private dumps, serial numbers or personal data.
