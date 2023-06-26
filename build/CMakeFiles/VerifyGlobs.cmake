# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.22
cmake_policy(SET CMP0009 NEW)

# CLIENT_SRC at CMakeLists.txt:28 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/home/regman/taller/left4Dead/client/*")
set(OLD_GLOB
  "/home/regman/taller/left4Dead/client/actions/action_client.h"
  "/home/regman/taller/left4Dead/client/actions/action_create.cpp"
  "/home/regman/taller/left4Dead/client/actions/action_create.h"
  "/home/regman/taller/left4Dead/client/actions/action_end_move.cpp"
  "/home/regman/taller/left4Dead/client/actions/action_end_move.h"
  "/home/regman/taller/left4Dead/client/actions/action_end_shoot.cpp"
  "/home/regman/taller/left4Dead/client/actions/action_end_shoot.h"
  "/home/regman/taller/left4Dead/client/actions/action_join.cpp"
  "/home/regman/taller/left4Dead/client/actions/action_join.h"
  "/home/regman/taller/left4Dead/client/actions/action_recharge.cpp"
  "/home/regman/taller/left4Dead/client/actions/action_recharge.h"
  "/home/regman/taller/left4Dead/client/actions/action_render.cpp"
  "/home/regman/taller/left4Dead/client/actions/action_render.h"
  "/home/regman/taller/left4Dead/client/actions/action_revive.cpp"
  "/home/regman/taller/left4Dead/client/actions/action_revive.h"
  "/home/regman/taller/left4Dead/client/actions/action_start_game.cpp"
  "/home/regman/taller/left4Dead/client/actions/action_start_game.h"
  "/home/regman/taller/left4Dead/client/actions/action_start_move.cpp"
  "/home/regman/taller/left4Dead/client/actions/action_start_move.h"
  "/home/regman/taller/left4Dead/client/actions/action_start_shoot.cpp"
  "/home/regman/taller/left4Dead/client/actions/action_start_shoot.h"
  "/home/regman/taller/left4Dead/client/client.cpp"
  "/home/regman/taller/left4Dead/client/client.h"
  "/home/regman/taller/left4Dead/client/client_connection/client_protocol.cpp"
  "/home/regman/taller/left4Dead/client/client_connection/client_protocol.h"
  "/home/regman/taller/left4Dead/client/client_connection/client_receiver.cpp"
  "/home/regman/taller/left4Dead/client/client_connection/client_receiver.h"
  "/home/regman/taller/left4Dead/client/client_connection/client_sender.cpp"
  "/home/regman/taller/left4Dead/client/client_connection/client_sender.h"
  "/home/regman/taller/left4Dead/client/client_documentation.md"
  "/home/regman/taller/left4Dead/client/client_event_manager.cc"
  "/home/regman/taller/left4Dead/client/client_event_manager.h"
  "/home/regman/taller/left4Dead/client/client_main.cpp"
  "/home/regman/taller/left4Dead/client/configuration/configuration.yaml"
  "/home/regman/taller/left4Dead/client/configuration/renderer_config.cpp"
  "/home/regman/taller/left4Dead/client/configuration/renderer_config.h"
  "/home/regman/taller/left4Dead/client/configuration/rutas.txt"
  "/home/regman/taller/left4Dead/client/correcciones.md"
  "/home/regman/taller/left4Dead/client/menuQT/create.cpp"
  "/home/regman/taller/left4Dead/client/menuQT/create.h"
  "/home/regman/taller/left4Dead/client/menuQT/create.ui"
  "/home/regman/taller/left4Dead/client/menuQT/hiloMensajes.cpp"
  "/home/regman/taller/left4Dead/client/menuQT/hiloMensajes.h"
  "/home/regman/taller/left4Dead/client/menuQT/join.cpp"
  "/home/regman/taller/left4Dead/client/menuQT/join.h"
  "/home/regman/taller/left4Dead/client/menuQT/join.ui"
  "/home/regman/taller/left4Dead/client/menuQT/mainwindow.cpp"
  "/home/regman/taller/left4Dead/client/menuQT/mainwindow.h"
  "/home/regman/taller/left4Dead/client/menuQT/mainwindow.ui"
  "/home/regman/taller/left4Dead/client/render/client_render.cpp"
  "/home/regman/taller/left4Dead/client/render/client_render.h"
  "/home/regman/taller/left4Dead/client/render/game/client_bullets.cpp"
  "/home/regman/taller/left4Dead/client/render/game/client_bullets.h"
  "/home/regman/taller/left4Dead/client/render/game/client_game.cpp"
  "/home/regman/taller/left4Dead/client/render/game/client_game.h"
  "/home/regman/taller/left4Dead/client/render/game/client_game_state.h"
  "/home/regman/taller/left4Dead/client/render/game/client_game_time.cpp"
  "/home/regman/taller/left4Dead/client/render/game/client_game_time.h"
  "/home/regman/taller/left4Dead/client/render/game/client_infected.cpp"
  "/home/regman/taller/left4Dead/client/render/game/client_infected.h"
  "/home/regman/taller/left4Dead/client/render/game/client_lifeBar.cpp"
  "/home/regman/taller/left4Dead/client/render/game/client_lifeBar.h"
  "/home/regman/taller/left4Dead/client/render/game/client_player.cpp"
  "/home/regman/taller/left4Dead/client/render/game/client_player.h"
  "/home/regman/taller/left4Dead/client/render/resources/Jumper/Attack_1.png"
  "/home/regman/taller/left4Dead/client/render/resources/Jumper/Attack_2.png"
  "/home/regman/taller/left4Dead/client/render/resources/Jumper/Attack_3.png"
  "/home/regman/taller/left4Dead/client/render/resources/Jumper/Dead.png"
  "/home/regman/taller/left4Dead/client/render/resources/Jumper/Eating.png"
  "/home/regman/taller/left4Dead/client/render/resources/Jumper/Hurt.png"
  "/home/regman/taller/left4Dead/client/render/resources/Jumper/Idle.png"
  "/home/regman/taller/left4Dead/client/render/resources/Jumper/Jump.png"
  "/home/regman/taller/left4Dead/client/render/resources/Jumper/Run.png"
  "/home/regman/taller/left4Dead/client/render/resources/Jumper/Walk.png"
  "/home/regman/taller/left4Dead/client/render/resources/Soldier_1/Attack.png"
  "/home/regman/taller/left4Dead/client/render/resources/Soldier_1/Dead.png"
  "/home/regman/taller/left4Dead/client/render/resources/Soldier_1/Explosion.png"
  "/home/regman/taller/left4Dead/client/render/resources/Soldier_1/Grenade.png"
  "/home/regman/taller/left4Dead/client/render/resources/Soldier_1/Hurt.png"
  "/home/regman/taller/left4Dead/client/render/resources/Soldier_1/Idle.png"
  "/home/regman/taller/left4Dead/client/render/resources/Soldier_1/Recharge.png"
  "/home/regman/taller/left4Dead/client/render/resources/Soldier_1/Run.png"
  "/home/regman/taller/left4Dead/client/render/resources/Soldier_1/Shot_1.png"
  "/home/regman/taller/left4Dead/client/render/resources/Soldier_1/Shot_2.png"
  "/home/regman/taller/left4Dead/client/render/resources/Soldier_1/Walk.png"
  "/home/regman/taller/left4Dead/client/render/resources/Soldier_2/Attack.png"
  "/home/regman/taller/left4Dead/client/render/resources/Soldier_2/Dead.png"
  "/home/regman/taller/left4Dead/client/render/resources/Soldier_2/Grenade.png"
  "/home/regman/taller/left4Dead/client/render/resources/Soldier_2/Hurt.png"
  "/home/regman/taller/left4Dead/client/render/resources/Soldier_2/Idle.png"
  "/home/regman/taller/left4Dead/client/render/resources/Soldier_2/Recharge.png"
  "/home/regman/taller/left4Dead/client/render/resources/Soldier_2/Run.png"
  "/home/regman/taller/left4Dead/client/render/resources/Soldier_2/Shot_1.png"
  "/home/regman/taller/left4Dead/client/render/resources/Soldier_2/Shot_2.png"
  "/home/regman/taller/left4Dead/client/render/resources/Soldier_2/Walk.png"
  "/home/regman/taller/left4Dead/client/render/resources/Soldier_3/Attack.png"
  "/home/regman/taller/left4Dead/client/render/resources/Soldier_3/Dead.png"
  "/home/regman/taller/left4Dead/client/render/resources/Soldier_3/Grenade.png"
  "/home/regman/taller/left4Dead/client/render/resources/Soldier_3/Hurt.png"
  "/home/regman/taller/left4Dead/client/render/resources/Soldier_3/Idle.png"
  "/home/regman/taller/left4Dead/client/render/resources/Soldier_3/Recharge.png"
  "/home/regman/taller/left4Dead/client/render/resources/Soldier_3/Run.png"
  "/home/regman/taller/left4Dead/client/render/resources/Soldier_3/Shot_1.png"
  "/home/regman/taller/left4Dead/client/render/resources/Soldier_3/Shot_2.png"
  "/home/regman/taller/left4Dead/client/render/resources/Soldier_3/Smoke.png"
  "/home/regman/taller/left4Dead/client/render/resources/Soldier_3/Walk.png"
  "/home/regman/taller/left4Dead/client/render/resources/Spear/Attack_1.png"
  "/home/regman/taller/left4Dead/client/render/resources/Spear/Attack_2.png"
  "/home/regman/taller/left4Dead/client/render/resources/Spear/Dead.png"
  "/home/regman/taller/left4Dead/client/render/resources/Spear/Fall.png"
  "/home/regman/taller/left4Dead/client/render/resources/Spear/Hurt.png"
  "/home/regman/taller/left4Dead/client/render/resources/Spear/Idle.png"
  "/home/regman/taller/left4Dead/client/render/resources/Spear/Protect.png"
  "/home/regman/taller/left4Dead/client/render/resources/Spear/Run+attack.png"
  "/home/regman/taller/left4Dead/client/render/resources/Spear/Run.png"
  "/home/regman/taller/left4Dead/client/render/resources/Spear/Walk.png"
  "/home/regman/taller/left4Dead/client/render/resources/Venom/Attack1.png"
  "/home/regman/taller/left4Dead/client/render/resources/Venom/Attack1a.png"
  "/home/regman/taller/left4Dead/client/render/resources/Venom/Attack2.png"
  "/home/regman/taller/left4Dead/client/render/resources/Venom/Dead.png"
  "/home/regman/taller/left4Dead/client/render/resources/Venom/Hurt.png"
  "/home/regman/taller/left4Dead/client/render/resources/Venom/Idle.png"
  "/home/regman/taller/left4Dead/client/render/resources/Venom/Jump.png"
  "/home/regman/taller/left4Dead/client/render/resources/Venom/Run.png"
  "/home/regman/taller/left4Dead/client/render/resources/Venom/Walk.png"
  "/home/regman/taller/left4Dead/client/render/resources/Witch/Attack_1.png"
  "/home/regman/taller/left4Dead/client/render/resources/Witch/Attack_2.png"
  "/home/regman/taller/left4Dead/client/render/resources/Witch/Attack_3.png"
  "/home/regman/taller/left4Dead/client/render/resources/Witch/Dead.png"
  "/home/regman/taller/left4Dead/client/render/resources/Witch/Hurt.png"
  "/home/regman/taller/left4Dead/client/render/resources/Witch/Idle.png"
  "/home/regman/taller/left4Dead/client/render/resources/Witch/Jump.png"
  "/home/regman/taller/left4Dead/client/render/resources/Witch/Run.png"
  "/home/regman/taller/left4Dead/client/render/resources/Witch/Scream.png"
  "/home/regman/taller/left4Dead/client/render/resources/Witch/Walk.png"
  "/home/regman/taller/left4Dead/client/render/resources/Zombie/Attack_1.png"
  "/home/regman/taller/left4Dead/client/render/resources/Zombie/Attack_2.png"
  "/home/regman/taller/left4Dead/client/render/resources/Zombie/Attack_3.png"
  "/home/regman/taller/left4Dead/client/render/resources/Zombie/Bite.png"
  "/home/regman/taller/left4Dead/client/render/resources/Zombie/Dead.png"
  "/home/regman/taller/left4Dead/client/render/resources/Zombie/Hurt.png"
  "/home/regman/taller/left4Dead/client/render/resources/Zombie/Idle.png"
  "/home/regman/taller/left4Dead/client/render/resources/Zombie/Jump.png"
  "/home/regman/taller/left4Dead/client/render/resources/Zombie/Run.png"
  "/home/regman/taller/left4Dead/client/render/resources/Zombie/Walk.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War1/Bright/War.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War1/Bright/crater1.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War1/Bright/crater2.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War1/Bright/crater3.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War1/Bright/fence.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War1/Bright/house3.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War1/Bright/houses1.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War1/Bright/houses2.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War1/Bright/road.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War1/Bright/ruins.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War1/Bright/sky.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War1/Bright/sun.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War1/Pale/War.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War1/Pale/crater1.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War1/Pale/crater2.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War1/Pale/crater3.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War1/Pale/fence.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War1/Pale/house3.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War1/Pale/houses1.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War1/Pale/houses2.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War1/Pale/road.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War1/Pale/ruins.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War1/Pale/sky.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War1/Pale/sun.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War2/Bright/War2.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War2/Bright/cracks1.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War2/Bright/cracks2.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War2/Bright/houses1.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War2/Bright/houses2.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War2/Bright/houses3.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War2/Bright/houses4.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War2/Bright/road.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War2/Bright/sky.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War2/Bright/wall.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War2/Pale/War2.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War2/Pale/cracks1.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War2/Pale/cracks2.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War2/Pale/houses1.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War2/Pale/houses2.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War2/Pale/houses3.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War2/Pale/houses4.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War2/Pale/road.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War2/Pale/sky.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War2/Pale/wall.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War3/Bright/War3.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War3/Bright/bricks1.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War3/Bright/bricks2.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War3/Bright/bricks3.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War3/Bright/fence.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War3/Bright/house&fountain.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War3/Bright/houses2.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War3/Bright/houses3.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War3/Bright/road.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War3/Bright/sky.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War3/Bright/sky_sun.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War3/Bright/trees.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War3/Pale/War3.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War3/Pale/bricks1.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War3/Pale/bricks2.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War3/Pale/bricks3.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War3/Pale/fence.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War3/Pale/house&fountain.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War3/Pale/houses2.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War3/Pale/houses3.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War3/Pale/road.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War3/Pale/sky.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War3/Pale/sky_sun.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War3/Pale/trees.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War4/0.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War4/00.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War4/000.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War4/0000.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War4/Bright/Moon_asset.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War4/Bright/War4.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War4/Bright/houses1.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War4/Bright/houses2.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War4/Bright/houses3.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War4/Bright/houses4.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War4/Bright/moon.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War4/Bright/road.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War4/Bright/sky.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War4/Bright/wall.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War4/Bright/wheels.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War4/Bright/wheels2.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War4/Bright/wheels3.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War4/Pale/Moon_asset.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War4/Pale/War4.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War4/Pale/houses1.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War4/Pale/houses2.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War4/Pale/houses3.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War4/Pale/houses4.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War4/Pale/moon.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War4/Pale/road.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War4/Pale/sky.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War4/Pale/wall.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War4/Pale/wheels.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War4/Pale/wheels2.png"
  "/home/regman/taller/left4Dead/client/render/resources/backgrounds/War4/Pale/wheels3.png"
  "/home/regman/taller/left4Dead/client/render/resources/fondoqt2.jpeg"
  "/home/regman/taller/left4Dead/client/render/resources/fondoqt3.jpeg"
  "/home/regman/taller/left4Dead/client/render/resources/icono_sonido.png"
  "/home/regman/taller/left4Dead/client/render/resources/sounds/ametralladora.wav"
  "/home/regman/taller/left4Dead/client/render/resources/sounds/bruja1.wav"
  "/home/regman/taller/left4Dead/client/render/resources/sounds/bruja2.wav"
  "/home/regman/taller/left4Dead/client/render/resources/sounds/caminar1.wav"
  "/home/regman/taller/left4Dead/client/render/resources/sounds/caminar2.wav"
  "/home/regman/taller/left4Dead/client/render/resources/sounds/cargar_arma1.wav"
  "/home/regman/taller/left4Dead/client/render/resources/sounds/cargar_arma1_2.wav"
  "/home/regman/taller/left4Dead/client/render/resources/sounds/cargar_arma2.wav"
  "/home/regman/taller/left4Dead/client/render/resources/sounds/dead.wav"
  "/home/regman/taller/left4Dead/client/render/resources/sounds/disparo1.wav"
  "/home/regman/taller/left4Dead/client/render/resources/sounds/disparo3.wav"
  "/home/regman/taller/left4Dead/client/render/resources/sounds/disparo4.wav"
  "/home/regman/taller/left4Dead/client/render/resources/sounds/disparo5.wav"
  "/home/regman/taller/left4Dead/client/render/resources/sounds/disparo6.wav"
  "/home/regman/taller/left4Dead/client/render/resources/sounds/explosion.wav"
  "/home/regman/taller/left4Dead/client/render/resources/sounds/fondo1.mp3"
  "/home/regman/taller/left4Dead/client/render/resources/sounds/fondo2.mp3"
  "/home/regman/taller/left4Dead/client/render/resources/sounds/fondo3.mp3"
  "/home/regman/taller/left4Dead/client/render/resources/sounds/granada.wav"
  "/home/regman/taller/left4Dead/client/render/resources/sounds/grito_de_ayuda.wav"
  "/home/regman/taller/left4Dead/client/render/resources/sounds/trotar.wav"
  "/home/regman/taller/left4Dead/client/render/resources/sounds/varios_disparos.wav"
  "/home/regman/taller/left4Dead/client/render/resources/sounds/voz_reloading.wav"
  "/home/regman/taller/left4Dead/client/render/resources/sounds/zombi1.wav"
  "/home/regman/taller/left4Dead/client/render/resources/sounds/zombie_come.wav"
  "/home/regman/taller/left4Dead/client/render/resources/sounds/zombies.wav"
  "/home/regman/taller/left4Dead/client/render/resources/vida/barrasvida.png"
  "/home/regman/taller/left4Dead/client/render/sound/client_sound.cpp"
  "/home/regman/taller/left4Dead/client/render/sound/client_sound.h"
  "/home/regman/taller/left4Dead/client/render/sound/client_sound_manager.cpp"
  "/home/regman/taller/left4Dead/client/render/sound/client_sound_manager.h"
  "/home/regman/taller/left4Dead/client/render/texture/client_texture.cpp"
  "/home/regman/taller/left4Dead/client/render/texture/client_texture.h"
  "/home/regman/taller/left4Dead/client/render/texture/client_texture_manager.cpp"
  "/home/regman/taller/left4Dead/client/render/texture/client_texture_manager.h"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/home/regman/taller/left4Dead/build/CMakeFiles/cmake.verify_globs")
endif()

# COMMON_SRC at CMakeLists.txt:27 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/home/regman/taller/left4Dead/dipa_classes/*")
set(OLD_GLOB
  "/home/regman/taller/left4Dead/dipa_classes/liberror.cpp"
  "/home/regman/taller/left4Dead/dipa_classes/liberror.h"
  "/home/regman/taller/left4Dead/dipa_classes/queue.h"
  "/home/regman/taller/left4Dead/dipa_classes/resolver.cpp"
  "/home/regman/taller/left4Dead/dipa_classes/resolver.h"
  "/home/regman/taller/left4Dead/dipa_classes/resolvererror.cpp"
  "/home/regman/taller/left4Dead/dipa_classes/resolvererror.h"
  "/home/regman/taller/left4Dead/dipa_classes/socket.cpp"
  "/home/regman/taller/left4Dead/dipa_classes/socket.h"
  "/home/regman/taller/left4Dead/dipa_classes/thread.h"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/home/regman/taller/left4Dead/build/CMakeFiles/cmake.verify_globs")
endif()

# SERVER_SRC at CMakeLists.txt:29 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/home/regman/taller/left4Dead/server_root/*")
set(OLD_GLOB
  "/home/regman/taller/left4Dead/server_root/client_connection/client_connection.cpp"
  "/home/regman/taller/left4Dead/server_root/client_connection/client_connection.h"
  "/home/regman/taller/left4Dead/server_root/client_connection/client_receiver.cpp"
  "/home/regman/taller/left4Dead/server_root/client_connection/client_receiver.h"
  "/home/regman/taller/left4Dead/server_root/client_connection/client_sender.cpp"
  "/home/regman/taller/left4Dead/server_root/client_connection/client_sender.h"
  "/home/regman/taller/left4Dead/server_root/client_connection/server_protocol.cpp"
  "/home/regman/taller/left4Dead/server_root/client_connection/server_protocol.h"
  "/home/regman/taller/left4Dead/server_root/entities/attack.cpp"
  "/home/regman/taller/left4Dead/server_root/entities/attack.h"
  "/home/regman/taller/left4Dead/server_root/entities/collision_detector.cpp"
  "/home/regman/taller/left4Dead/server_root/entities/collision_detector.h"
  "/home/regman/taller/left4Dead/server_root/entities/entity.cpp"
  "/home/regman/taller/left4Dead/server_root/entities/entity.h"
  "/home/regman/taller/left4Dead/server_root/entities/player.cpp"
  "/home/regman/taller/left4Dead/server_root/entities/player.h"
  "/home/regman/taller/left4Dead/server_root/entities/weapon.cpp"
  "/home/regman/taller/left4Dead/server_root/entities/weapon.h"
  "/home/regman/taller/left4Dead/server_root/entities/zombies/infected.cpp"
  "/home/regman/taller/left4Dead/server_root/entities/zombies/infected.h"
  "/home/regman/taller/left4Dead/server_root/entities/zombies/jumper.cpp"
  "/home/regman/taller/left4Dead/server_root/entities/zombies/jumper.h"
  "/home/regman/taller/left4Dead/server_root/entities/zombies/spear.cpp"
  "/home/regman/taller/left4Dead/server_root/entities/zombies/spear.h"
  "/home/regman/taller/left4Dead/server_root/entities/zombies/venom.cpp"
  "/home/regman/taller/left4Dead/server_root/entities/zombies/venom.h"
  "/home/regman/taller/left4Dead/server_root/entities/zombies/witch.cpp"
  "/home/regman/taller/left4Dead/server_root/entities/zombies/witch.h"
  "/home/regman/taller/left4Dead/server_root/entities/zombies/zombie.cpp"
  "/home/regman/taller/left4Dead/server_root/entities/zombies/zombie.h"
  "/home/regman/taller/left4Dead/server_root/entities/zombies/zombie_spawner.cpp"
  "/home/regman/taller/left4Dead/server_root/entities/zombies/zombie_spawner.h"
  "/home/regman/taller/left4Dead/server_root/game/action.cpp"
  "/home/regman/taller/left4Dead/server_root/game/action.h"
  "/home/regman/taller/left4Dead/server_root/game/configuration/configuration.yaml"
  "/home/regman/taller/left4Dead/server_root/game/configuration/game_config.cpp"
  "/home/regman/taller/left4Dead/server_root/game/configuration/game_config.h"
  "/home/regman/taller/left4Dead/server_root/game/game.cpp"
  "/home/regman/taller/left4Dead/server_root/game/game.h"
  "/home/regman/taller/left4Dead/server_root/game/games_manager.cpp"
  "/home/regman/taller/left4Dead/server_root/game/games_manager.h"
  "/home/regman/taller/left4Dead/server_root/game/server_message.cpp"
  "/home/regman/taller/left4Dead/server_root/game/server_message.h"
  "/home/regman/taller/left4Dead/server_root/server/acceptor.cpp"
  "/home/regman/taller/left4Dead/server_root/server/acceptor.h"
  "/home/regman/taller/left4Dead/server_root/server/server.cpp"
  "/home/regman/taller/left4Dead/server_root/server/server.h"
  "/home/regman/taller/left4Dead/server_root/server/server_main.cpp"
  "/home/regman/taller/left4Dead/server_root/server_documentation.md"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/home/regman/taller/left4Dead/build/CMakeFiles/cmake.verify_globs")
endif()

# CLIENT_TESTS_SRC at tests/CMakeLists.txt:18 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/home/regman/taller/left4Dead/tests/client_tests/*.cpp")
set(OLD_GLOB
  "/home/regman/taller/left4Dead/tests/client_tests/client_protocol_tests.cpp"
  "/home/regman/taller/left4Dead/tests/client_tests/main_client_test.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/home/regman/taller/left4Dead/build/CMakeFiles/cmake.verify_globs")
endif()

# SERVER_TESTS_SRC at tests/CMakeLists.txt:17 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/home/regman/taller/left4Dead/tests/server_tests/*.cpp")
set(OLD_GLOB
  "/home/regman/taller/left4Dead/tests/server_tests/collisions_tests.cpp"
  "/home/regman/taller/left4Dead/tests/server_tests/entity_tests.cpp"
  "/home/regman/taller/left4Dead/tests/server_tests/game_config_tests.cpp"
  "/home/regman/taller/left4Dead/tests/server_tests/game_tests.cpp"
  "/home/regman/taller/left4Dead/tests/server_tests/games_manager_tests.cpp"
  "/home/regman/taller/left4Dead/tests/server_tests/main_tests.cpp"
  "/home/regman/taller/left4Dead/tests/server_tests/server_protocol_tests.cpp"
  "/home/regman/taller/left4Dead/tests/server_tests/zombie_spawner_tests.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/home/regman/taller/left4Dead/build/CMakeFiles/cmake.verify_globs")
endif()
