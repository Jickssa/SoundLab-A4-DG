# Installation and usage

## Local use
Open `index.html` in a recent Chrome or Edge browser. Audio playback and local inventory do not require a server.

## Web MIDI and audio capture
On Windows, run `scripts/Lancer_WebMIDI_Chrome_Edge.bat`. Python 3 is required. The server listens on `http://localhost:8765`. Keep the console open and grant Web MIDI/SysEx and audio-input permissions when prompted.

## SysEx transfer
1. Connect the instrument and verify MIDI/USB routing.
2. Back up the target data.
3. Explicitly prepare the instrument's SysEx receive mode.
4. Select the MIDI output and logical target in SoundLab.
5. Verify the dump origin and target model.
6. Send selected messages. SoundLab cannot confirm receipt or storage.

## Native sound audition
AFSND/DNSND files are inspected as binary containers. The built-in proxy engine produces an approximation. For faithful audition, load the patch on the instrument and capture its audio output through an audio interface.
