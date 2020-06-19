PROGRAM=game

CC=g++
CFLAGS=-std=c++11 -Wall -pedantic -Wextra -g -Wno-long-long -O0 -ggdb

all: compile doc

run: compile
	./$(PROGRAM)

compile: $(PROGRAM)

doc: 
	doxygen Doxyfile

$(PROGRAM): objs/main.o objs/Card.o objs/Minion.o objs/Spell.o \
 objs/DamageEnemyMinionsEffect.o objs/DiscardCardEffect.o objs/DrawCardEffect.o \
 objs/GainManaEffect.o objs/HealHeroEffect.o objs/Entity.o objs/Player.o objs/AIPlayer.o \
 objs/GameManager.o objs/GameSaver.o objs/GUI.o objs/Game.o objs/AssetLoader.o \
 objs/Board.o objs/Menu.o 
	$(CC) $(CFLAGS) $^ -o $@

objs/main.o: src/main.cpp src/Game/Game.h src/Game/GameManager.h \
 src/Game/AssetLoader.h src/Game/../Cards/Card.h \
 src/Game/../Cards/../Effects/Effect.h src/Game/../Entities/Player.h \
 src/Game/../Entities/Entity.h src/Game/../Entities/../Cards/Card.h \
 src/Game/../Entities/../Game/Board.h \
 src/Game/../Entities/../Game/../Cards/Minion.h \
 src/Game/../Entities/../Game/../Cards/Card.h \
 src/Game/../Entities/../Game/../Cards/../Entities/Entity.h \
 src/Game/../Entities/../Game/../Entities/Player.h \
 src/Game/../Entities/../Effects/DiscardCardEffect.h \
 src/Game/../Entities/../Effects/Effect.h \
 src/Game/../Entities/../Effects/../Entities/Player.h src/Game/Board.h \
 src/Game/../Entities/AIPlayer.h src/Game/../Entities/Player.h \
 src/Game/Menu/Menu.h src/Game/Menu/MenuItem.h src/Game/Menu/../GUI.h \
 src/Game/Menu/../../Entities/Player.h src/Game/Menu/../GameManager.h \
 src/Game/Menu/../GameManager.h src/Game/Menu/../GameSaver.h | objs
	$(CC) $(CFLAGS) -c $< -o $@


objs/Card.o: src/Cards/Card.cpp src/Cards/Card.h src/Cards/../Effects/Effect.h | objs
	$(CC) $(CFLAGS) -c $< -o $@

objs/Minion.o: src/Cards/Minion.cpp src/Cards/Minion.h src/Cards/Card.h \
 src/Cards/../Effects/Effect.h src/Cards/../Entities/Entity.h \
 src/Cards/../Game/GameManager.h src/Cards/../Game/AssetLoader.h \
 src/Cards/../Game/../Cards/Card.h src/Cards/../Game/../Entities/Player.h \
 src/Cards/../Game/../Entities/Entity.h \
 src/Cards/../Game/../Entities/../Cards/Card.h \
 src/Cards/../Game/../Entities/../Game/Board.h \
 src/Cards/../Game/../Entities/../Game/../Cards/Minion.h \
 src/Cards/../Game/../Entities/../Game/../Entities/Player.h \
 src/Cards/../Game/../Entities/../Effects/DiscardCardEffect.h \
 src/Cards/../Game/../Entities/../Effects/Effect.h \
 src/Cards/../Game/../Entities/../Effects/../Entities/Player.h \
 src/Cards/../Game/Board.h src/Cards/../Game/../Entities/AIPlayer.h \
 src/Cards/../Game/../Entities/Player.h | objs
	$(CC) $(CFLAGS) -c $< -o $@
	
objs/Spell.o: src/Cards/Spell.cpp src/Cards/Spell.h src/Cards/Card.h \
 src/Cards/../Effects/Effect.h src/Cards/../Entities/Player.h \
 src/Cards/../Entities/Entity.h src/Cards/../Entities/../Cards/Card.h \
 src/Cards/../Entities/../Game/Board.h \
 src/Cards/../Entities/../Game/../Cards/Minion.h \
 src/Cards/../Entities/../Game/../Cards/Card.h \
 src/Cards/../Entities/../Game/../Cards/../Entities/Entity.h \
 src/Cards/../Entities/../Game/../Entities/Player.h \
 src/Cards/../Entities/../Effects/DiscardCardEffect.h \
 src/Cards/../Entities/../Effects/Effect.h \
 src/Cards/../Entities/../Effects/../Entities/Player.h | objs
	$(CC) $(CFLAGS) -c $< -o $@
	
#objs/Effect.o: src/Effects/Effect.h | objs
#	$(CC) $(CFLAGS) -c $< -o $@

objs/DamageEnemyMinionsEffect.o: src/Effects/DamageEnemyMinionsEffect.cpp \
 src/Effects/DamageEnemyMinionsEffect.h src/Effects/../Entities/Player.h \
 src/Effects/../Entities/Entity.h src/Effects/../Entities/../Cards/Card.h \
 src/Effects/../Entities/../Cards/../Effects/Effect.h \
 src/Effects/../Entities/../Game/Board.h \
 src/Effects/../Entities/../Game/../Cards/Minion.h \
 src/Effects/../Entities/../Game/../Cards/Card.h \
 src/Effects/../Entities/../Game/../Cards/../Entities/Entity.h \
 src/Effects/../Entities/../Game/../Entities/Player.h \
 src/Effects/../Entities/../Effects/DiscardCardEffect.h \
 src/Effects/../Entities/../Effects/Effect.h \
 src/Effects/../Entities/../Effects/../Entities/Player.h | objs
	$(CC) $(CFLAGS) -c $< -o $@

objs/DiscardCardEffect.o: src/Effects/DiscardCardEffect.cpp \
 src/Effects/DiscardCardEffect.h src/Effects/Effect.h \
 src/Effects/../Entities/Player.h src/Effects/../Entities/Entity.h \
 src/Effects/../Entities/../Cards/Card.h \
 src/Effects/../Entities/../Cards/../Effects/Effect.h \
 src/Effects/../Entities/../Game/Board.h \
 src/Effects/../Entities/../Game/../Cards/Minion.h \
 src/Effects/../Entities/../Game/../Cards/Card.h \
 src/Effects/../Entities/../Game/../Cards/../Entities/Entity.h \
 src/Effects/../Entities/../Game/../Entities/Player.h \
 src/Effects/../Entities/../Effects/DiscardCardEffect.h | objs
	$(CC) $(CFLAGS) -c $< -o $@

objs/DrawCardEffect.o: src/Effects/DrawCardEffect.cpp \
 src/Effects/DrawCardEffect.h src/Effects/../Entities/Player.h \
 src/Effects/../Entities/Entity.h src/Effects/../Entities/../Cards/Card.h \
 src/Effects/../Entities/../Cards/../Effects/Effect.h \
 src/Effects/../Entities/../Game/Board.h \
 src/Effects/../Entities/../Game/../Cards/Minion.h \
 src/Effects/../Entities/../Game/../Cards/Card.h \
 src/Effects/../Entities/../Game/../Cards/../Entities/Entity.h \
 src/Effects/../Entities/../Game/../Entities/Player.h \
 src/Effects/../Entities/../Effects/DiscardCardEffect.h \
 src/Effects/../Entities/../Effects/Effect.h \
 src/Effects/../Entities/../Effects/../Entities/Player.h | objs
	$(CC) $(CFLAGS) -c $< -o $@

objs/GainManaEffect.o: src/Effects/GainManaEffect.cpp \
 src/Effects/GainManaEffect.h src/Effects/../Entities/Player.h \
 src/Effects/../Entities/Entity.h src/Effects/../Entities/../Cards/Card.h \
 src/Effects/../Entities/../Cards/../Effects/Effect.h \
 src/Effects/../Entities/../Game/Board.h \
 src/Effects/../Entities/../Game/../Cards/Minion.h \
 src/Effects/../Entities/../Game/../Cards/Card.h \
 src/Effects/../Entities/../Game/../Cards/../Entities/Entity.h \
 src/Effects/../Entities/../Game/../Entities/Player.h \
 src/Effects/../Entities/../Effects/DiscardCardEffect.h \
 src/Effects/../Entities/../Effects/Effect.h \
 src/Effects/../Entities/../Effects/../Entities/Player.h | objs
	$(CC) $(CFLAGS) -c $< -o $@

objs/HealHeroEffect.o: src/Effects/HealHeroEffect.cpp \
 src/Effects/HealHeroEffect.h src/Effects/../Entities/Player.h \
 src/Effects/../Entities/Entity.h src/Effects/../Entities/../Cards/Card.h \
 src/Effects/../Entities/../Cards/../Effects/Effect.h \
 src/Effects/../Entities/../Game/Board.h \
 src/Effects/../Entities/../Game/../Cards/Minion.h \
 src/Effects/../Entities/../Game/../Cards/Card.h \
 src/Effects/../Entities/../Game/../Cards/../Entities/Entity.h \
 src/Effects/../Entities/../Game/../Entities/Player.h \
 src/Effects/../Entities/../Effects/DiscardCardEffect.h \
 src/Effects/../Entities/../Effects/Effect.h \
 src/Effects/../Entities/../Effects/../Entities/Player.h | objs
	$(CC) $(CFLAGS) -c $< -o $@

objs/Entity.o: src/Entities/Entity.cpp src/Entities/Entity.h | objs
	$(CC) $(CFLAGS) -c $< -o $@

objs/Player.o: src/Entities/Player.cpp src/Entities/Player.h \
 src/Entities/Entity.h src/Entities/../Cards/Card.h \
 src/Entities/../Cards/../Effects/Effect.h src/Entities/../Game/Board.h \
 src/Entities/../Game/../Cards/Minion.h \
 src/Entities/../Game/../Cards/Card.h \
 src/Entities/../Game/../Cards/../Entities/Entity.h \
 src/Entities/../Game/../Entities/Player.h \
 src/Entities/../Effects/DiscardCardEffect.h \
 src/Entities/../Effects/Effect.h \
 src/Entities/../Effects/../Entities/Player.h | objs
	$(CC) $(CFLAGS) -c $< -o $@

objs/AIPlayer.o: src/Entities/AIPlayer.cpp src/Entities/AIPlayer.h \
 src/Entities/Player.h src/Entities/Entity.h src/Entities/../Cards/Card.h \
 src/Entities/../Cards/../Effects/Effect.h src/Entities/../Game/Board.h \
 src/Entities/../Game/../Cards/Minion.h \
 src/Entities/../Game/../Cards/Card.h \
 src/Entities/../Game/../Cards/../Entities/Entity.h \
 src/Entities/../Game/../Entities/Player.h \
 src/Entities/../Effects/DiscardCardEffect.h \
 src/Entities/../Effects/Effect.h \
 src/Entities/../Effects/../Entities/Player.h | objs
	$(CC) $(CFLAGS) -c $< -o $@

objs/GameManager.o: src/Game/GameManager.cpp src/Game/GameManager.h \
 src/Game/AssetLoader.h src/Game/../Cards/Card.h \
 src/Game/../Cards/../Effects/Effect.h src/Game/../Entities/Player.h \
 src/Game/../Entities/Entity.h src/Game/../Entities/../Cards/Card.h \
 src/Game/../Entities/../Game/Board.h \
 src/Game/../Entities/../Game/../Cards/Minion.h \
 src/Game/../Entities/../Game/../Cards/Card.h \
 src/Game/../Entities/../Game/../Cards/../Entities/Entity.h \
 src/Game/../Entities/../Game/../Entities/Player.h \
 src/Game/../Entities/../Effects/DiscardCardEffect.h \
 src/Game/../Entities/../Effects/Effect.h \
 src/Game/../Entities/../Effects/../Entities/Player.h src/Game/Board.h \
 src/Game/../Entities/AIPlayer.h src/Game/../Entities/Player.h | objs
	$(CC) $(CFLAGS) -c $< -o $@

objs/GameSaver.o: src/Game/GameSaver.cpp src/Game/GameSaver.h \
 src/Game/GameManager.h src/Game/AssetLoader.h src/Game/../Cards/Card.h \
 src/Game/../Cards/../Effects/Effect.h src/Game/../Entities/Player.h \
 src/Game/../Entities/Entity.h src/Game/../Entities/../Cards/Card.h \
 src/Game/../Entities/../Game/Board.h \
 src/Game/../Entities/../Game/../Cards/Minion.h \
 src/Game/../Entities/../Game/../Cards/Card.h \
 src/Game/../Entities/../Game/../Cards/../Entities/Entity.h \
 src/Game/../Entities/../Game/../Entities/Player.h \
 src/Game/../Entities/../Effects/DiscardCardEffect.h \
 src/Game/../Entities/../Effects/Effect.h \
 src/Game/../Entities/../Effects/../Entities/Player.h src/Game/Board.h \
 src/Game/../Entities/AIPlayer.h src/Game/../Entities/Player.h \
 src/Game/../Cards/Spell.h src/Game/../Cards/Card.h | objs
	$(CC) $(CFLAGS) -c $< -o $@
 
objs/GUI.o: src/Game/GUI.cpp src/Game/GUI.h src/Game/../Entities/Player.h \
 src/Game/../Entities/Entity.h src/Game/../Entities/../Cards/Card.h \
 src/Game/../Entities/../Cards/../Effects/Effect.h \
 src/Game/../Entities/../Game/Board.h \
 src/Game/../Entities/../Game/../Cards/Minion.h \
 src/Game/../Entities/../Game/../Cards/Card.h \
 src/Game/../Entities/../Game/../Cards/../Entities/Entity.h \
 src/Game/../Entities/../Game/../Entities/Player.h \
 src/Game/../Entities/../Effects/DiscardCardEffect.h \
 src/Game/../Entities/../Effects/Effect.h \
 src/Game/../Entities/../Effects/../Entities/Player.h \
 src/Game/GameManager.h src/Game/AssetLoader.h src/Game/../Cards/Card.h \
 src/Game/Board.h src/Game/../Entities/AIPlayer.h \
 src/Game/../Entities/Player.h | objs
	$(CC) $(CFLAGS) -c $< -o $@

objs/Game.o: src/Game/Game.cpp src/Game/Game.h src/Game/GameManager.h \
 src/Game/AssetLoader.h src/Game/../Cards/Card.h \
 src/Game/../Cards/../Effects/Effect.h src/Game/../Entities/Player.h \
 src/Game/../Entities/Entity.h src/Game/../Entities/../Cards/Card.h \
 src/Game/../Entities/../Game/Board.h \
 src/Game/../Entities/../Game/../Cards/Minion.h \
 src/Game/../Entities/../Game/../Cards/Card.h \
 src/Game/../Entities/../Game/../Cards/../Entities/Entity.h \
 src/Game/../Entities/../Game/../Entities/Player.h \
 src/Game/../Entities/../Effects/DiscardCardEffect.h \
 src/Game/../Entities/../Effects/Effect.h \
 src/Game/../Entities/../Effects/../Entities/Player.h src/Game/Board.h \
 src/Game/../Entities/AIPlayer.h src/Game/../Entities/Player.h \
 src/Game/Menu/Menu.h src/Game/Menu/MenuItem.h src/Game/Menu/../GUI.h \
 src/Game/Menu/../../Entities/Player.h src/Game/Menu/../GameManager.h \
 src/Game/Menu/../GameManager.h src/Game/Menu/../GameSaver.h \
 src/Game/GameSaver.h | objs
	$(CC) $(CFLAGS) -c $< -o $@

objs/AssetLoader.o: src/Game/AssetLoader.cpp src/Game/AssetLoader.h \
 src/Game/../Cards/Card.h src/Game/../Cards/../Effects/Effect.h \
 src/Game/../Cards/Minion.h src/Game/../Cards/Card.h \
 src/Game/../Cards/../Entities/Entity.h \
 src/Game/../Effects/DrawCardEffect.h \
 src/Game/../Effects/../Entities/Player.h \
 src/Game/../Effects/../Entities/Entity.h \
 src/Game/../Effects/../Entities/../Cards/Card.h \
 src/Game/../Effects/../Entities/../Game/Board.h \
 src/Game/../Effects/../Entities/../Game/../Cards/Minion.h \
 src/Game/../Effects/../Entities/../Game/../Entities/Player.h \
 src/Game/../Effects/../Entities/../Effects/DiscardCardEffect.h \
 src/Game/../Effects/../Entities/../Effects/Effect.h \
 src/Game/../Effects/../Entities/../Effects/../Entities/Player.h \
 src/Game/../Effects/DiscardCardEffect.h src/Game/../Cards/Spell.h \
 src/Game/../Effects/DamageEnemyMinionsEffect.h \
 src/Game/../Effects/HealHeroEffect.h \
 src/Game/../Effects/GainManaEffect.h | objs
	$(CC) $(CFLAGS) -c $< -o $@

objs/Board.o: src/Game/Board.cpp src/Game/Board.h src/Game/../Cards/Minion.h \
 src/Game/../Cards/Card.h src/Game/../Cards/../Effects/Effect.h \
 src/Game/../Cards/../Entities/Entity.h src/Game/../Entities/Player.h \
 src/Game/../Entities/Entity.h src/Game/../Entities/../Cards/Card.h \
 src/Game/../Entities/../Game/Board.h \
 src/Game/../Entities/../Effects/DiscardCardEffect.h \
 src/Game/../Entities/../Effects/Effect.h \
 src/Game/../Entities/../Effects/../Entities/Player.h | objs
	$(CC) $(CFLAGS) -c $< -o $@

objs/Menu.o: src/Game/Menu/Menu.cpp src/Game/Menu/Menu.h \
 src/Game/Menu/MenuItem.h src/Game/Menu/../GUI.h \
 src/Game/Menu/../../Entities/Player.h \
 src/Game/Menu/../../Entities/Entity.h \
 src/Game/Menu/../../Entities/../Cards/Card.h \
 src/Game/Menu/../../Entities/../Cards/../Effects/Effect.h \
 src/Game/Menu/../../Entities/../Game/Board.h \
 src/Game/Menu/../../Entities/../Game/../Cards/Minion.h \
 src/Game/Menu/../../Entities/../Game/../Cards/Card.h \
 src/Game/Menu/../../Entities/../Game/../Cards/../Entities/Entity.h \
 src/Game/Menu/../../Entities/../Game/../Entities/Player.h \
 src/Game/Menu/../../Entities/../Effects/DiscardCardEffect.h \
 src/Game/Menu/../../Entities/../Effects/Effect.h \
 src/Game/Menu/../../Entities/../Effects/../Entities/Player.h \
 src/Game/Menu/../GameManager.h src/Game/Menu/../AssetLoader.h \
 src/Game/Menu/../../Cards/Card.h src/Game/Menu/../Board.h \
 src/Game/Menu/../../Entities/AIPlayer.h \
 src/Game/Menu/../../Entities/Player.h src/Game/Menu/../GameManager.h \
 src/Game/Menu/../GameSaver.h | objs
	$(CC) $(CFLAGS) -c $< -o $@

#objs/MenuItem.o: src/Game/Menu/MenuItem.h | objs
#	$(CC) $(CFLAGS) -c $< -o $@

objs: 
	mkdir objs
	
clean:
	rm -rf $(PROGRAM) objs/ doc/ 2>/dev/null

