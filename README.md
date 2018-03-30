# Bomberman 3D 2018 ;)

Some classic Bomberman 3D spinoff recreated in UnrealEngine 4

### Already implemented features

- Map generator
- Player movement (analog way like in 3d games)
- Destructible walls
- Bombs placing, configurable blast radius in 4 directions (blast kills player, destroys some walls and pickups)
- Pickups (at this moment only bombs max amount boost)

### Considerations

Movmement. Current implementation is anaglog, seems more fun to play this way in 3d game but to consider is option of reimplementation of MovementComponent to fit classic movement over grid

### Todo and next steps

- Add few more pickups
- Begin porting into multiplayer, replace calls by RPC and add replication
- Add begin and end screen (start single game, start multiplayer session, summary page)
- Add HUD
- Add AI with simple pathfinding

### Credits

Solution was developed by Tomasz Kolaj and is licensed under Apache License Version 2.0.
Please reports bugs at https://github.com/migotom/ue4-bomberman/issues and major security issues directly to me at tomasz246@gmail.com.