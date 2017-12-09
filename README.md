# Erwin's Arduboy Collection

You can browse this repo here:
http://arduboy.ried.cl

Json file for the repository:
http://arduboy.ried.cl/repo.json

## Loading the games

### Windows

1. Install [Arduboy Uploader](https://github.com/eried/ArduboyUploader/releases/latest)

2. Browse this repository using http://arduboy.ried.cl, if you clicked yes to the _arduboy: protocol_ association when installing Arduboy Uploader, you can click "Upload to my Arduboy", otherwise just download the games and open Arduboy Uploader manually

_Also, check out [other alternatives](https://community.arduboy.com/t/how-to-upload-a-hex-to-the-arduboy/4081) for this platform._

### Android

1. Install [Arduboy Utility](https://play.google.com/store/apps/details?id=com.obnsoft.arduboyutil)

2. Click "Upload to my Arduboy" in http://arduboy.ried.cl and follow Arduboy Utility steps in your phone

_Also, check out [other alternatives](https://play.google.com/store/apps/details?id=de.mockfrog.arduboymate&hl=en) for this platform._

![Demo](/demo.jpg)

## How to submit your game
1. Fork this repo
2. Create a new folder for your game under a category (you cannot create new categories, so choose one of the current available ones)
3. Inside that directory place the following files:

| Filename | Description |
| ------ | ------ |
| anything.hex | Binary file for the Arduboy |
| anything.png | Banner image / screenshot of the game |
|description.txt| (Optional, deprecated) Contains the description to be parsed |
|game.ini|Text file with information of the game (check below for format details)|
|anything.url|Contains the URL (using the typical browser format for bookmark files, check below)|
|source.url| (Optional) Contains the URL of the source code of the game|

4. Create a Pull request with your changes

### game.ini format
```
title=Game name
date=yyyy-MM-ddTHH:mm:ssZ
author=Author
description=Description of the game
```
### .url format
__TIP:__ You can drag from the left side of your browser's address bar to a folder to get the .url file of the current webpage
```
[InternetShortcut]
URL=https://url.to/the/website
```

A webhook updates the repository static json file after a commit automatically. 
