# This script tracks the local changes, adds those changes into staging,
# commits them and then pushes the changes to the main branch.
git add .
if [ -z "$1" ]
  then
    git commit -m "generalized commit"
else
    git commit -m "$1"
fi
git push origin main