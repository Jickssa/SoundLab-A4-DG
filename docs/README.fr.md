# Elektron SoundLab — Analog Four & Digitone

Bibliothèque locale de sons, station de préécoute et utilitaire SysEx prudent pour Analog Four MKI / Analog Keys et Digitone MK1.

[English](README.en.md) · [Installation](INSTALLATION.md) · [Limites](LIMITATIONS.md) · [Roadmap](../ROADMAP.md) · [Contribuer](../CONTRIBUTING.md) · [Sécurité](../SECURITY.md)

> **État : expérimental, tests communautaires nécessaires.** Projet indépendant, sans affiliation avec Elektron. SoundLab ne remplace pas Elektron Transfer.

## Démarrage
Ouvrir `index.html` dans Chrome ou Edge récents. La lecture audio et l'inspection fonctionnent localement. Pour Web MIDI/SysEx et la capture audio sous Windows, exécuter `scripts/Lancer_WebMIDI_Chrome_Edge.bat` (Python 3 requis), puis ouvrir `http://localhost:8765`.

## Fonctions
- Inventaire des .afsnd, .dnsnd, .syx, audios pris en charge, archives ZIP et projets.
- Extraction des manifestes et tags accessibles des AFSND.
- Séparation des messages SysEx complets F0…F7 et contrôles prudents fabricant / 7-bit.
- Lecture audio navigateur, aperçu proxy déterministe des payloads natifs et export WAV.
- Association d'un enregistrement réel à un sound natif et capture d'entrée audio externe.
- Filtres, favoris, lecture séquentielle, export JSON et mise en file de notes / SysEx via Web MIDI.

## Limites essentielles
- Les payloads .afsnd/.dnsnd ne sont pas décodés en paramètres propriétaires. La préécoute proxy est une approximation, **pas un émulateur**.
- Le protocole USB-MIDI natif d'Elektron Transfer n'est pas implémenté. Les sons natifs ne sont pas envoyés comme SysEx brut.
- La mise en file Web MIDI ne prouve pas la réception, l'acceptation ou l'enregistrement par l'instrument.
- Le transfert de projets et de firmware est exclu.

Lire [Limites](LIMITATIONS.md) avant tout envoi SysEx. Publier les retours dans GitHub Issues. Ne pas joindre de banques protégées, firmwares, dumps privés, numéros de série ou données personnelles.

## Licence
Le dépôt conserve son [Unlicense](../LICENSE). Elektron est une marque de son titulaire.
