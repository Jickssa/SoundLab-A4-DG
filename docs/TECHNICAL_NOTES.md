# Technical notes

## Architecture
Single-file HTML/CSS/JavaScript app; no build step or external runtime dependency. Web Audio API handles decoding/playback, deterministic proxy generation, WAV encoding and audio-input capture. Web MIDI API is requested with SysEx permission where supported.

## File handling
- **AFSND**: ZIP-like container inspected for manifest, payload and accessible metadata. Manifest schemas may vary; fields are not treated as synthesis parameter values.
- **DNSND**: raw binary is retained and inspected conservatively. No full proprietary parameter decoder is claimed.
- **SYX**: complete F0…F7 messages are separated. Manufacturer and 7-bit checks are heuristics, not full semantic validation. Raw SysEx entries are not marked as audible previews.
- **ZIP**: non-encrypted stored/deflate entries are supported; CRC and expanded size are checked. ZIP64 is unsupported. Limits: 128 MiB archive, 2,048 entries, 64 MiB per expanded entry, 256 MiB cumulative expanded content per import batch.
- **Audio**: browser codec support determines whether decodeAudioData succeeds. Recording export uses the actual MediaRecorder MIME type when known.

## Proxy audio
A deterministic seed derived from input bytes/file identity and controls drives generic analog/FM/percussion/texture proxy audio. Attack, release, width and a simple feedback-delay reverb stage affect the render. It is for rough triage and comparison, not sound recreation. No proprietary algorithms, wavetables, parameter mappings or firmware code are included.

## MIDI / SysEx
Web MIDI requires browser/device support and explicit permission. The input monitor logs event summaries and suppresses rapid message flooding. Successful output.send() means the browser accepted the request; it is not a target-device acknowledgement. SysEx sending requires explicit target selection and a user safety acknowledgement. Batch size and individual message size are capped. Firmware/OS detection remains heuristic and must not be relied upon to identify safe data.

## Validation scope
GitHub Actions checks HTML ID uniqueness, JavaScript selector references, mandatory controls, SysEx acknowledgement markup and JavaScript syntax. These static checks do not replace browser tests, codec tests, driver tests or tests with physical Digitone and Analog Four hardware.
