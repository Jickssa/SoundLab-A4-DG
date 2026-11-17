# Elektron SoundLab — A4 & Digitone

Local-first sound library, audition workstation and cautious SysEx utility for Elektron Analog Four MKI / Analog Keys and Digitone MK1.

[Français](docs/README.fr.md) · [English](docs/README.en.md) · [Installation](docs/INSTALLATION.md) · [Limitations](docs/LIMITATIONS.md) · [Testing](docs/TESTING.md) · [Roadmap](ROADMAP.md) · [Contributing](CONTRIBUTING.md) · [Security](SECURITY.md)

> **Version 3.5 — experimental / community testing required.** Independent project; not affiliated with Elektron and not a replacement for Elektron Transfer.

## Quick start
Open `index.html` in a recent Chromium browser. Audio and local file inspection work without a server. Optional IndexedDB persistence lets you save and restore the local library in the current browser profile/origin. Each successful GitHub Actions run also publishes a portable ZIP artifact. For Web MIDI/SysEx and audio-input capture on Windows, run `scripts/Lancer_WebMIDI_Chrome_Edge.bat` (Python 3 required), then open `http://localhost:8765`.

## Current features
- Inventory of .afsnd, .dnsnd, .syx, supported audio, ZIP archives and project files.
- Extract accessible manifests/tags from AFSND containers.
- Split complete F0…F7 SysEx messages; conservative manufacturer and 7-bit checks.
- Real audio playback; deterministic proxy synthesis for native sounds; WAV export.
- Link an imported audio file or a direct machine input capture to a native sound.
- **A/B audition**: A plays the real linked recording/capture; B plays the deterministic proxy of the native sound. WAV export follows the selected A/B mode.
- Audio inspector: duration, sample rate, channel count and sampled peak/RMS estimates.
- Waveform zoom/pan and separate monitoring gain (does not alter the exported source WAV).
- Filtering, favourites, sequential audition, JSON inventory and Web MIDI note/SysEx queueing.
- MIDI input monitor, bounded ZIP processing, duplicate detection and guarded SysEx sending.
- Optional local IndexedDB save/restore for source files, metadata, favourites, audio links and recorded captures.

## Important boundaries
- Native .afsnd/.dnsnd payloads are not decoded into proprietary synthesis parameters. Proxy preview is an approximation, **not an instrument emulator**.
- A-mode recordings are references recorded/imported by the user; they are not a decode of the proprietary patch.
- Raw SysEx data is not synthesized. A SysEx item is audible only when a real audio reference/capture is attached.
- Elektron Transfer's native USB-MIDI protocol is not implemented. Native sounds are not sent as raw SysEx.
- Web MIDI queueing does not prove that the instrument received, accepted or stored a dump.
- Project and firmware transfer are unsupported.
- IndexedDB is browser-local storage, not cloud sync or a substitute for independent backups.

Please read [Limitations](docs/LIMITATIONS.md) and [Testing](docs/TESTING.md) before connecting or sending anything. Public feedback belongs in GitHub Issues. Do not upload copyrighted sound banks, firmware, private dumps, serial numbers or personal data.

## License
The repository retains its existing [Unlicense](LICENSE). Elektron is a trademark of its respective owner.
