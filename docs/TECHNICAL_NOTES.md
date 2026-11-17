# Technical notes

## Architecture
Single-file HTML/CSS/JavaScript app; no build step or external runtime dependency. Web Audio API handles decoding/playback, deterministic proxy generation, WAV encoding and audio-input capture. Web MIDI API is requested with SysEx permission where supported. IndexedDB stores a user-initiated persistent copy of the library.

## A/B audition
Each native item may have an imported audio reference (`item.ref`) and/or a direct capture blob in `S.captures`. In A/reference mode, the direct capture is preferred; if absent, the linked audio item is decoded. In B/proxy mode, native AFSND/DNSND data is passed to the generic proxy generator. Ordinary audio files always play as their original decoded audio. Other data types such as raw SysEx do not get a proxy sound; an attached reference can only be played in A mode. Export uses the same selection function, so the WAV corresponds to the current A/B mode.

## File handling
- **AFSND**: ZIP-like container inspected for manifest, payload and accessible metadata. Manifest schemas may vary; fields are not treated as synthesis parameter values.
- **DNSND**: raw binary is retained and inspected conservatively. No full proprietary parameter decoder is claimed.
- **SYX**: complete F0…F7 messages are separated. The v3.6 Sound inspector recognizes only a specific Sound subtype with manufacturer ID 00 20 3C, model ID 06 (A4) or 0D (Digitone MK1), prefix 00 53 01 01, valid 8-in-7 payload, checksum and length. It extracts slot, name and 32 tag flags. It does not decode synthesis parameters. Other messages stay inventory-only and are not marked transferable or audible.
- **ZIP**: non-encrypted stored/deflate entries are supported; CRC and expanded size are checked. ZIP64 is unsupported. Limits: 128 MiB archive, 2,048 entries, 64 MiB per expanded entry, 256 MiB cumulative expanded content per import batch.
- **Audio**: browser codec support determines whether decodeAudioData succeeds. Recording export uses the actual MediaRecorder MIME type when known.

## Audio inspector and monitoring
The inspector reports decoded AudioBuffer duration, sample rate and channel count. Peak and RMS are estimates computed by sampling at most 250,000 frames per channel to keep analysis responsive on large buffers. Waveform zoom and horizontal position change the displayed sample window. A Web Audio GainNode controls monitoring level from 0–150%; this does not change source buffers or the WAV export data.

## IndexedDB persistence
The database `ElektronSoundLabLibrary` version 1 contains an `entries` object store. Save writes item metadata and source `Blob`/typed-array payloads plus captured audio blobs in one read-write transaction. Restore reconstructs the in-memory library, recreates object URLs for captures, and lets the browser rebuild decoded AudioBuffers and proxy previews on demand. Delete removes the persistent store contents but does not clear the current session. Persistence is manual and bound to the current browser profile/origin. Browser quota, eviction and site-data clearing remain outside the application's control.

## Proxy audio
A deterministic seed derived from input bytes/file identity and controls drives generic analog/FM/percussion/texture proxy audio. Attack, release, width and a simple feedback-delay reverb stage affect the render. It is for rough triage and comparison, not sound recreation. No proprietary algorithms, wavetables, parameter mappings or firmware code are included.

## MIDI / SysEx
v3.6 sending is restricted to validated individual Sound frames whose embedded model ID matches the selected target. Generic SysEx, project/pattern dumps and firmware-like names are not sendable through this path. See [Sound SysEx format](SYSEX_SOUND_FORMAT.md) for the observed layout and explicit boundaries.
Web MIDI requires browser/device support and explicit permission. The input monitor logs event summaries and suppresses rapid message flooding. Successful output.send() means the browser accepted the request; it is not a target-device acknowledgement. SysEx sending requires explicit target selection and a user safety acknowledgement. Batch size and individual message size are capped. Firmware/OS detection remains heuristic and must not be relied upon to identify safe data.

## Validation scope
The v3.6 parser regression test uses synthetic A4/Digitone Sound frames and exercises checksum, length, model, prefix, 7-bit and metadata extraction. GitHub Actions checks HTML ID uniqueness, JavaScript selector references, required controls, SysEx acknowledgement markup, IndexedDB and audio-inspector controls, parser/A-B regression tests and JavaScript syntax. It also builds and validates the portable ZIP artifact. These checks do not replace physical Digitone and Analog Four tests.
