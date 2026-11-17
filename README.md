# Elektron SoundLab — A4 & Digitone

Local-first sound library, audition workstation and cautious SysEx utility for Elektron Analog Four MKI / Analog Keys and Digitone MK1.

[Français](docs/README.fr.md) · [English](docs/README.en.md) · [Installation](docs/INSTALLATION.md) · [Limitations](docs/LIMITATIONS.md) · [Testing](docs/TESTING.md) · [Roadmap](ROADMAP.md) · [Contributing](CONTRIBUTING.md) · [Security](SECURITY.md)

> **Version 3.2 — experimental / community testing required.** Independent project; not affiliated with Elektron and not a replacement for Elektron Transfer.

## Quick start
Open `index.html` in a recent Chromium browser. Audio and local file inspection work without a server. For Web MIDI/SysEx and audio-input capture on Windows, run `scripts/Lancer_WebMIDI_Chrome_Edge.bat` (Python 3 required), then open `http://localhost:8765`.

## Current features
- Inventory of .afsnd, .dnsnd, .syx, supported audio, ZIP archives and project files.
- Extract accessible manifests/tags from AFSND containers.
- Split complete F0…F7 SysEx messages; conservative manufacturer and 7-bit checks.
- Real audio playback; deterministic proxy synthesis for native sounds; WAV export.
- Link a real recording to a native sound; capture an external audio input.
- Filtering, favourites, sequential audition, JSON inventory and Web MIDI note/SysEx queueing.
- MIDI input monitor for incoming notes, CC and SysEx event summaries.
- Bounded ZIP processing, CRC checks, duplicate import detection and explicit SysEx send acknowledgement.

## Important boundaries
- Native .afsnd/.dnsnd payloads are not decoded into proprietary synthesis parameters. Proxy preview is an approximation, **not an instrument emulator**.
- Elektron Transfer's native USB-MIDI protocol is not implemented. Native sounds are not sent as raw SysEx.
- Web MIDI queueing does not prove that the instrument received, accepted or stored a dump.
- Project and firmware transfer are unsupported.
- SysEx candidates require explicit target selection and a manual safety acknowledgement. This does not establish the message's model compatibility or semantic safety.

Please read [Limitations](docs/LIMITATIONS.md) and [Testing](docs/TESTING.md) before connecting or sending anything. Public feedback belongs in GitHub Issues. Do not upload copyrighted sound banks, firmware, private dumps, serial numbers or personal data.

## License
The repository retains its existing [Unlicense](LICENSE). Elektron is a trademark of its respective owner.
