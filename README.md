# SmallCardGame

![Screenshot of game state](screen.png?raw=true "Title")

Simple card game inspired by Hearthstone, semestral work for PA2 class in C++ with focus on OOP and polymorphism

The objective is to kill the other player. That can be done by building a strong board and by playing the right cards.
Key elements are Spells and Minions which cost your mana and can be played during your turn.
Player's mana is restored each round and increased by one.

The game supports match against other player and against computer.
The games can be saved/loaded and you can define your own cards in the preset.

### How to play it
I've used makefile in order to compile and resolve dependencies. Simply run

```
make compile
```

And then 

```
./game
```
to start it up.
### Documentation
Doxygen is required and can generate the documentation by typing: 
```
make doc
```

