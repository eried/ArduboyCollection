# Erwin's Arduboy Collection

[![paypal](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=CLCKXMYJUWA8Y&source=url)

You can browse this repo here:
http://arduboy.ried.cl

Json file for the repository:
http://arduboy.ried.cl/repo.json

## Play games

### Windows

1. Install [Arduboy Uploader](https://github.com/eried/ArduboyUploader/releases/latest)

2. Browse this repository using http://arduboy.ried.cl, if you clicked yes to the _arduboy: protocol_ association when installing Arduboy Uploader, you can click "Upload to my Arduboy", otherwise just download the games and open Arduboy Uploader manually

_Also, check out [alternatives](https://community.arduboy.com/t/how-to-upload-a-hex-to-the-arduboy/4081) for this platform._

### Android

1. Install [Arby Utility](https://play.google.com/store/apps/details?id=com.obnsoft.arduboyutil)

2. Click "Upload to my Arduboy" in http://arduboy.ried.cl and follow Arduboy Utility steps in your phone

_Also, check out [alternatives](https://play.google.com/store/apps/details?id=de.mockfrog.arduboymate) for this platform._

![Demo](/demo.jpg)

## Submit your game
1. Fork this repo (If you *do not get* what this step means, **stop** and follow [this steps](https://community.arduboy.com/t/big-asteroids/5994/7))
2. Create a new unique folder (case insensitive) for your game under an existent category folder (i.e. Arcade, RPG, etc)
3. Inside your folder, place:

| Filename | Description |
| ------ | ------ |
| anything.hex | Your compiled game for the Arduboy (check [below](#get-your-gamehex-file) for more details) |
| anything.png | Banner image / screenshot of the game |
| anything.url | Game details URL (using the typical browser format for bookmark files, check [below](#url-format))|
| game.ini | Information of the game (check [below](#gameini-format) for format details)|
| source.url | (Optional) Contains the URL of the source code of the game|

4. Sync your fork and Create a Pull request

### game.ini format
```
title=Game name
date=yyyy-MM-ddTHH:mm:ssZ
author=Author
description=Description of the game
license=Identifier of the license used in the game
```
Instead of typing the date and time for the `date` variable, you can use: https://www.utctime.net/

For the `license` variable, you need to use one of the identifiers defined here: https://spdx.org/licenses/

You can also add the following entry to reference a remote file. If you are linking to github, make sure it is the "Raw" version of the url and not the github details for the file.

```
hex=http://url.to/your/own/server-with-the/game.hex
```

This file is parsed by php's [parse-ini-file](http://php.net/manual/en/function.parse-ini-file.php) function, try to avoid trailing spaces.

### .url format
__TIP:__ You can drag from the left side of your browser's address bar to a folder to get the .url file of the current webpage
```
[InternetShortcut]
URL=https://url.to/the/website
```

A webhook updates the repository static json file after a commit automatically. 

### Get your game.hex file

1. Open your code in Arduino IDE
2. Click `Sketch / Export compiled Binary`
3. Click `Sketch / Show Sketch Folder`

__WARNING:__ Do not use the `with_bootloader.leonardo.hex` file. This file may brick your Arduboy. [Arduboy Uploader](https://github.com/eried/ArduboyUploader/releases/latest) will protect your Arduboy from this kind of issues, but if you manage to brick your device, check the following [instructions](https://community.arduboy.com/t/bring-your-arduboy-back-from-the-dead-burn-bootloader/3422)
