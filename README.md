# IMAC WARS

IMAC WARS is a strategic game and a student project coded in C/C++.

## Rules

The game is played by two or three players. The goal is to destroy all enemy units on the ground.

The maximum number of units present on the field is 18. You can therefore have up to 9 units (in two-player mode).

There are currently 3 different types of units, each with its specificities.

The players take turns. On each turn, the player can perform two actions to follow. The possible actions are either to move or to attack.

The movement is done according to the dexterity of the unit. Certain movements will therefore be impossible.

The attack is also made according to the range of the unit. The enemy will therefore sometimes be too far away to be hit. Just like the damage inflicted by your attack will be calculated according to this distance, but also according to the strength of your unit. Depending on the types of units that confront each other, the damage will be adapted.
Each of your shots creates a damage zone. If there are enemies in this area, they will be impacted by your attack. However, the damage will be much less than a direct attack. So be careful if you shoot into the void, you will not do any damage.

Randomly, bonuses are dropped on the field. It can be a bonus of health, dexterity or strength. It is up to you to judge if these can be useful in your quest for victory.

As the head of your army, use strategy and anticipation to carry out your battle and achieve victory.

## Getting Started

To play the game, open your terminal and go to the main directory of the project.

### Start a game

Then, you just have to enter the two following commands

```
make
```

```
./imacwars
```

## Authors

* **Nils Landrodie** - *master's degree student in engineering from IMAC*
* **Vincent Scavinner** - *master's degree student in engineering from IMAC*

## Possible upgrades

Here is a non-exhaustive list of possible upgrades to implement

* Create a graphical environment using the SDL library
* Make more or less effective unit against other types of unit
* Add music according to the current action
* Add experience points to be able to buy units or bonuses

