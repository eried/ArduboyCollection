# `template.html` mustache reference

* First, check the mustache [reference](https://mustache.github.io/mustache.5.html).
* Paste the contents of the modified `template.html` [here](https://mustache.github.io/#demo) in the 
first field.
* Paste http://arduboy.ried.cl/repo.json contents in the second field to test it without installing anything.

# Updater

# Requirements

  sudo apt install php7.0-cli
  sudo apt install php7.0-xml
  sudo apt install php-curl
  
# Running

  php update.php
  git add ../*
  git commit -m "Repository update"
  git push