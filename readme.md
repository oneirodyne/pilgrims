# Game Guide

## Values

* Food : If you have no food in your stocks, your game will end. Every round, you will lose food amounting to one third of your population. Food can be gained through farming.
* Population : If your population is less than 10, your population will vanish into obscurity. Every round, you will gain population amounting to one tenth of your food. You may want to control your population by sending your people to death in the mines, so that you dont have too many mouths to feed.
* Resources : Resources are primarily used to farm food. They can be obtained through producing.
* Piety : If you have less than 10 piety, your population will lose hope and go insane. Every kill takes 0.5 Piety from you. It can be gained through praying.
* Tribal Relations : Tribal Relations represent your diplomatic status with the local native tribes. It decreases by 3 every day. You can influence it through prostelytizing, extortion, or trade. Depending on your relations, you may get hostile or friendly events from the native tribes.

## Command Guide

Every base command takes one action.

### Base Commands

* end : Surrenders your remaining actions, and ends the day.
* exit : Exits the game.
* pray : Adds a fixed value of 5 to your Piety.
* farm : Removes a fixed value of 5 from your Resources, and adds Food amounting to a fifth of your population.
* prod : Removes between 1 and 10 people, and adds a fixed value of 10 Resources.
* trib : Allows you to enter a Tribal Diplomacy command.

### Tribe Diplomacy 

* pros : Adds a fixed value of 10 Piety, removes a fixed value of 5 Relations.
* exto : Adds a fixed value of 25 Resources, removes a fixed value of 20 Relations and 10 Piety.
* trad : Removes a fixed value of 25 Resources, adds a fixed value of 50 Food and 12 Relations.

## Strategy Guide

WORK IN PROGRESS!!!

# Code Documentation

## Compilation

To compile, change directory into the pilgrims folder, then run make.sh. This expects you to have GCC, but you can change it to something else if you'd like.
