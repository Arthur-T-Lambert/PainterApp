# Projet de Recréation d'Application de Dessin

## Description

Ce projet de groupe vise à recréer une application de dessin ainsi que sa documentation.

## Génération de l'Installateur

Pour générer l'installateur, suivez ces étapes :

1. **Compiler le projet en mode Release**
   - Assurez-vous que le projet est compilé en mode Release.

2. **Préparer l'exécutable**
   - Placez l'exécutable compilé dans un dossier à part (nommons ce dossier `Release`).
   - Exécutez la commande suivante pour déployer les dépendances nécessaires :
     ```bash
     C:/Qt/6.7.2/mingw_64/bin/windeployqt.exe Release/PainterApplication.exe
     ```
     (où `Release` est le dossier contenant l'exécutable)

3. **Ajouter les fichiers DLL manquants**
   - Si les fichiers suivants ne sont pas présents dans le dossier, ajoutez-les :
     - `libgcc_s_seh-1.dll`
     - `libstdc++-6.dll`
     - `libwinpthread-1.dll`

4. **Préparer le package**
   - Zippez le contenu du dossier contenant l'exécutable et les fichiers DLL.
   - Placez le fichier zip dans le dossier `InstallerConfig/packages/com.vendor.root/data`.

5. **Créer l'installateur**
   - Lancez la commande suivante pour créer l'installateur :
     ```bash
     C:/Qt/QtIFW-4.7.0/bin/binarycreator.exe -c InstallerConfig/config/config.xml -p InstallerConfig/packages PainterAppInstaller.exe
     ```
   - L'installateur `PainterAppInstaller.exe` sera alors créé.

## Notes

- Assurez-vous que toutes les dépendances et configurations sont correctement définies pour éviter les erreurs lors de la création de l'installateur.
- Les chemins d'accès mentionnés sont basés sur une installation par défaut de Qt et QtIFW. Modifiez-les en fonction de votre configuration locale.

