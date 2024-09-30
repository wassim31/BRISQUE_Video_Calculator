## Building process

This a technical test provided by Mr Abderrezzaq Sendjasni for an Internship opportunity.

## #Développement d’un système d’acquisition de flux visuel avec contrôle de qualité en temps réel par la métrique BRISQUE.

Description :
Ce projet consiste à développer un système capable de capturer un flux vidéo en temps réel et
d’appliquer la métrique de qualité visuelle BRISQUE sur chaque image du flux. Le score de qualité
sera affiché en direct sur la vidéo visualisée et sauvegardé pour des analyses ultérieures, afin
d'évaluer la performance et la variation de la qualité du flux au fil du temps.
Objectifs :
1. Système d'acquisition de flux visuel :
• Développer un système qui capture des flux vidéo en temps réel à partir d'une caméra
ou d'un fichier vidéo (par exemple, via OpenCV).

Pour l'utilisation avec une vidéo déja prete : 

./main <input.avi\.mp4\.MPEG> frame_delay_in_ms

Pour l'utilisation avec votre camera de pc ajouter la valeur 0 en input_file: 

./main 0 frame_delay_in_ms


2. Application de la métrique BRISQUE :
• Implémenter la métrique BRISQUE (Blind/Referenceless Image Spatial Quality
Evaluator) pour analyser les images du flux en temps réel et calculer des scores de
qualité visuelle. Un tutoriel assez exhaustive sur cette métriques ainsi que le code
pour la mettre en œuvre (Python ou C++) se trouve sur ce lien.
• Superposer le score BRISQUE en temps réel directement sur la vidéo visualisée.
3. Enregistrement des résultats pour analyse ultérieure :
• Sauvegarder les scores BRISQUE associés à chaque frame avec un horodatage pour
permettre une analyse statistique ou visuelle des données plus tard.

Livrables attendus :
1. Système d’acquisition et d’évaluation :
• Un système capable de capturer un flux vidéo en temps réel, d’appliquer la métrique
BRISQUE sur chaque image, et d’afficher le score de qualité superposé directement
sur la vidéo.

2. Rapport succinct :
• Un rapport contenant :
• Visualisation des courbes de score BRISQUE : Graphiques illustrant
l’évolution du score BRISQUE au fil du temps, avec des commentaires sur le
comportement observé et les variations de qualité.
• Explication technique : Une bref description du processus de mise en œuvre
et des défis rencontrés durant le développement.

to plot results in c++ , i tried to port matplotlib in c++ using the library : https://github.com/lava/matplotlib-cpp/ but it creates many linking problems , so i'll extract the results as a txt or csv and plot them easily with a python script