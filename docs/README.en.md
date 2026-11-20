# Elektron SoundLab — Analog Four & Digitone

A local-first sound library, audition workstation and cautious SysEx utility for the Analog Four MKI / Analog Keys and Digitone MK1.

[Français](README.fr.md) · [Installation](INSTALLATION.md) · [Limitations](LIMITATIONS.md) · [Roadmap](../ROADMAP.md) · [Contributing](../CONTRIBUTING.md) · [Security](../SECURITY.md)

> **Status: experimental; community testing is required.** Independent project, not affiliated with Elektron. SoundLab is not a replacement for Elektron Transfer.

## Quick start
Open `index.html` in a recent Chromium browser. Audio and local file inspection work without a server. For Web MIDI/SysEx and audio-input capture on Windows, run `scripts/Lancer_WebMIDI_Chrome_Edge.bat` (Python 3 required), then open `http://localhost:8765`.

## Features
- Inventory .afsnd, .dnsnd, .syx, supported audio, ZIP archives and project files.
- Extract accessible manifests/tags from AFSND containers.
- Split complete F0…F7 SysEx messages; conservative manufacturer/7-bit checks.
- Browser audio playback; deterministic proxy previews for native payloads; WAV export.
- Link real audio recordings to native sounds and capture external audio input.
- Filtering, favourites, sequential audition, JSON inventory and Web MIDI note/SysEx queueing.

## Important limitations
- Proprietary synthesis parameters are not decoded from .afsnd/.dnsnd payloads. Proxy playback is an approximation, **not an instrument emulator**.
- Elektron Transfer's native USB-MIDI protocol is not implemented. Native sounds are not sent as raw SysEx.
- Web MIDI queueing does not prove that the instrument received, accepted or stored a dump.
- Project and firmware transfer are unsupported.

Read [Limitations](LIMITATIONS.md) before sending SysEx. Use GitHub Issues for feedback. Do not upload copyrighted sound banks, firmware, private dumps, serial numbers or personal data.

## License
The repository retains its existing [Unlicense](../LICENSE). Elektron is a trademark of its respective owner.
