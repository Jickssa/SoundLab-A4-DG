# SoundLab v3.7 — plan de test

Ce document sépare les contrôles automatisés, les essais manuels dans un navigateur et les essais sur matériel physique. Un résultat dans une catégorie ne vaut pas validation dans les autres. Ne jamais utiliser une banque irremplaçable ou un instrument sans sauvegarde.

## Contrôles automatisés

Depuis la racine du dépôt :

```sh
python3 scripts/check_html.py
node scripts/test_parsers.js
node scripts/test_elektron_sound_sysex.js
node scripts/test_persistence.js
node scripts/test_audio_inspector.js
node scripts/test_visual_editor.js
node scripts/test_ab_audition.js
python3 scripts/package_portable.py
```

Vérifier également la syntaxe du script intégré :

```sh
python3 - <<'PY'
from pathlib import Path
html = Path("index.html").read_text(encoding="utf-8")
script = html.split("<script>", 1)[1].split("</script>", 1)[0]
Path("/tmp/soundlab.js").write_text(script, encoding="utf-8")
PY
node --check /tmp/soundlab.js
```

GitHub Actions exécute les contrôles configurés dans le workflow et publie une archive ZIP en artefact si la construction aboutit.

## Essais manuels dans le navigateur

### Import et lecture

- [ ] Importer un WAV et vérifier lecture, forme d'onde et export.
- [ ] Vérifier durée, fréquence d'échantillonnage, nombre de canaux et estimations crête/RMS.
- [ ] Modifier zoom et position horizontale ; vérifier la fenêtre affichée.
- [ ] Modifier le volume de monitoring ; vérifier que l'export source n'est pas modifié.
- [ ] Importer un AFSND et un DNSND ; vérifier le rendu proxy uniquement.
- [ ] Associer un fichier audio réel ; vérifier A puis B.
- [ ] Capturer directement la sortie audio de la machine ; vérifier la disponibilité en A et le proxy en B.
- [ ] Exporter A et B séparément et contrôler les contenus.

### Éditeur visuel

- [ ] Ouvrir l'éditeur sur un fichier audio et faire une sélection à la souris.
- [ ] Vérifier que la sélection suit le zoom et le déplacement horizontal.
- [ ] Appliquer un gain sur la sélection et vérifier que les échantillons extérieurs restent inchangés.
- [ ] Dessiner une enveloppe sans sélection et vérifier qu'elle reste dans la zone visible.
- [ ] Recommencer avec une sélection et vérifier que l'enveloppe reste dans cette sélection.
- [ ] Tester fondu entrant, fondu sortant, normalisation −1 dBFS, inversion, silence et rognage.
- [ ] Vérifier annulation/rétablissement et restauration de la durée après annulation du rognage.
- [ ] Lire la sélection et le résultat édité.
- [ ] Exporter le WAV édité et créer une copie dans la bibliothèque.
- [ ] Vérifier que l'original reste intact et que la copie éditée peut être sauvegardée/restaurée.
- [ ] Passer de A à B et confirmer que les états d'édition sont indépendants.
- [ ] Vérifier le refus propre au-delà de 128 Mio par tampon.
- [ ] Vérifier le plafond agrégé de 256 Mio et l'éviction contrôlée de snapshots d'historique.
- [ ] Utiliser **Libérer mémoire** et confirmer la disparition de l'édition non exportée.

### MIDI / SysEx

- [ ] Tester les trames Sound synthétiques A4 et Digitone reconnues.
- [ ] Vérifier le rejet des mauvais modèles, longueurs, préfixes, checksums et payloads invalides.
- [ ] Confirmer qu'un message non reconnu reste non transférable.
- [ ] Vérifier la correspondance entre modèle de trame et cible choisie.
- [ ] Ne réaliser les essais matériels qu'avec sauvegarde, message connu et destination sans risque.

### Persistance

- [ ] Sauvegarder la bibliothèque dans IndexedDB.
- [ ] Recharger la page depuis la même origine et restaurer les données.
- [ ] Vérifier les blobs source, captures, métadonnées, favoris et liens audio.
- [ ] Vérifier le comportement lorsque le stockage est indisponible ou quota atteint.

## Essais matériels

À documenter séparément pour chaque essai : modèle exact, révision matérielle si connue, firmware, système, navigateur, interface MIDI/audio, routage, fichier de test non sensible et résultat observé. Ne jamais assimiler un test synthétique ou logiciel à un essai sur Analog Four ou Digitone.

## Rapport de validation

Pour chaque résultat, indiquer **PASS** (contrôle exécuté et résultat conforme), **FAIL** (anomalie reproduite), **NOT RUN** (non exécuté) ou **NOT APPLICABLE** (sans rapport avec l'environnement testé). Joindre les logs expurgés et l'identifiant du commit testé. Éviter les affirmations globales du type « fonctionne sur tout le matériel ».
