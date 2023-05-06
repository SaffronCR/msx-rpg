;Compiles the player, the music and sfxs, using RASM.
;No ORG needed.

    ;Songs.
	include "dungeon_playerconfig.asm" ;Optional.
	include "battle_playerconfig.asm" ;Optional.

    include "dungeon.asm"
	include "battle.asm"

    ;Sound effects.
    include "SoundEffects.asm"
    include "SoundEffects_playerconfig.asm"  ;Optional.

    ;Hardware config.
    PLY_AKG_HARDWARE_MSX = 1

    ;Comment/delete this line if not using sound effects.
    PLY_AKG_MANAGE_SOUND_EFFECTS = 1

    ;This is the player.
    include "PlayerAkg.asm"
