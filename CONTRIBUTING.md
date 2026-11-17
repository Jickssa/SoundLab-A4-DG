# Contributing

Thanks for helping improve SoundLab. Contributions should be reproducible, focused and honest about hardware validation.

## Bug reports
Use the bug issue template. Include version/commit, OS/browser, exact device and firmware (if relevant), audio/MIDI interface, file extension/size, exact reproduction steps, expected vs actual behaviour and sanitized logs.

Never attach copyrighted sound packs, private dumps, firmware, serial numbers or personal data.

## Feature proposals
Describe the user problem, workflow, target instrument, expected behaviour and a safe test plan. Separate documented facts from assumptions.

## Code contributions
1. Open an issue for substantial changes.
2. Keep the app dependency-free unless a dependency has clear value.
3. Never change transfer semantics without fixtures and a safety review.
4. Never describe proxy output as true hardware emulation.
5. Run `python3 scripts/check_html.py`, `node scripts/test_parsers.js` and `node scripts/test_persistence.js` and `node scripts/test_audio_inspector.js` and `node scripts/test_ab_audition.js`.
6. Extract the inline script and run `node --check` (the GitHub Actions workflow does both).
7. Update French and English documentation.
8. Submit a focused pull request with manual test steps.

Issues and PRs may be written in English or French.
