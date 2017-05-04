# Erwin's Arduboy Collection

Access the repository here:
http://arduboy.ried.cl/repo.json

## Usage

Use the repository in your own application or in an Arduboy uploader like Arduboy Mate for Android:
https://play.google.com/store/apps/details?id=de.mockfrog.arduboymate&hl=en

![GitHub Logo](/demo.jpg)

## Submission files

For this early version, the way the repository works is like this:
_category/Game Name/somefile.hex_: file.hex is the binary for the Arduboy

Inside that directory:
_anything.png:_ Correspond to the banner
_description.txt:_ Contains the description to be parsed
_anything.url:_ Contains the URL (using the typical browser format for bookmark files)

A webhook updates the repository static json file after a commit automatically. 
