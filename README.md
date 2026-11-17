# Elektron SoundLab — A4 & Digitone

A local-first sound library, audition workstation and cautious SysEx utility for Elektron Analog Four MKI / Analog Keys and Digitone MK1.

[Français](docs/README.fr.md) · [English](docs/README.en.md) · [Installation](docs/INSTALLATION.md) · [Limitations](docs/LIMITATIONS.md) · [Roadmap](ROADMAP.md) · [Contributing](CONTRIBUTING.md) · [Security](SECURITY.md)

> **Status: experimental / community testing required.** Independent project; not affiliated with Elektron and not a replacement for Elektron Transfer.

## Quick start
Open `index.html` in a recent Chromium browser. Audio and local file inspection work without a server. For Web MIDI/SysEx and audio-input capture on Windows, run `scripts/Lancer_WebMIDI_Chrome_Edge.bat` (Python 3 required), then open `http://localhost:8765`.

## Current features
- Inventory of .afsnd, .dnsnd, .syx, supported audio, ZIP archives and project files.
- Extract accessible manifests/tags from AFSND containers.
- Split complete F0…F7 SysEx messages; conservative manufacturer/7-bit checks.
- Browser audio playback; deterministic proxy preview of native sound payloads; WAV export.
- Link a real audio recording to a native sound; short external input capture.
- Filtering, favourites, sequential audition, JSON inventory and Web MIDI note/SysEx queueing.

## Important boundaries
- Native .afsnd/.dnsnd payloads are not decoded into proprietary synthesis parameters. Proxy preview is an approximation, **not an instrument emulator**.
- Elektron Transfer's native USB-MIDI protocol is not implemented. Native sounds are not sent as raw SysEx.
- Web MIDI queueing does not prove that the instrument received, accepted or stored a dump.
- Project and firmware transfer are unsupported.

Please read [Limitations](docs/LIMITATIONS.md) before sending SysEx. Public feedback belongs in GitHub Issues. Do not upload copyrighted sound banks, firmware, private dumps, serial numbers or personal data.

## License
The repository retains its existing [Unlicense](LICENSE). Elektron is a trademark of its respective owner.
