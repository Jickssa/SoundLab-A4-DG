# Politique de sécurité

SoundLab est une application locale de traitement de fichiers et d'interaction MIDI/SysEx. Les fichiers importés, métadonnées, archives et messages MIDI doivent être considérés comme non fiables.

## Signaler une vulnérabilité

Ne publiez pas de détail exploitable dans une issue publique avant coordination. Utilisez la fonction **Private vulnerability reporting** de GitHub si elle est activée pour le dépôt. Sinon, contactez le propriétaire du dépôt en privé via GitHub. Fournissez une description, les étapes de reproduction minimales, les versions concernées et l'impact observé. N'incluez aucun dump privé, secret ou donnée personnelle. Aucun délai de réponse ou niveau de service n'est garanti pour ce projet communautaire.

## Périmètre

Les signalements pertinents incluent notamment :

- exécution ou injection de script à travers un nom de fichier, manifeste, tag ou métadonnée ;
- traversée de chemin, archive malformée, bombe de décompression ou contournement des limites ZIP ;
- lecture/écriture non autorisée de fichiers ou accès réseau inattendu ;
- corruption ou divulgation de données locales ;
- contournement des garde-fous MIDI/SysEx ou envoi inattendu vers un périphérique ;
- déni de service par consommation excessive de mémoire ou de ressources.

## Mesures et limites connues

- Les fichiers importés et captures ne sont pas téléversés par les fonctions locales de l'application.
- Les imports ZIP sont limités et contrôlés, mais ces vérifications ne constituent pas une garantie contre tous les fichiers malveillants.
- Les payloads natifs AFSND/DNSND ne sont pas envoyés comme SysEx brut.
- L'envoi MIDI/SysEx est limité au sous-type Sound reconnu, après contrôles structurels et correspondance du modèle déclaré.
- Un appel Web MIDI réussi ne prouve pas la réception ou le stockage par le matériel.
- Les sauvegardes IndexedDB restent dépendantes du profil navigateur, de l'origine et des quotas locaux.

## Conseils aux utilisateurs

Utilisez des fichiers provenant de sources fiables. Conservez des sauvegardes indépendantes. N'utilisez pas l'application pour des opérations critiques ou avec des données instrumentales irremplaçables. Ne transmettez jamais de firmware, OS, bootloader ou message non identifié.
