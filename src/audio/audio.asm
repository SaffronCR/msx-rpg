;;
;; sr_init_dungeon_song function
;; input: nothing
;; output: nothing
;;
_sr_init_dungeon_song::
	ld hl,#DUNGEON_START
    xor a
    call PLY_AKG_INIT
	ret

;;
;; sr_init_battle_song function
;; input: nothing
;; output: nothing
;;
_sr_init_battle_song::
	ld hl,#BATTLE_START
    xor a
    call PLY_AKG_INIT
	ret

;;
;; sr_play_song function
;; input: nothing
;; output: nothing
;;
_sr_play_song::
    ;Play one frame of the song.
    call PLY_AKG_PLAY
	ret

;;
;; sr_stop_song function
;; input: nothing
;; output: nothing
;;
_sr_stop_song::
;stop the player
    call PLY_AKG_STOP
	ret

.include "At2Files.asm"
