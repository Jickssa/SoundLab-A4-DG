#!/usr/bin/env python3
"""Create a dependency-free ZIP bundle for public SoundLab testers."""
from __future__ import annotations

from pathlib import Path
from zipfile import ZIP_DEFLATED, ZipFile

ROOT = Path(__file__).resolve().parents[1]
OUTPUT = ROOT / "dist" / "Elektron-SoundLab-v3.6-portable.zip"
INCLUDED = [
    "index.html",
    "README.md",
    "LICENSE",
    "CHANGELOG.md",
    "SECURITY.md",
    "ROADMAP.md",
    "CONTRIBUTING.md",
    "docs/README.fr.md",
    "docs/README.en.md",
    "docs/INSTALLATION.md",
    "docs/LIMITATIONS.md",
    "docs/TECHNICAL_NOTES.md",
    "docs/TESTING.md",
    "docs/GUIDE_FR.txt",
    "docs/FEEDBACK_FR.md",
    "docs/FEEDBACK_EN.md",
    "scripts/Lancer_SoundLab.bat",
    "scripts/Lancer_WebMIDI_Chrome_Edge.bat",
]

missing = [item for item in INCLUDED if not (ROOT / item).is_file()]
if missing:
    raise SystemExit("Missing bundle files: " + ", ".join(missing))

OUTPUT.parent.mkdir(parents=True, exist_ok=True)
with ZipFile(OUTPUT, "w", compression=ZIP_DEFLATED, compresslevel=9) as archive:
    for relative in INCLUDED:
        archive.write(ROOT / relative, f"Elektron-SoundLab/{relative}")

with ZipFile(OUTPUT, "r") as archive:
    bad_member = archive.testzip()
    if bad_member:
        raise SystemExit(f"ZIP integrity check failed at: {bad_member}")
    names = set(archive.namelist())
    expected = {f"Elektron-SoundLab/{item}" for item in INCLUDED}
    if names != expected:
        raise SystemExit("ZIP member list differs from the expected manifest")

print(f"Portable bundle created: {OUTPUT}")
print(f"Files packaged: {len(INCLUDED)}")
print(f"Archive size: {OUTPUT.stat().st_size} bytes")
