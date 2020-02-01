;Compiles the player, the music and sfxs, using RASM.
;No ORG needed.

    ;Songs.
    include "song.asm" 
    include "song_playerconfig.asm" ;Optional.
 
    ;Sound effects.
    ;include "SoundEffects.asm" 
    ;include "SoundEffects_playerconfig.asm"  ;Optional.

    ;Hardware config.
    PLY_AKG_HARDWARE_MSX = 1

    ;Comment/delete this line if not using sound effects.
    PLY_AKG_MANAGE_SOUND_EFFECTS = 1

    ;This is the player.
    include "PlayerAkg.asm"
