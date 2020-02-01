;;
;; sf_init_song function
;; input: nothing
;; output: nothing
;;
_sf_init_song::
	ld hl,#CASTLE_START
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
