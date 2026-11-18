# Installation et utilisation

## Utilisation locale simple

SoundLab est une application HTML/CSS/JavaScript autonome, sans étape de compilation. Télécharger ou cloner le dépôt, puis ouvrir `index.html` dans une version récente de Chrome ou Edge. La lecture audio, l'inventaire et l'inspection locale ne nécessitent pas de serveur dédié. Les codecs disponibles dépendent du navigateur et du système.

## Web MIDI, SysEx et capture audio sous Windows

1. Installer Python 3.
2. Lancer `scripts/Lancer_WebMIDI_Chrome_Edge.bat`.
3. Laisser la fenêtre de terminal ouverte.
4. Ouvrir `http://localhost:8765` dans Chrome ou Edge.
5. Accorder explicitement les permissions Web MIDI/SysEx et microphone/capture audio lorsque le navigateur les demande.
6. Vérifier les ports MIDI IN/OUT et périphériques audio sélectionnés.

Les permissions et fonctions disponibles varient selon le navigateur, le système et les pilotes.

## Comparaison A/B

1. Importer un son natif `.afsnd` ou `.dnsnd`.
2. Associer un enregistrement audio réel avec **Lier l'audio sélectionné**, ou capturer directement la sortie de l'instrument.
3. Choisir **A · Capture réelle** pour écouter cette référence.
4. Choisir **B · Proxy** pour écouter l'approximation générée par SoundLab.
5. Exporter le mode actif si nécessaire.

Une capture directe attachée au son est prioritaire sur un fichier audio lié. A est un enregistrement fourni par l'utilisateur ; B est un rendu proxy. Aucun des deux ne constitue un décodage des paramètres du preset.

## Éditeur audio visuel (v3.7)

Ouvrir l'inspecteur audio puis **Ouvrir l'éditeur visuel**. Faire glisser sur la forme d'onde pour sélectionner une région temporelle. Dessiner une enveloppe de gain sur la sélection ou, sans sélection, sur la zone visible. Appliquer gain, fondu entrant/sortant, normalisation à −1 dBFS, inversion, silence ou rognage. Utiliser annulation/rétablissement et lecture de sélection pour contrôler le résultat. Exporter le WAV édité ou créer une nouvelle copie dans la bibliothèque.

L'édition porte sur une copie audio privée en mémoire. Les ressources sources restent intactes. Les états A/référence et B/proxy sont indépendants.

Limites mémoire : 128 Mio par tampon de piste, 128 Mio d'historique et 256 Mio cumulés par session. **Libérer mémoire** abandonne l'édition non exportée de l'élément courant après confirmation. Un export PCM 16 bits borne les échantillons hors de ±1 ; normaliser si nécessaire pour éviter l'écrêtage.

## Sauvegarde de la bibliothèque

Les commandes **Sauvegarder localement**, **Restaurer** et **Effacer sauvegarde** gèrent une copie IndexedDB dans le profil et l'origine du navigateur courants. La sauvegarde est manuelle et locale. Pour restaurer, réutiliser la même origine (par exemple toujours `http://localhost:8765`). Le nettoyage des données du site, les quotas et l'éviction du stockage sont sous le contrôle du navigateur. IndexedDB ne remplace pas les fichiers originaux ni une sauvegarde indépendante.

Les modifications de l'éditeur restent en mémoire tant qu'elles ne sont pas exportées ou ajoutées comme nouvelle copie à la bibliothèque. Après création de la copie, sauvegarder la bibliothèque si une persistance est souhaitée.

## Utilisation MIDI/SysEx prudente

1. Sauvegarder les données de l'instrument.
2. Vérifier indépendamment l'origine du fichier et le modèle de destination.
3. Contrôler le routage MIDI et la sortie choisie.
4. Mettre l'instrument dans le mode de réception approprié.
5. Envoyer uniquement des messages Sound reconnus et correspondant au modèle de la cible.
6. Vérifier directement sur l'instrument le résultat et l'absence d'écrasement de données.

SoundLab ne confirme pas que l'instrument a reçu ou stocké les données. Le protocole de transfert USB-MIDI natif d'Elektron Transfer n'est pas implémenté. Ne jamais envoyer de firmware, de données non identifiées ou de dumps dont la compatibilité n'a pas été établie.

## Télécharger l'archive portable

Les exécutions réussies du workflow **Static checks** construisent et publient un artefact ZIP. Ouvrir l'onglet [Actions](https://github.com/Jickssa/SoundLab-A4-DG/actions), choisir une exécution réussie correspondant à la branche/version souhaitée, puis télécharger l'artefact dans la section **Artifacts**. Le nom inclut la version et le commit. Les artefacts expirent selon la rétention configurée par GitHub ; ce ne sont pas des releases permanentes.

## Environnement testé et limites

La CI réalise les audits statiques, tests de régression et la construction de l'archive. Cela ne garantit pas le fonctionnement de tous les navigateurs, interfaces audio/MIDI ou matériels. Les essais physiques sur Analog Four et Digitone doivent être documentés séparément.
