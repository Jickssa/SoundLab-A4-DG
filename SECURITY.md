# Security policy

SoundLab is a local browser application handling user-supplied files. Treat imported archives and MIDI/SysEx data as untrusted.

## Reporting
Do not disclose security issues in public issues before assessment. Use GitHub private vulnerability reporting if enabled; otherwise contact the repository owner privately through GitHub.

## Scope
Relevant issues include ZIP/path handling, script injection via file names or metadata, unsafe archive expansion, unintended network/file access and unsafe MIDI/SysEx behaviour.

## Safe defaults
- No network upload of imported sounds.
- No firmware or project transfer.
- Native sound payloads are not sent as raw SysEx.
- Basic manufacturer bytes do not establish that a SysEx message is safe.
- The current app is experimental; do not use it for mission-critical transfers or irreplaceable data.
