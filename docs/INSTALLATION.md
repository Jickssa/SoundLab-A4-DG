# Installation and usage

## Local use
Open `index.html` in a recent Chrome or Edge browser. Audio playback and local inventory do not require a server.

## Web MIDI and audio capture
On Windows, run `scripts/Lancer_WebMIDI_Chrome_Edge.bat`. Python 3 is required. The server listens on `http://localhost:8765`. Keep the console open and grant Web MIDI/SysEx and audio-input permissions when prompted.

## A/B audition (v3.5)
1. Import a native `.afsnd` or `.dnsnd` sound.
2. Either import a real WAV/AIFF recording and use **Link selected audio**, or select the native sound and make a six-second input capture while the instrument plays it.
3. Press **A · Capture réelle** to hear the direct machine capture or linked audio file.
4. Press **B · Proxy** to hear SoundLab's deterministic approximation of the native sound.
5. Export with **Export WAV**; the filename identifies whether A/reference or B/proxy was exported.

A direct capture stored on the native item takes precedence over a linked imported recording. A-mode is actual recorded audio, not a parameter decode. B-mode is a proxy, not a faithful emulator. Raw SysEx messages never receive an arbitrary proxy sound.

## Local library persistence (v3.3+)
The **Save locally**, **Restore** and **Delete backup** controls use IndexedDB in the current browser profile and origin. To restore a saved library, reopen SoundLab through the same address (for example, always use `http://localhost:8765`, not sometimes `file://`). Saving is manual; imported source blobs and capture recordings are stored locally. Browser storage can be cleared or evicted, and available quota depends on the browser. Keep original files and independent backups.

## SysEx transfer
1. Connect the instrument and verify MIDI/USB routing.
2. Back up the target data.
3. Explicitly prepare the instrument's SysEx receive mode.
4. Select the MIDI output and logical target in SoundLab.
5. Verify the dump origin and target model.
6. Tick the safety acknowledgement and send only known, model-specific messages. SoundLab cannot confirm receipt or storage.

## Portable distribution
The latest successful GitHub Actions run publishes an `Elektron-SoundLab-v3.5-portable.zip` artifact. Open the repository's Actions tab, select the latest successful **Static checks** run, and download its artifact.
