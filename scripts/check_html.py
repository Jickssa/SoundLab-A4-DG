#!/usr/bin/env python3
"""Static integrity checks for the standalone SoundLab HTML application."""
from __future__ import annotations

import re
import sys
from collections import Counter
from html.parser import HTMLParser
from pathlib import Path


class MarkupAudit(HTMLParser):
    def __init__(self) -> None:
        super().__init__(convert_charrefs=True)
        self.ids: list[str] = []
        self.checkbox_ids: set[str] = set()

    def handle_starttag(self, tag: str, attrs: list[tuple[str, str | None]]) -> None:
        attrs_dict = dict(attrs)
        element_id = attrs_dict.get("id")
        if element_id:
            self.ids.append(element_id)
            if tag == "input" and attrs_dict.get("type") == "checkbox":
                self.checkbox_ids.add(element_id)


def fail(message: str) -> None:
    print(f"FAIL: {message}", file=sys.stderr)
    raise SystemExit(1)


html_path = Path("index.html")
if not html_path.is_file():
    fail("index.html is missing")

html = html_path.read_text(encoding="utf-8")
if html.count("<script>") != 1 or html.count("</script>") != 1:
    fail("Expected exactly one inline application script")

script = html.split("<script>", 1)[1].split("</script>", 1)[0]
if not script.strip():
    fail("Inline application script is empty")

audit = MarkupAudit()
audit.feed(html)
counts = Counter(audit.ids)
duplicates = sorted(key for key, count in counts.items() if count > 1)
if duplicates:
    fail("Duplicate HTML ids: " + ", ".join(duplicates))

binding_match = re.search(
    r"E=\{\};\[(.*?)\]\.forEach\(k=>E\[k\]=\$\('#'\+k\)\);",
    script,
    re.S,
)
if not binding_match:
    fail("Could not locate the dynamic DOM binding list")
binding_list = re.findall(r"""['"]([A-Za-z0-9_-]+)['"]""", binding_match.group(1))
binding_counts = Counter(binding_list)
duplicate_bindings = sorted(key for key, count in binding_counts.items() if count > 1)
if duplicate_bindings:
    fail("DOM IDs are bound more than once: " + ", ".join(duplicate_bindings))

selector_ids = set(binding_list) | set(re.findall(r"\$\('#([A-Za-z0-9_-]+)'\)", script))
missing = sorted(selector_ids - set(audit.ids))
if missing:
    fail("JavaScript bindings reference missing IDs: " + ", ".join(missing))

required = {
    "fileInput", "dirInput", "rows", "midiOut", "midiIn", "target",
    "sysexAck", "sendCurrent", "sendSelected", "play", "stop",
    "wave", "analysis", "capture", "exportInventory", "saveLocal", "restoreLocal", "deleteLocal", "localStatus", "audioFacts", "waveZoom", "waveOffset", "previewGain", "saveLocal", "restoreLocal", "deleteLocal", "localStatus",
}
missing_required = sorted(required - set(audit.ids))
if missing_required:
    fail("Required controls are missing: " + ", ".join(missing_required))

if "sysexAck" not in audit.checkbox_ids:
    fail("SysEx safety acknowledgement must be an actual checkbox")

if "Hardware receipt is not confirmed" not in script and "hardware receipt is not confirmed" not in script:
    fail("Missing explicit MIDI hardware receipt limitation")

print(
    "PASS: "
    f"{len(audit.ids)} unique HTML IDs; "
    f"{len(selector_ids)} JavaScript-bound IDs; "
    f"{len(required)} required controls; "
    "SysEx acknowledgement checkbox present."
)
