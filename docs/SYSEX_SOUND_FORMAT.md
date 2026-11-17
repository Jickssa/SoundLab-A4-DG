# Elektron Sound SysEx — inspection périmétrée

## Ce que SoundLab reconnaît en v3.6

SoundLab peut maintenant identifier une sous-famille précise de messages SysEx Elektron correspondant à des Sounds individuels pour :

- Analog Four / Analog Keys : identifiant modèle 0x06 ;
- Digitone MK1 : identifiant modèle 0x0D.

La reconnaissance demande simultanément un cadre F0…F7, l'identifiant fabricant 00 20 3C, l'identifiant modèle attendu, le préfixe de Sound 00 53 01 01, un payload 7-bit décodable, le checksum attendu et le champ de longueur cohérent. Un message qui échoue à un seul de ces contrôles reste un élément SysEx brut d'inventaire.

Pour les messages reconnus, SoundLab extrait uniquement les métadonnées accessibles : modèle, numéro de slot, nom et tags. Les tags sont des indicateurs sur 32 bits propres au modèle.

## Structure observée

La structure utilisée pour cette inspection est fondée sur l'analyse publique du projet communautaire Digitools, notamment son gestionnaire SysEx et sa classe Sound :

1. Délimiteur F0 ;
2. identifiant fabricant 00 20 3C ;
3. identifiant modèle (06 pour A4 ou 0D pour Digitone) ;
4. préfixe de Sound 00 53 01 01 ;
5. numéro de slot ;
6. payload compressé au format 8-in-7 (un octet de bits hauts suivi d'un groupe pouvant contenir jusqu'à sept octets de données) ;
7. checksum sur 14 bits ;
8. longueur sur 14 bits ;
9. délimiteur F7.

Dans le payload décodé, les quatre octets de tags se trouvent aux positions 8 à 11 et le nom occupe les positions 12 à 26, avec un éventuel terminateur nul. Le codage des tags et leur signification dépendent du modèle.

Cette description est un format de travail issu de l'analyse d'implémentations publiques, pas une spécification officielle Elektron. Les tests SoundLab construisent des messages synthétiques et vérifient la cohérence des champs ; ils ne constituent pas une validation sur machine réelle.

## Ce que cette inspection ne fait pas

- Elle ne décode pas les paramètres de synthèse FM ou analogiques.
- Elle ne reconstruit pas les Patterns, Kits, Projects, Songs, routages, automations ou états complets de la machine.
- Elle ne transforme pas un .afsnd ou un .dnsnd en message SysEx.
- Elle ne déduit pas qu'un fichier inconnu est sûr parce qu'il contient le fabricant Elektron.
- Elle ne valide pas l'acceptation matérielle du message après mise en file MIDI.

Un fichier .syx peut contenir plusieurs sous-types SysEx. En v3.6, seuls les messages identifiés comme Sounds individuels selon les contrôles ci-dessus sont proposés à la mise en file. Les autres restent inspectables comme données non transférables.

## Distinction essentielle : .syx et fichiers natifs Transfer

Les messages Sound SysEx et les conteneurs natifs .afsnd / .dnsnd sont des représentations différentes. Elektron Transfer emploie son propre flux de communication USB-MIDI pour gérer les fichiers natifs. SoundLab ne réimplémente pas ce protocole et ne prétend pas remplacer Transfer.

## Garde-fous d'envoi

Pour mettre en file un Sound SysEx reconnu, SoundLab exige :

- un modèle cible explicitement sélectionné ;
- une correspondance exacte entre le modèle du message et la cible choisie ;
- l'accusé de lecture des consignes de sécurité ;
- la confirmation de l'opération ;
- le respect des limites de taille et de nombre de messages déjà appliquées par l'application.

Avant tout essai matériel, sauvegarder la machine, sélectionner le mode de réception et le slot appropriés, et commencer avec un Sound non critique. L'appel Web MIDI confirme au mieux la mise en file côté navigateur/OS : il ne confirme ni la réception, ni l'acceptation, ni l'écriture sur le matériel.

## Références de recherche

- Digitools — README : https://github.com/ashojaeddini/digitools — périmètre annoncé de lecture/édition des noms et tags des Sounds A4 et Digitone.
- Digitools — sound.py : https://github.com/ashojaeddini/digitools/blob/master/digitools/sound.py — structure des messages, identifiants de modèles, encodage 8-in-7, checksum, longueur, nom et tags.
- Digitools — sysex.py : https://github.com/ashojaeddini/digitools/blob/master/digitools/sysex.py — séparation F0/F7 et encodeur/décodeur 7-bit.
- libdigitone : https://github.com/d-huck/libdigitone — recherche antérieure sur les paramètres de patch Digitone. Son auteur signale lui-même des limites de validation ; ce projet ne décode pas les Patterns et ne fournit pas d'encodeur complet.
- Manuel officiel Digitone OS 1.41 : https://www.elektron.se/wp-content/uploads/2024/09/Digitone_User_Manual_ENG_OS1.41_231108.pdf — référence utilisateur et MIDI pour le Digitone MK1.

Les dépôts cités sont des travaux communautaires indépendants. Leur existence ne signifie pas que l'ensemble de leurs hypothèses ou mappings a été vérifié par Elektron ou par un essai physique SoundLab.
