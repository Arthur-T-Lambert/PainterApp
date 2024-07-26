# PainterApp
Projet de groupe ayant pour but de recréer une application de dessin, ainsi que sa documentation.

L'installer est à la racine du projet.
Pour générer l'installateur :
	- Compiler le projet en mode Release.
	- Mettre l'executable dans un dossier à part et lancer la commande : 'C:/Qt/6.7.2/mingw_64/bin/windeployqt.exe Release/PainterApplication.exe' (où Release est le dossier à part)
	- Ajouter les fichiers libgcc_s_seh-1.dll, libstdc++-6.dll, libwinpthread-1.dll si il ne sont pas présents.
	- Ziper le contenu du dossier et mettre le zip dans le dossier InstallerConfig/packages/com.vendor.root/data
	- Lancer la commande :
'C:/Qt/QtIFW-4.7.0/bin/binarycreator.exe -c InstallerConfig/config/config.xml -p InstallerConfig/packages PainterAppInstaller.exe'
-> L'instalateur est créé