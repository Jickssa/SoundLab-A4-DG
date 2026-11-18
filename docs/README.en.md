# Elektron SoundLab — Analog Four & Digitone

A local-first sound library, structured inspection utility, A/B audition workstation and visual audio editor for Elektron Analog Four MKI / Analog Keys and Digitone MK1.

[Français](README.fr.md) · [Installation](INSTALLATION.md) · [Architecture](TECHNICAL_NOTES.md) · [Limitations](LIMITATIONS.md) · [Testing](TESTING.md) · [Sound SysEx format](SYSEX_SOUND_FORMAT.md) · [Roadmap](../ROADMAP.md) · [Changelog](../CHANGELOG.md) · [Contributing](../CONTRIBUTING.md) · [Security](../SECURITY.md)

> **v3.7 — experimental; community validation required.** Independent project, not affiliated with Elektron and not a replacement for Elektron Transfer.

## Overview

SoundLab is a standalone HTML/CSS/JavaScript browser application for organizing, inspecting and auditioning files associated with the Analog Four MKI / Analog Keys and Digitone MK1. It keeps native files, user-provided audio references, generated proxy previews and limited MIDI/SysEx utilities in one local-first workspace. No application server, user account or library upload is required for the local inventory and audio workflows.

## Features

- **Library**: import and inventory `.afsnd`, `.dnsnd`, `.syx`, browser-supported audio, ZIP archives and recognized project files.
- **Inspection**: conservative extraction of accessible AFSND manifests/tags and structured inspection of one recognized Sound SysEx subtype (model, slot, name, tags, length and checksum).
- **Audition**: real audio playback and deterministic generic proxy rendering for native sounds.
- **A/B comparison**: A uses a real instrument capture or linked audio file; B uses SoundLab's generated proxy. WAV export follows the active source.
- **Audio inspector**: duration, sample rate, channel count, sampled peak/RMS estimates and waveform navigation.
- **Visual editor (v3.7)**: mouse/touch time selection, hand-drawn gain envelope, gain, fades, −1 dBFS normalization, reverse, silence, trim, selection playback, undo/redo and WAV export.
- **Non-destructive copies**: create a new edited WAV library item without overwriting the imported source or recording.
- **Library utilities**: filtering, favourites, sequential audition, JSON inventory and optional local IndexedDB persistence.
- **MIDI/SysEx**: MIDI input monitoring and queueing restricted to recognized, valid Sound frames matching the declared target model.

## Quick start

Clone or download the repository, or download a portable ZIP from a successful GitHub Actions run. Open `index.html` in a recent Chrome or Edge browser and import audio or sound libraries. For Web MIDI/SysEx and audio-input capture on Windows, run `scripts/Lancer_WebMIDI_Chrome_Edge.bat` (Python 3 required), then open `http://localhost:8765`. Grant browser permissions deliberately and check the selected audio/MIDI devices. See the [installation guide](INSTALLATION.md).

## Visual editor memory limits

| Resource | Limit |
|---|---:|
| Working buffer per track | 128 MiB |
| Undo/redo history | 128 MiB |
| Aggregate working buffers and history per session | 256 MiB |

Edits are session-memory state until exported or copied into the library. The editor changes a private decoded AudioBuffer, not the original imported Blob, capture, or native sound payload. A/reference and B/proxy edit states are isolated.

## Important limitations

- Proprietary synthesis parameters inside `.afsnd` / `.dnsnd` are not decoded. Proxy audio is deterministic approximation, not faithful emulation.
- Editing B mode changes only the generated proxy waveform; it does not alter the native Elektron preset.
- Raw SysEx is data, not audio. Only the supported Sound subtype is inspected; synthesis parameters are not decoded.
- Elektron Transfer's native USB-MIDI protocol, project transfer and firmware transfer are not implemented.
- Web MIDI `send()` is not a hardware acknowledgement.
- Automated tests and static checks do not replace real-browser interaction testing or physical Analog Four/Digitone validation.

Read [limitations and safe-use notes](LIMITATIONS.md) before any MIDI/SysEx operation.

## Tests and CI

Automated tests cover parsers, the supported Sound SysEx format, IndexedDB persistence, audio inspection, the visual editor, A/B audition and JavaScript syntax. GitHub Actions runs the checks, builds a portable ZIP and uploads it as a workflow artifact. See the [test plan](TESTING.md) and the repository [Actions tab](https://github.com/Jickssa/SoundLab-A4-DG/actions).

## Project documentation

- [French guide](README.fr.md)
- [Installation and usage](INSTALLATION.md)
- [Technical notes and architecture](TECHNICAL_NOTES.md)
- [Limitations and safety](LIMITATIONS.md)
- [Test plan](TESTING.md)
- [Observed Sound SysEx format](SYSEX_SOUND_FORMAT.md)
- [Roadmap](../ROADMAP.md) and [changelog](../CHANGELOG.md)
- [Contributing](../CONTRIBUTING.md) · [Security](../SECURITY.md) · [License](../LICENSE)

## Project status

Version 3.7 is developed on a feature branch and tracked by an open pull request. The features described here refer to that development branch; they are not a certification of the default branch or of physical hardware compatibility.

Repository: https://github.com/Jickssa/SoundLab-A4-DG  
v3.7 pull request: https://github.com/Jickssa/SoundLab-A4-DG/pull/7

## License and independence

The repository includes the Unlicense. Elektron, Analog Four, Analog Keys and Digitone names are used solely to identify the target products. SoundLab is an independent project and is not developed, endorsed or supported by Elektron.
