;;
;; sf_init_menu_song function
;; input: nothing
;; output: nothing
;;
_sf_init_menu_song::
	;ld hl,#MENU_START
    xor a
    call PLY_AKG_INIT
	ret

;;
;; sf_init_intro_song function
;; input: nothing
;; output: nothing
;;
_sf_init_intro_song::
	;ld hl,#INTRO_START
    xor a
    call PLY_AKG_INIT
	ret

;;
;; sf_init_dungeon_song function
;; input: nothing
;; output: nothing
;;
_sf_init_dungeon_song::
	;ld hl,#DUNGEON_START
    xor a
    call PLY_AKG_INIT
	ret

;;
;; sf_init_song function
;; input: nothing
;; output: nothing
;;
_sf_init_battle_song::
	ld hl,#BATTLE_START
    xor a
    call PLY_AKG_INIT
	ret

;;
;; sf_play_song function
;; input: nothing
;; output: nothing
;;
_sf_play_song::
    ;Play one frame of the song.
    call PLY_AKG_PLAY
	ret

.include "At2Files.asm"
