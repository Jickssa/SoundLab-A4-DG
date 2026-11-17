# Elektron SoundLab — Analog Four & Digitone

Bibliothèque locale de sons, station de préécoute et utilitaire SysEx prudent pour Analog Four MKI / Analog Keys et Digitone MK1.

[English](README.en.md) · [Installation](INSTALLATION.md) · [Limites](LIMITATIONS.md) · [Tests](TESTING.md) · [Roadmap](../ROADMAP.md) · [Contribuer](../CONTRIBUTING.md) · [Sécurité](../SECURITY.md)

> **Version 3.2 — expérimentale, tests communautaires nécessaires.** Projet indépendant, sans affiliation avec Elektron. SoundLab ne remplace pas Elektron Transfer.

## Démarrage
Ouvrir `index.html` dans Chrome ou Edge récents. La lecture audio et l'inspection fonctionnent localement. Pour Web MIDI/SysEx et la capture audio sous Windows, exécuter `scripts/Lancer_WebMIDI_Chrome_Edge.bat` (Python 3 requis), puis ouvrir `http://localhost:8765`.

## Fonctions
- Inventaire des .afsnd, .dnsnd, .syx, audios pris en charge, archives ZIP et projets.
- Extraction des manifestes et tags accessibles des AFSND.
- Séparation des messages SysEx complets F0…F7, contrôles fabricant / 7-bit conservateurs.
- Lecture audio, synthèse proxy analogique/FM/percussion et export WAV.
- Réglages proxy effectifs : attaque, relâchement, largeur stéréo, modulation, brillance et réverbération à retard.
- Association d'un enregistrement réel à un sound natif, capture audio externe et lecture séquentielle.
- Filtres, favoris, inventaire JSON et monitoring MIDI IN.
- Envoi SysEx sous garde : sélection explicite de l'appareil, case de reconnaissance des risques, confirmation et limites de taille.

## Limites essentielles
- Les paramètres propriétaires des .afsnd/.dnsnd ne sont pas décodés. La préécoute proxy est une approximation, **pas un émulateur**.
- Le protocole natif USB-MIDI d'Elektron Transfer n'est pas implémenté. Les sons natifs ne sont pas envoyés comme SysEx.
- Les messages SysEx bruts ne sont pas préécoutés comme de l'audio. Pour entendre un dump, associer un enregistrement réel ou charger le son sur la machine.
- La mise en file Web MIDI ne prouve pas la réception ni l'écriture sur la machine.
- Transfert de projets et de firmware exclu.

Lire [Limites](LIMITATIONS.md) et [Tests](TESTING.md) avant tout transfert. Ne jamais publier banques commerciales, firmwares, dumps privés, numéros de série ou données personnelles.
