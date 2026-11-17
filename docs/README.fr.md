# Elektron SoundLab — Analog Four & Digitone

Bibliothèque locale de sons, station de préécoute et utilitaire SysEx prudent pour Analog Four MKI / Analog Keys et Digitone MK1.

[English](README.en.md) · [Installation](INSTALLATION.md) · [Limites](LIMITATIONS.md) · [Tests](TESTING.md) · [Format SysEx Sound](SYSEX_SOUND_FORMAT.md) · [Roadmap](../ROADMAP.md) · [Contribuer](../CONTRIBUTING.md) · [Sécurité](../SECURITY.md)

> **Version 3.7 — expérimentale, tests communautaires nécessaires.** Projet indépendant, sans affiliation avec Elektron. SoundLab ne remplace pas Elektron Transfer.

## Démarrage
Ouvrir `index.html` dans Chrome ou Edge récents. La lecture audio et l'inspection fonctionnent localement. Pour Web MIDI/SysEx et la capture audio sous Windows, exécuter `scripts/Lancer_WebMIDI_Chrome_Edge.bat` (Python 3 requis), puis ouvrir `http://localhost:8765`.

## Fonctions
- Inventaire AFSND, DNSND, SysEx, audio, ZIP et projets.
- Extraction des manifestes et tags accessibles des AFSND.
- Inspection structurée des messages Sound SysEx A4 / Digitone : modèle, slot, nom, tags, checksum et longueur.
- Lecture audio, synthèse proxy analogique/FM/percussion et export WAV.
- Association d'un fichier audio réel importé ou d'une capture directe de la machine à un son natif.
- **Écoute A/B** : A lit la référence réelle (fichier importé ou capture associée) ; B lit le proxy synthétique du patch natif. L'export WAV suit le mode sélectionné.
- Inspecteur audio : durée, fréquence d'échantillonnage, nombre de canaux et estimations crête/RMS échantillonnées.
- Zoom et déplacement horizontal de la forme d'onde ; volume de monitoring indépendant.
- Éditeur audio visuel : sélection temporelle à la souris/tactile, enveloppe de gain dessinée, gain, fondus, normalisation à −1 dBFS, inversion, silence, rognage, annulation/rétablissement et lecture de sélection.
- Export du résultat en WAV ou création d'une copie éditée dans la bibliothèque, sans écraser le fichier importé.
- Filtres, favoris, lecture séquentielle, inventaire JSON et monitoring MIDI IN.
- Mise en file limitée aux messages Sound SysEx reconnus et valides, avec correspondance obligatoire entre modèle du message et cible sélectionnée. Les autres messages restent non transférables.
- Sauvegarde/restauration facultative en IndexedDB dans le profil et l'origine du navigateur.

## Comparaison A/B
Après association d'un enregistrement réel ou capture de la sortie de la machine au son natif, utiliser **A · Capture réelle** pour écouter cette référence et **B · Proxy** pour écouter l'approximation générée par SoundLab. La capture directe est automatiquement proposée en A ; si elle est absente, le fichier audio lié est utilisé. Le mode B n'est disponible que pour les sons natifs AFSND/DNSND.

Un message SysEx brut n'est pas un signal audio et ne reçoit aucun rendu proxy. S'il est associé à un enregistrement, seul cet enregistrement peut être écouté en A.

## Sauvegarde locale
Les boutons **Sauvegarder localement**, **Restaurer** et **Effacer sauvegarde** agissent sur la base IndexedDB de l'origine et du profil navigateur courants. Rien n'est téléversé. Utiliser la même origine pour retrouver les données. Le nettoyage des données du site ou du profil peut supprimer cette sauvegarde : conserver les fichiers originaux et des copies indépendantes.

## Limites essentielles
- Les paramètres propriétaires des .afsnd/.dnsnd ne sont pas décodés. La préécoute proxy est une approximation, **pas un émulateur**. L'éditeur peut traiter le rendu proxy en audio, mais ne change pas les paramètres du preset natif.
- L'éditeur travaille sur une copie AudioBuffer en mémoire, limitée à 128 Mio par piste ; l'historique d'annulation est plafonné à 128 Mio.
- Les modifications de session ne sont pas une sauvegarde permanente : exporter le WAV édité ou créer une copie dans la bibliothèque, puis sauvegarder la bibliothèque locale.
- La référence A est une capture/fichier réel associé ; elle ne constitue pas un décodage du patch propriétaire.
- Les mesures crête/RMS sont échantillonnées et approximatives ; elles ne remplacent pas une analyse audio hors ligne exhaustive.
- L'inspection SysEx ne décode que les métadonnées Sound (modèle, slot, nom, tags) ; aucun paramètre de synthèse n'est décodé.
- Les messages SysEx autres que les Sounds individuels reconnus ne sont pas proposés à l'envoi. Les checksums et longueurs vérifiés ne constituent pas une certification de compatibilité matérielle.
- Le protocole natif USB-MIDI d'Elektron Transfer n'est pas implémenté. Les conteneurs .afsnd/.dnsnd ne sont pas transférés comme SysEx.
- La mise en file Web MIDI ne prouve pas la réception ni l'écriture sur la machine.
- Transfert de projets et de firmware exclu.

Lire [Limites](LIMITATIONS.md) et [Tests](TESTING.md) avant tout transfert. Ne jamais publier banques commerciales, firmwares, dumps privés, numéros de série ou données personnelles.
