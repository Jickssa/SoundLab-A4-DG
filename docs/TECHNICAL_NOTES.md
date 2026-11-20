# Technical notes

## Architecture
Single-file HTML/CSS/JavaScript app; no build step or external runtime dependency. Web Audio API handles decoding/playback, deterministic proxy generation, WAV encoding and audio-input capture. Web MIDI API is requested with SysEx permission where supported.

## File handling
- **AFSND**: ZIP-like container inspected for manifest, payload and accessible metadata. Manifest schemas may vary; fields are not treated as synthesis parameter values.
- **DNSND**: raw binary is retained and inspected conservatively. No full proprietary parameter decoder is claimed.
- **SYX**: complete F0…F7 messages are separated. Manufacturer and 7-bit checks are heuristics, not full semantic validation.
- **ZIP**: supported non-encrypted archives; CRC and uncompressed size are checked. ZIP64 is not supported.
- **Audio**: browser codec support determines whether decodeAudioData succeeds.

## Proxy audio
A deterministic seed derived from input bytes/file identity and controls drives generic analog/FM/percussion/texture proxy audio. It is for rough triage and comparison, not sound recreation. No proprietary algorithms, wavetables, parameter mappings or firmware code are included.

## MIDI / SysEx
Web MIDI requires browser/device support and explicit permission. Successful output.send() means the browser accepted the request; it is not a target-device acknowledgement. Bulk pacing is not guaranteed for every MIDI interface.

## Validation scope
Static JavaScript syntax checks and local smoke tests do not replace testing with physical Digitone and Analog Four units, different OS versions, drivers, MIDI interfaces and file variants. Report exact reproduction details.
