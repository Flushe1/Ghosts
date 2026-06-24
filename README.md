[README.md](https://github.com/user-attachments/files/29288830/README.md)
# Ghosts

Ghosts is an ultra-realistic tactical FPS prototype built in Unreal Engine. The goal is grounded gunplay, deliberate movement, lethal damage, squad-oriented encounters, and readable tactical decision-making.

## Current Base

- Engine: Unreal Engine 5.7
- Main module: `Ghosts`
- Default map: `/Game/FirstPerson/Lvl_FirstPerson`
- Default game mode: `/Game/FirstPerson/Blueprints/BP_FirstPersonGameMode`
- Input: Enhanced Input
- UI: UMG
- AI foundation: StateTree and Gameplay StateTree plugins
- Operator foundation: health, stamina, and suppression via `UGhostsOperatorComponent`
- Firearm foundation: magazine ammo, reserve ammo, reloads, dry fire, and fire modes via `UGhostsFirearmComponent`

## Tactical Direction

1. Build a grounded operator controller: walk, sprint, crouch, lean, stance, stamina, and suppression.
2. Establish realistic weapon handling: ADS, recoil, sway, reload states, fire modes, magazines, and ballistics-friendly traces.
3. Create lethal damage rules with clear hit reactions and fast time-to-kill.
4. Prototype AI with patrol, alert, investigate, suppress, flank, and breach behavior.
5. Replace template content with Ghosts-specific weapons, UI, audio, animation, and tactical maps.

## First Gameplay Milestone

The first milestone should be a small tactical slice:

- Player can move as an operator with stamina limits.
- Player can fire a primary weapon with recoil and ADS.
- Targets react to hits and suppression.
- One small encounter supports cover, flank routes, and line-of-sight decisions.
- The level can be completed through careful movement and accurate shooting.

## Project Notes

Keep template assets only while they are useful for prototyping. Shared gameplay systems should live under `Source/Ghosts`, while template variants remain isolated under the existing `Variant_*` folders.
