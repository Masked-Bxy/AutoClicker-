#!/bin/bash

# Vérifier si on est dans un repo Git
if ! git rev-parse --is-inside-work-tree >/dev/null 2>&1; then
    echo "Erreur : Ce script doit être exécuté dans un repository Git."
    exit 1
fi

echo "Analyse du repository..."

# Compter le nombre total de commits
commit_count=$(git rev-list --count --all)

# Initialisation
code_line_count=0
h_count=0
hpp_count=0
cpp_count=0

# Vérifier si GameLoop existe
if [ -d "GameLoop" ]; then

    # Compter les lignes de code
    code_line_count=$(find GameLoop \
        -type d \( -name Dependencies -o -name x64 \) -prune -o \
        -type f \( -name "*.c" -o -name "*.h" -o -name "*.hpp" -o -name "*.cpp" \) \
        -print | xargs wc -l 2>/dev/null | tail -n 1 | awk '{print $1}')

    # Compter les fichiers
    h_count=$(find GameLoop -type d \( -name Dependencies -o -name x64 \) -prune -o -type f -name "*.h" -print | wc -l)
    hpp_count=$(find GameLoop -type d \( -name Dependencies -o -name x64 \) -prune -o -type f -name "*.hpp" -print | wc -l)
    cpp_count=$(find GameLoop -type d \( -name Dependencies -o -name x64 \) -prune -o -type f -name "*.cpp" -print | wc -l)

fi

# Générer readme.md
{
echo "# Statistiques du projet"
echo
echo "- **Nombre total de commits : $commit_count**"
echo "- **Nombre de lignes de code dans GameLoop : $code_line_count**"
echo
echo "## Fichiers"
echo "- **.h : $h_count**"
echo "- **.hpp : $hpp_count**"
echo "- **.cpp : $cpp_count**"
} > readme.md

echo "Fichier readme.md mis à jour."