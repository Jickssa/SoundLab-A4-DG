# Elektron SoundLab — Analog Four & Digitone

Bibliothèque locale de sons, station de préécoute et utilitaire SysEx prudent pour Analog Four MKI / Analog Keys et Digitone MK1.

[English](README.en.md) · [Installation](INSTALLATION.md) · [Limites](LIMITATIONS.md) · [Tests](TESTING.md) · [Roadmap](../ROADMAP.md) · [Contribuer](../CONTRIBUTING.md) · [Sécurité](../SECURITY.md)

> **Version 3.5 — expérimentale, tests communautaires nécessaires.** Projet indépendant, sans affiliation avec Elektron. SoundLab ne remplace pas Elektron Transfer.

## Démarrage
Ouvrir `index.html` dans Chrome ou Edge récents. La lecture audio et l'inspection fonctionnent localement. Pour Web MIDI/SysEx et la capture audio sous Windows, exécuter `scripts/Lancer_WebMIDI_Chrome_Edge.bat` (Python 3 requis), puis ouvrir `http://localhost:8765`.

## Fonctions
- Inventaire AFSND, DNSND, SysEx, audio, ZIP et projets.
- Extraction des manifestes et tags accessibles des AFSND.
- Lecture audio, synthèse proxy analogique/FM/percussion et export WAV.
- Association d'un fichier audio réel importé ou d'une capture directe de la machine à un son natif.
- **Écoute A/B** : A lit la référence réelle (fichier importé ou capture associée) ; B lit le proxy synthétique du patch natif. L'export WAV suit le mode sélectionné.
- Inspecteur audio : durée, fréquence d'échantillonnage, nombre de canaux et estimations crête/RMS échantillonnées.
- Zoom et déplacement horizontal de la forme d'onde ; volume de monitoring indépendant.
- Filtres, favoris, lecture séquentielle, inventaire JSON et monitoring MIDI IN.
- Envoi SysEx sous garde : sélection explicite de l'appareil, reconnaissance des risques, confirmation et limites.
- Sauvegarde/restauration facultative en IndexedDB dans le profil et l'origine du navigateur.

## Comparaison A/B
Après association d'un enregistrement réel ou capture de la sortie de la machine au son natif, utiliser **A · Capture réelle** pour écouter cette référence et **B · Proxy** pour écouter l'approximation générée par SoundLab. La capture directe est automatiquement proposée en A ; si elle est absente, le fichier audio lié est utilisé. Le mode B n'est disponible que pour les sons natifs AFSND/DNSND.

Un message SysEx brut n'est pas un signal audio et ne reçoit aucun rendu proxy. S'il est associé à un enregistrement, seul cet enregistrement peut être écouté en A.

## Sauvegarde locale
Les boutons **Sauvegarder localement**, **Restaurer** et **Effacer sauvegarde** agissent sur la base IndexedDB de l'origine et du profil navigateur courants. Rien n'est téléversé. Utiliser la même origine pour retrouver les données. Le nettoyage des données du site ou du profil peut supprimer cette sauvegarde : conserver les fichiers originaux et des copies indépendantes.

## Limites essentielles
- Les paramètres propriétaires des .afsnd/.dnsnd ne sont pas décodés. La préécoute proxy est une approximation, **pas un émulateur**.
- La référence A est une capture/fichier réel associé ; elle ne constitue pas un décodage du patch propriétaire.
- Les mesures crête/RMS sont échantillonnées et approximatives ; elles ne remplacent pas une analyse audio hors ligne exhaustive.
- Le protocole natif USB-MIDI d'Elektron Transfer n'est pas implémenté. Les sons natifs ne sont pas envoyés comme SysEx.
- La mise en file Web MIDI ne prouve pas la réception ni l'écriture sur la machine.
- Transfert de projets et de firmware exclu.

Lire [Limites](LIMITATIONS.md) et [Tests](TESTING.md) avant tout transfert. Ne jamais publier banques commerciales, firmwares, dumps privés, numéros de série ou données personnelles.
