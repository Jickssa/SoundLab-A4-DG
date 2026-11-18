# Contribuer à SoundLab

Les contributions sont bienvenues lorsqu'elles sont ciblées, reproductibles et accompagnées d'une description honnête de leur niveau de validation. Les échanges et propositions peuvent être rédigés en français ou en anglais.

## Avant de commencer

- Lire le [README](README.md), les [notes techniques](docs/TECHNICAL_NOTES.md) et les [limites](docs/LIMITATIONS.md).
- Pour une évolution importante, ouvrir d'abord une issue afin de discuter du besoin, du périmètre et du plan de test.
- Vérifier les issues et pull requests existantes pour limiter les doublons.

## Signaler un bug

Utiliser le modèle d'issue **Bug report**. Inclure autant que possible la version, branche et commit ; le système, navigateur et version ; instrument et firmware si pertinent ; interface audio/MIDI et routage ; extension et taille du fichier ; étapes minimales de reproduction ; résultat attendu/observé ; logs expurgés et captures sans données privées.

Ne jamais joindre de banques commerciales, fichiers protégés, dumps privés, firmware, numéros de série ou données personnelles.

## Proposer une fonctionnalité

Décrire le problème utilisateur avant la solution souhaitée. Préciser formats, appareils et navigateurs concernés, comportements attendus, effets sur les données sources, risques MIDI/SysEx et plan de validation. Séparer faits documentés, hypothèses et éléments restant à rétroconcevoir.

## Développement

Le projet est une application HTML/CSS/JavaScript autonome. Préserver cette simplicité, sauf justification claire d'une dépendance ou d'une étape de build.

1. Ne jamais modifier une source importée, une capture ou un payload natif de façon implicite.
2. Garder les opérations destructives explicites, confirmées et réversibles lorsque c'est raisonnablement possible.
3. Ne jamais élargir les possibilités d'envoi SysEx sans fixtures, tests négatifs et revue de sécurité.
4. Ne pas présenter le rendu proxy comme une émulation de l'instrument.
5. Borner les opérations mémoire et décompression ; tester les fichiers volumineux et malformés.
6. Préserver le fonctionnement local-first et ne pas introduire de téléversement sans décision explicite et documentation de confidentialité.
7. Mettre à jour les documentations française et anglaise, les limites et le changelog lorsque le comportement change.

## Tests locaux

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

Pour vérifier la syntaxe du JavaScript intégré à `index.html` :

```sh
python3 - <<'PY'
from pathlib import Path
html = Path("index.html").read_text(encoding="utf-8")
script = html.split("<script>", 1)[1].split("</script>", 1)[0]
Path("/tmp/soundlab.js").write_text(script, encoding="utf-8")
PY
node --check /tmp/soundlab.js
```

La CI GitHub exécute les contrôles correspondants et vérifie l'archive portable.

## Pull requests

- Une PR doit avoir un objectif précis et un périmètre cohérent.
- Expliquer les changements fonctionnels, fichiers concernés et éventuelles migrations.
- Énumérer les tests réellement exécutés, avec leurs résultats.
- Distinguer tests automatisés, essais manuels dans navigateur et essais sur matériel physique.
- Ajouter des étapes de reproduction et, si utile, des captures avant/après.
- Signaler limites connues, risques de perte de données et impacts de compatibilité.

Ne jamais déclarer un essai matériel ou navigateur qui n'a pas été effectué.

## Licence

En soumettant une contribution, l'auteur accepte que celle-ci soit distribuée selon la licence du dépôt, l'Unlicense, dans la mesure permise par le droit applicable.
