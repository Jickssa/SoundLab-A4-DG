# Elektron SoundLab — Analog Four & Digitone

**Bibliothèque locale de sons, inspection SysEx prudente, préécoute A/B et édition audio visuelle.**

[Français](docs/README.fr.md) · [English](docs/README.en.md) · [Installation](docs/INSTALLATION.md) · [Architecture](docs/TECHNICAL_NOTES.md) · [Limites](docs/LIMITATIONS.md) · [Tests](docs/TESTING.md) · [Format Sound SysEx](docs/SYSEX_SOUND_FORMAT.md) · [Roadmap](ROADMAP.md) · [Journal des versions](CHANGELOG.md) · [Contribuer](CONTRIBUTING.md) · [Sécurité](SECURITY.md)

> **v3.7 — logiciel expérimental, validation communautaire nécessaire.** Projet indépendant, non affilié à Elektron. SoundLab n'est ni un émulateur des instruments ni un remplacement d'Elektron Transfer.

## Présentation

SoundLab est une application HTML/CSS/JavaScript autonome conçue pour organiser, inspecter et écouter localement des fichiers liés aux Elektron Analog Four MKI / Analog Keys et Digitone MK1. Elle associe les fichiers natifs, leurs références audio réelles, des rendus proxy approximatifs et des utilitaires MIDI/SysEx strictement limités à un sous-type Sound reconnu.

L'application fonctionne d'abord dans le navigateur : aucun compte, serveur applicatif ou téléversement de bibliothèque n'est requis pour les fonctions locales.

## Fonctionnalités

- **Bibliothèque** : import et inventaire de fichiers `.afsnd`, `.dnsnd`, `.syx`, audio pris en charge par le navigateur, archives ZIP et fichiers de projet reconnus.
- **Inspection** : extraction prudente de manifestes/tags accessibles dans les conteneurs AFSND et inspection des messages Sound SysEx reconnus (modèle, slot, nom, tags, longueur et checksum).
- **Écoute** : lecture audio réelle et génération déterministe d'un rendu proxy générique pour certains sons natifs.
- **Comparaison A/B** : A utilise une capture de la machine ou un fichier audio lié ; B utilise le rendu proxy du son natif. L'export suit la source active.
- **Inspecteur audio** : durée, fréquence d'échantillonnage, canaux, estimations crête/RMS et navigation dans la forme d'onde.
- **Éditeur visuel v3.7** : sélection temporelle à la souris/tactile, enveloppe de gain dessinée, gain, fondus, normalisation à −1 dBFS, inversion, silence, rognage, lecture de sélection, annulation/rétablissement et export WAV.
- **Copies non destructives** : création d'un nouvel élément WAV édité dans la bibliothèque sans écraser le fichier ou l'enregistrement source.
- **Outils de bibliothèque** : filtres, favoris, lecture séquentielle, inventaire JSON et sauvegarde/restauration locale facultative via IndexedDB.
- **MIDI/SysEx** : monitoring MIDI IN et mise en file limitée aux trames Sound reconnues, valides et correspondant au modèle de la cible déclarée.

## Démarrage rapide

1. Récupérer le dépôt ou télécharger l'archive portable depuis un workflow GitHub Actions réussi.
2. Ouvrir `index.html` dans une version récente de Chrome ou Edge.
3. Importer des fichiers audio ou une bibliothèque de sons depuis l'interface.
4. Pour Web MIDI/SysEx et la capture d'entrée audio sous Windows, lancer `scripts/Lancer_WebMIDI_Chrome_Edge.bat` (Python 3 requis), puis ouvrir `http://localhost:8765`.
5. Accorder explicitement les permissions demandées par le navigateur et vérifier les entrées/sorties audio/MIDI sélectionnées.

Voir le [guide d'installation détaillé](docs/INSTALLATION.md).

## Éditeur audio visuel

L'éditeur traite une copie privée du tampon audio décodé. Il ne modifie pas le Blob importé, les captures enregistrées ni les données natives des presets. Les éditions A/référence et B/proxy sont séparées.

| Ressource | Limite |
|---|---:|
| Tampon de travail par piste | 128 Mio |
| Historique annulation/rétablissement | 128 Mio |
| Total des tampons et historiques par session | 256 Mio |

Les éditions non exportées restent en mémoire de session. Exporter le WAV ou créer une copie dans la bibliothèque pour conserver le résultat ; sauvegarder ensuite la bibliothèque locale si une persistance IndexedDB est souhaitée.

## Limites essentielles

- Les paramètres propriétaires des fichiers `.afsnd` / `.dnsnd` ne sont pas décodés. Le rendu proxy est une approximation déterministe, pas une reproduction fidèle du moteur sonore.
- L'éditeur appliqué en mode B ne traite que la forme d'onde proxy générée par SoundLab ; il ne modifie jamais les paramètres du preset Elektron.
- Un message SysEx brut n'est pas un signal audio. Seul le sous-type Sound ciblé est inspecté de manière structurée ; aucun paramètre de synthèse n'est décodé.
- Le protocole USB-MIDI natif d'Elektron Transfer, le transfert de projets et celui de firmware ne sont pas implémentés.
- Un appel Web MIDI `send()` ne constitue pas un accusé de réception matériel.
- Les tests automatisés et l'inspection statique ne remplacent pas les essais dans un navigateur réel ni les validations sur Analog Four/Digitone physiques.

Lire impérativement [Limites et utilisation sûre](docs/LIMITATIONS.md) avant tout transfert MIDI/SysEx.

## Tests et intégration continue

Les scripts de tests couvrent notamment les parsers, le format Sound SysEx pris en charge, la persistance IndexedDB, l'inspecteur audio, l'éditeur visuel, l'écoute A/B et la syntaxe JavaScript. GitHub Actions exécute les contrôles, construit une archive portable et la publie comme artefact du workflow.

Consulter [le plan de test](docs/TESTING.md) et l'onglet [Actions](https://github.com/Jickssa/SoundLab-A4-DG/actions).

## Documentation du projet

- [Guide en français](docs/README.fr.md) et [guide en anglais](docs/README.en.md)
- [Installation et utilisation](docs/INSTALLATION.md)
- [Notes techniques et architecture](docs/TECHNICAL_NOTES.md)
- [Limites et avertissements](docs/LIMITATIONS.md)
- [Plan de tests](docs/TESTING.md)
- [Structure Sound SysEx observée](docs/SYSEX_SOUND_FORMAT.md)
- [Feuille de route](ROADMAP.md) et [changelog](CHANGELOG.md)
- [Contribuer](CONTRIBUTING.md) · [Politique de sécurité](SECURITY.md) · [Licence](LICENSE)

## Statut du projet

La version 3.7 est portée par une branche de développement et une pull request ouverte. Les fonctionnalités décrites correspondent au code et aux tests de cette branche ; elles ne doivent pas être interprétées comme une validation de la branche principale ni comme une certification matérielle.

**Dépôt :** https://github.com/Jickssa/SoundLab-A4-DG  
**Pull request v3.7 :** https://github.com/Jickssa/SoundLab-A4-DG/pull/7

## Licence et indépendance

Le dépôt contient une licence Unlicense. Les noms et marques Elektron, Analog Four, Analog Keys et Digitone sont utilisés uniquement pour identifier les matériels ciblés. SoundLab est un projet indépendant et n'est ni développé, ni approuvé, ni maintenu par Elektron.
