DUNGEON_START:
_DUNGEON_START::
PLY_AKG_OPCODE_ADD_HL_BC_MSB: .db 65
PLY_AKG_FULL_INIT_CODE:
PLY_AKG_OFFSET1B:
PLY_AKG_USE_HOOKS:
PLY_AKG_STOP_SOUNDS: .db 84
PLY_AKG_BITFORSOUND:
PLY_AKG_OFFSET2B:
PLY_AKG_SOUNDEFFECTDATA_OFFSETINVERTEDVOLUME: .db 50
PLY_AKG_SOUNDEFFECTDATA_OFFSETCURRENTSTEP: .db 48
PLY_AKG_BITFORNOISE = .+1
PLY_AKG_SOUNDEFFECTDATA_OFFSETSPEED: .dw DUNGEON_ARPEGGIOTABLE
    .dw DUNGEON_ARPEGGIOTABLE
PLY_AKG_OPCODE_ADD_HL_BC_LSB = .+1
PLY_AKG_CHANNEL_SOUNDEFFECTDATASIZE: .dw DUNGEON_INSTRUMENTTABLE
    .dw DUNGEON_EFFECTBLOCKTABLE
    .dw DUNGEON_SUBSONG0_START
DUNGEON_ARPEGGIOTABLE:
DUNGEON_PITCHTABLE: .dw DUNGEON_PITCH1
DUNGEON_PITCH1: .db 2
    .db 0
    .db 0
DUNGEON_PITCH1_GOTONEXTFORLINE0: .dw DUNGEON_PITCH1_GOTONEXTFORLINE0+2
    .db 0
    .db 0
DUNGEON_PITCH1_GOTONEXTFORLINE1: .dw DUNGEON_PITCH1_GOTONEXTFORLINE1+2
    .db 0
    .db 0
DUNGEON_PITCH1_GOTONEXTFORLINE2: .dw DUNGEON_PITCH1_GOTONEXTFORLINE2+2
    .db 255
    .db 255
DUNGEON_PITCH1_GOTONEXTFORLINE3: .dw DUNGEON_PITCH1_GOTONEXTFORLINE3+2
    .db 252
    .db 255
DUNGEON_PITCH1_GOTONEXTFORLINE4:
PLY_AKG_OPCODE_INC_HL: .dw DUNGEON_PITCH1_GOTONEXTFORLINE4+2
    .db 2
    .db 0
    .dw DUNGEON_PITCH1_GOTONEXTFORLINE1+2
DUNGEON_INSTRUMENTTABLE: .dw DUNGEON_EMPTYINSTRUMENT
PLY_AKG_OPCODE_DEC_HL: .dw DUNGEON_INSTRUMENT1
    .dw DUNGEON_INSTRUMENT2
DUNGEON_EMPTYINSTRUMENT: .db 0
DUNGEON_EMPTYINSTRUMENT_LOOP: .db 0
    .db 6
DUNGEON_INSTRUMENT1: .db 3
    .db 249
    .db 233
    .db 225
    .db 217
PLY_AKG_OPCODE_SCF: .db 209
    .db 201
    .db 193
    .db 185
    .db 177
    .db 169
    .db 161
    .db 153
    .db 145
    .db 137
    .db 6
DUNGEON_INSTRUMENT2:
PLY_AKG_OPCODE_SBC_HL_BC_LSB: .db 1
DUNGEON_INSTRUMENT2_LOOP: .db 34
    .db 131
    .db 7
    .dw DUNGEON_INSTRUMENT2_LOOP
DUNGEON_EFFECTBLOCKTABLE: .dw DUNGEON_EFFECTBLOCK_P3P2P10P0
    .dw DUNGEON_EFFECTBLOCK_P5P2P10P0
DUNGEON_EFFECTBLOCK_P3P2P10P0: .db 3
    .db 2
    .db 10
    .db 0
DUNGEON_EFFECTBLOCK_P5P2P10P0: .db 5
    .db 2
    .db 10
    .db 0
DUNGEON_SUBSONG0_START: .db 1
    .db 0
    .db 1
    .db 0
    .db 3
    .db 8
    .db 9
DUNGEON_SUBSONG0_LINKER:
DUNGEON_SUBSONG0_LINKER_LOOP: .dw DUNGEON_SUBSONG0_TRACK0
    .dw DUNGEON_SUBSONG0_TRACK2
    .dw DUNGEON_SUBSONG0_TRACK1
    .dw DUNGEON_SUBSONG0_LINKERBLOCK0
    .dw DUNGEON_SUBSONG0_TRACK4
    .dw DUNGEON_SUBSONG0_TRACK4
    .dw DUNGEON_SUBSONG0_TRACK4
    .dw DUNGEON_SUBSONG0_LINKERBLOCK1
    .dw DUNGEON_SUBSONG0_TRACK3
    .dw DUNGEON_SUBSONG0_TRACK4
    .dw DUNGEON_SUBSONG0_TRACK5
    .dw DUNGEON_SUBSONG0_LINKERBLOCK0
    .dw DUNGEON_SUBSONG0_TRACK4
    .dw DUNGEON_SUBSONG0_TRACK4
    .dw DUNGEON_SUBSONG0_TRACK4
    .dw DUNGEON_SUBSONG0_LINKERBLOCK1
    .db 0
    .db 0
    .dw DUNGEON_SUBSONG0_LINKER
DUNGEON_SUBSONG0_LINKERBLOCK0: .db 32
    .db 0
    .db 0
    .db 0
    .dw DUNGEON_SUBSONG0_SPEEDTRACK0
    .dw DUNGEON_SUBSONG0_EVENTTRACK0
DUNGEON_SUBSONG0_LINKERBLOCK1: .db 16
    .db 0
    .db 0
    .db 0
    .dw DUNGEON_SUBSONG0_SPEEDTRACK0
    .dw DUNGEON_SUBSONG0_EVENTTRACK0
DUNGEON_SUBSONG0_TRACK0: .db 242
    .db 1
    .db 0
    .db 61
    .db 6
    .db 51
    .db 61
    .db 6
    .db 41
    .db 61
    .db 6
    .db 53
    .db 61
    .db 127
DUNGEON_SUBSONG0_TRACK1: .db 190
    .db 240
    .db 1
    .db 1
    .db 61
    .db 6
    .db 46
    .db 61
    .db 6
    .db 50
    .db 61
    .db 6
    .db 43
    .db 61
    .db 127
DUNGEON_SUBSONG0_TRACK2: .db 142
    .db 2
    .db 61
    .db 127
DUNGEON_SUBSONG0_TRACK3: .db 242
    .db 1
    .db 0
    .db 61
    .db 7
    .db 44
    .db 61
PLY_AKG_OPCODE_OR_A: .db 8
    .db 43
    .db 61
    .db 7
    .db 41
    .db 61
    .db 127
DUNGEON_SUBSONG0_TRACK4: .db 61
    .db 127
DUNGEON_SUBSONG0_TRACK5: .db 124
    .db 1
    .db 190
    .db 179
    .db 1
    .db 61
PLY_AKG_OPCODE_ADD_A_IMMEDIATE: .db 7
    .db 55
    .db 61
    .db 7
    .db 46
    .db 61
    .db 127
DUNGEON_SUBSONG0_SPEEDTRACK0: .db 255
DUNGEON_SUBSONG0_EVENTTRACK0: .db 255
BATTLE_START:
_BATTLE_START:: .db 65
    .db 84
    .db 50
    .db 48
    .dw BATTLE_ARPEGGIOTABLE
PLY_AKG_OPCODE_SUB_IMMEDIATE = .+1
    .dw BATTLE_ARPEGGIOTABLE
    .dw BATTLE_ARPEGGIOTABLE
    .dw BATTLE_EFFECTBLOCKTABLE
    .dw BATTLE_EFFECTBLOCKTABLE
BATTLE_ARPEGGIOTABLE:
BATTLE_PITCHTABLE:
BATTLE_INSTRUMENTTABLE: .dw BATTLE_EMPTYINSTRUMENT
    .dw BATTLE_INSTRUMENT1
    .dw BATTLE_INSTRUMENT2
    .dw BATTLE_INSTRUMENT3
    .dw BATTLE_INSTRUMENT4
    .dw BATTLE_INSTRUMENT5
BATTLE_EMPTYINSTRUMENT: .db 0
BATTLE_EMPTYINSTRUMENT_LOOP: .db 0
    .db 6
BATTLE_INSTRUMENT1: .db 1
PLY_AKG_OPCODE_SBC_HL_BC_MSB: .db 249
    .db 241
    .db 233
    .db 225
    .db 217
    .db 209
    .db 201
    .db 193
    .db 185
    .db 177
    .db 169
    .db 161
    .db 153
    .db 145
    .db 137
    .db 6
BATTLE_INSTRUMENT2: .db 1
    .db 248
    .db 1
    .db 113
    .db 32
    .db 150
    .db 0
    .db 105
    .db 32
    .db 44
    .db 1
    .db 97
    .db 32
    .db 144
    .db 1
    .db 89
    .db 32
    .db 244
    .db 1
    .db 81
    .db 32
    .db 88
    .db 2
    .db 6
BATTLE_INSTRUMENT3: .db 1
    .db 248
    .db 1
    .db 232
    .db 1
    .db 216
    .db 1
    .db 192
    .db 1
    .db 168
    .db 1
    .db 6
BATTLE_INSTRUMENT4: .db 1
    .db 248
    .db 1
    .db 113
    .db 34
    .db 246
    .db 255
    .db 97
    .db 35
    .db 226
    .db 255
    .db 216
    .db 1
    .db 80
    .db 208
    .db 1
    .db 200
    .db 1
    .db 192
    .db 1
    .db 184
    .db 1
    .db 176
    .db 1
    .db 168
    .db 1
    .db 160
    .db 1
    .db 144
    .db 1
    .db 136
    .db 1
    .db 6
BATTLE_INSTRUMENT5: .db 1
    .db 121
    .db 32
    .db 244
    .db 1
    .db 113
    .db 32
    .db 38
    .db 2
    .db 105
    .db 32
    .db 88
    .db 2
    .db 97
    .db 32
    .db 138
    .db 2
    .db 89
    .db 32
    .db 188
    .db 2
    .db 81
    .db 32
    .db 238
    .db 2
    .db 73
    .db 32
    .db 32
    .db 3
    .db 65
    .db 32
    .db 82
    .db 3
    .db 57
    .db 32
    .db 132
    .db 3
    .db 6
BATTLE_EFFECTBLOCKTABLE:
BATTLE_SUBSONG0_START: .db 1
    .db 0
    .db 1
    .db 0
    .db 2
    .db 3
    .db 0
BATTLE_SUBSONG0_LINKER:
BATTLE_SUBSONG0_LINKER_LOOP: .dw BATTLE_SUBSONG0_TRACK0
    .dw BATTLE_SUBSONG0_TRACK1
    .dw BATTLE_SUBSONG0_TRACK2
    .dw BATTLE_SUBSONG0_LINKERBLOCK0
    .dw BATTLE_SUBSONG0_TRACK3
    .dw BATTLE_SUBSONG0_TRACK1
    .dw BATTLE_SUBSONG0_TRACK2
    .dw BATTLE_SUBSONG0_LINKERBLOCK0
    .dw BATTLE_SUBSONG0_TRACK4
    .dw BATTLE_SUBSONG0_TRACK1
    .dw BATTLE_SUBSONG0_TRACK5
    .dw BATTLE_SUBSONG0_LINKERBLOCK0
    .db 0
    .db 0
    .dw BATTLE_SUBSONG0_LINKER
BATTLE_SUBSONG0_LINKERBLOCK0: .db 64
    .db 0
    .db 0
    .db 0
    .dw BATTLE_SUBSONG0_SPEEDTRACK0
    .dw BATTLE_SUBSONG0_EVENTTRACK0
BATTLE_SUBSONG0_TRACK0: .db 61
    .db 31
    .db 182
    .db 1
    .db 126
    .db 54
    .db 126
    .db 54
    .db 126
    .db 54
    .db 126
    .db 54
    .db 126
    .db 54
    .db 126
    .db 54
    .db 126
    .db 55
    .db 61
    .db 127
BATTLE_SUBSONG0_TRACK1: .db 175
    .db 1
    .db 126
    .db 50
    .db 60
    .db 47
    .db 60
    .db 42
    .db 60
    .db 47
    .db 60
    .db 50
    .db 126
    .db 47
    .db 126
    .db 50
    .db 60
    .db 47
    .db 60
    .db 42
    .db 60
    .db 47
    .db 60
    .db 50
    .db 126
    .db 47
    .db 126
    .db 50
    .db 60
    .db 47
    .db 60
    .db 42
    .db 60
    .db 47
    .db 60
    .db 50
    .db 126
    .db 47
    .db 126
    .db 50
    .db 60
    .db 47
    .db 60
    .db 42
    .db 60
    .db 47
    .db 60
    .db 50
    .db 61
    .db 127
BATTLE_SUBSONG0_TRACK2: .db 176
    .db 2
    .db 60
    .db 48
    .db 60
    .db 176
    .db 3
    .db 60
    .db 176
    .db 4
    .db 60
    .db 176
    .db 5
    .db 60
    .db 176
    .db 2
    .db 60
    .db 176
    .db 3
    .db 60
    .db 176
    .db 2
    .db 176
    .db 4
    .db 176
    .db 2
    .db 60
    .db 48
    .db 60
    .db 176
    .db 3
    .db 60
    .db 176
    .db 4
    .db 60
    .db 176
    .db 5
    .db 60
    .db 176
    .db 2
    .db 60
    .db 176
    .db 3
    .db 60
    .db 176
    .db 2
    .db 176
    .db 4
    .db 176
    .db 2
    .db 60
    .db 48
    .db 60
    .db 176
    .db 3
    .db 60
    .db 176
    .db 4
    .db 60
    .db 176
    .db 5
    .db 60
    .db 176
    .db 2
    .db 60
    .db 176
    .db 3
    .db 60
    .db 176
    .db 2
    .db 176
    .db 4
    .db 176
    .db 2
    .db 60
    .db 48
    .db 60
    .db 176
    .db 3
    .db 60
    .db 176
    .db 4
    .db 60
    .db 176
    .db 5
    .db 60
    .db 176
    .db 2
    .db 60
    .db 176
    .db 3
    .db 60
    .db 176
    .db 2
    .db 176
    .db 4
    .db 61
    .db 127
BATTLE_SUBSONG0_TRACK3: .db 182
    .db 1
    .db 126
    .db 54
    .db 126
    .db 54
    .db 126
    .db 54
    .db 126
    .db 54
    .db 126
    .db 54
    .db 126
    .db 54
    .db 126
    .db 55
    .db 126
    .db 54
    .db 126
    .db 54
    .db 126
    .db 54
    .db 126
    .db 54
    .db 126
    .db 54
    .db 126
    .db 54
    .db 126
    .db 54
    .db 126
    .db 55
    .db 61
    .db 127
BATTLE_SUBSONG0_TRACK4: .db 182
    .db 1
    .db 126
    .db 54
    .db 126
    .db 54
    .db 126
    .db 54
    .db 126
    .db 54
    .db 126
    .db 54
    .db 126
    .db 54
    .db 126
    .db 55
    .db 61
    .db 127
BATTLE_SUBSONG0_TRACK5: .db 176
    .db 2
    .db 60
    .db 48
    .db 60
    .db 176
    .db 3
    .db 60
    .db 176
    .db 4
    .db 60
    .db 176
    .db 5
    .db 60
    .db 176
    .db 2
    .db 60
    .db 176
    .db 3
    .db 60
    .db 176
    .db 2
    .db 176
    .db 4
    .db 176
    .db 2
    .db 60
    .db 48
    .db 60
    .db 176
    .db 3
    .db 60
    .db 176
    .db 4
    .db 60
    .db 176
    .db 5
    .db 60
    .db 176
    .db 2
    .db 48
    .db 176
    .db 3
    .db 176
    .db 4
    .db 48
    .db 48
    .db 176
    .db 2
    .db 60
    .db 48
    .db 60
    .db 176
    .db 3
    .db 60
    .db 176
    .db 4
    .db 60
    .db 176
    .db 5
    .db 60
    .db 176
    .db 2
    .db 60
    .db 176
    .db 3
    .db 60
    .db 176
    .db 2
    .db 176
    .db 4
    .db 176
    .db 2
    .db 60
    .db 48
    .db 60
    .db 176
    .db 3
    .db 60
    .db 176
    .db 4
    .db 60
    .db 176
    .db 5
    .db 60
    .db 176
    .db 2
    .db 60
    .db 176
    .db 3
    .db 60
    .db 176
    .db 2
    .db 176
    .db 4
    .db 61
    .db 127
BATTLE_SUBSONG0_SPEEDTRACK0: .db 255
BATTLE_SUBSONG0_EVENTTRACK0: .db 255
SFX_SOUNDEFFECTS:
_SFX_SOUNDEFFECTS:: .dw SFX_SOUNDEFFECTS_SOUND1
    .dw SFX_SOUNDEFFECTS_SOUND2
    .dw SFX_SOUNDEFFECTS_SOUND3
    .dw SFX_SOUNDEFFECTS_SOUND4
    .dw SFX_SOUNDEFFECTS_SOUND5
SFX_SOUNDEFFECTS_SOUND1: .db 0
SFX_SOUNDEFFECTS_SOUND1_LOOP: .db 189
    .db 1
    .db 95
    .db 0
    .db 189
    .db 1
    .db 99
    .db 0
    .db 177
    .db 1
    .db 102
    .db 0
    .db 173
    .db 1
    .db 106
    .db 0
    .db 4
SFX_SOUNDEFFECTS_SOUND2: .db 1
SFX_SOUNDEFFECTS_SOUND2_LOOP: .db 189
    .db 1
    .db 45
    .db 1
    .db 189
    .db 8
    .db 63
    .db 1
    .db 185
    .db 2
    .db 146
    .db 1
    .db 181
    .db 16
    .db 213
    .db 0
    .db 177
    .db 2
    .db 225
    .db 0
    .db 173
    .db 2
    .db 239
    .db 0
    .db 165
    .db 16
    .db 102
    .db 1
    .db 157
    .db 31
    .db 119
    .db 0
    .db 153
    .db 7
    .db 80
    .db 0
    .db 4
SFX_SOUNDEFFECTS_SOUND3: .db 1
SFX_SOUNDEFFECTS_SOUND3_LOOP: .db 189
    .db 1
    .db 119
    .db 0
    .db 57
    .db 60
    .db 0
    .db 181
    .db 1
    .db 95
    .db 0
    .db 49
    .db 47
    .db 0
    .db 185
    .db 1
    .db 80
    .db 0
    .db 61
    .db 40
    .db 0
    .db 3
    .db 15
    .db 0
    .db 222
    .db 1
    .db 61
    .db 239
    .db 0
    .db 3
    .db 15
    .db 0
    .db 222
    .db 1
    .db 61
    .db 239
    .db 0
    .db 3
    .db 15
    .db 0
    .db 222
    .db 1
    .db 61
    .db 239
    .db 0
    .db 3
    .db 30
    .db 0
    .db 188
    .db 3
    .db 61
    .db 239
    .db 0
    .db 3
    .db 30
    .db 0
    .db 188
    .db 3
    .db 61
    .db 239
    .db 0
    .db 4
SFX_SOUNDEFFECTS_SOUND4: .db 1
SFX_SOUNDEFFECTS_SOUND4_LOOP: .db 189
    .db 1
    .db 119
    .db 0
    .db 61
    .db 56
    .db 0
    .db 189
    .db 1
    .db 106
    .db 0
    .db 61
    .db 53
    .db 0
    .db 61
    .db 100
    .db 0
    .db 61
    .db 50
    .db 0
    .db 4
SFX_SOUNDEFFECTS_SOUND5: .db 1
SFX_SOUNDEFFECTS_SOUND5_LOOP: .db 3
    .db 2
    .db 0
    .db 27
    .db 0
    .db 3
    .db 3
    .db 0
    .db 47
    .db 0
    .db 3
    .db 2
    .db 0
    .db 30
    .db 0
    .db 3
    .db 5
    .db 0
    .db 75
    .db 0
    .db 3
    .db 3
    .db 0
    .db 47
    .db 0
    .db 3
    .db 7
    .db 0
    .db 119
    .db 0
    .db 3
    .db 5
    .db 0
    .db 75
    .db 0
    .db 3
    .db 12
    .db 0
    .db 190
    .db 0
    .db 3
    .db 7
    .db 0
    .db 119
    .db 0
    .db 3
    .db 19
    .db 0
    .db 45
    .db 1
    .db 3
    .db 12
    .db 0
    .db 190
    .db 0
    .db 3
    .db 34
    .db 0
    .db 24
    .db 2
    .db 3
    .db 50
    .db 0
    .db 36
    .db 3
    .db 4
PLY_AKG_START: jp PLY_AKG_INIT
    jp PLY_AKG_PLAY
    jp PLY_AKG_INITTABLEORA_END
_PLY_AKG_INITSOUNDEFFECTS::
PLY_AKG_INITSOUNDEFFECTS: ld (PLY_AKG_PTSOUNDEFFECTTABLE+1),hl
    ret 
_PLY_AKG_PLAYSOUNDEFFECT::
PLY_AKG_PLAYSOUNDEFFECT: dec a
PLY_AKG_PTSOUNDEFFECTTABLE: ld hl,#0
    ld e,a
    ld d,#0
    add hl,de
    add hl,de
    ld e,(hl)
    inc hl
    ld d,(hl)
    ld a,(de)
    inc de
    ex af,af'
    ld a,b
    ld hl,#PLY_AKG_CHANNEL1_SOUNDEFFECTDATA
    ld b,#0
    sla c
    sla c
    sla c
    add hl,bc
    ld (hl),e
    inc hl
    ld (hl),d
    inc hl
    ld (hl),a
    inc hl
    ld (hl),#0
    inc hl
    ex af,af'
    ld (hl),a
    ret 
_PLY_AKG_STOPSOUNDEFFECTFROMCHANNEL::
PLY_AKG_STOPSOUNDEFFECTFROMCHANNEL: add a,a
    add a,a
    add a,a
    ld e,a
    ld d,#0
    ld hl,#PLY_AKG_CHANNEL1_SOUNDEFFECTDATA
    add hl,de
    ld (hl),d
    inc hl
    ld (hl),d
    ret 
PLY_AKG_PLAYSOUNDEFFECTSSTREAM: rla 
    rla 
    ld ix,#PLY_AKG_CHANNEL1_SOUNDEFFECTDATA
    ld iy,#PLY_AKG_PSGREG8
    ld hl,#PLY_AKG_PSGREG01_INSTR+1
    exx
    ld c,a
    call PLY_AKG_PSES_PLAY
    ld ix,#PLY_AKG_CHANNEL2_SOUNDEFFECTDATA
    ld iy,#PLY_AKG_PSGREG9
    exx
    ld hl,#PLY_AKG_PSGREG23_INSTR+1
    exx
    srl c
    call PLY_AKG_PSES_PLAY
    ld ix,#PLY_AKG_CHANNEL3_SOUNDEFFECTDATA
    ld iy,#PLY_AKG_PSGREG10
    exx
    ld hl,#PLY_AKG_PSGREG45_INSTR+1
    exx
    scf
    rr c
    call PLY_AKG_PSES_PLAY
    ld a,c
    ret 
PLY_AKG_PSES_PLAY: ld l,+0(ix)
    ld h,+1(ix)
    ld a,l
    or h
    ret z
PLY_AKG_PSES_READFIRSTBYTE: ld a,(hl)
    inc hl
    ld b,a
    rra 
    jr c,PLY_AKG_PSES_SOFTWAREORSOFTWAREANDHARDWARE
    rra 
    rra 
PLY_AKG_PSES_S_ENDORLOOP: xor a
    ld +0(ix),a
    ld +1(ix),a
    ret 
PLY_AKG_PSES_SAVEPOINTERANDEXIT: ld a,+3(ix)
    cp +4(ix)
    jr c,PLY_AKG_PSES_NOTREACHED
    ld +3(ix),#0
    .db 221
    .db 117
    .db 0
    .db 221
    .db 116
    .db 1
    ret 
PLY_AKG_PSES_NOTREACHED: inc +3(ix)
    ret 
PLY_AKG_PSES_SOFTWAREORSOFTWAREANDHARDWARE: rra 
    jr c,PLY_AKG_PSES_SOFTWAREANDHARDWARE
    call PLY_AKG_PSES_MANAGEVOLUMEFROMA_FILTER4BITS
    rl b
    call PLY_AKG_PSES_READNOISEIFNEEDEDANDOPENORCLOSENOISECHANNEL
    res 2,c
    call PLY_AKG_PSES_READSOFTWAREPERIOD
    jr PLY_AKG_PSES_SAVEPOINTERANDEXIT
PLY_AKG_PSES_SOFTWAREANDHARDWARE: call PLY_AKG_PSES_SHARED_READRETRIGHARDWAREENVPERIODNOISE
    call PLY_AKG_PSES_READSOFTWAREPERIOD
    res 2,c
    jr PLY_AKG_PSES_SAVEPOINTERANDEXIT
PLY_AKG_PSES_SHARED_READRETRIGHARDWAREENVPERIODNOISE: rra 
    and #7
    add a,#8
    ld (PLY_AKG_PSGREG13_INSTR+1),a
    set 5,c
    call PLY_AKG_PSES_READHARDWAREPERIOD
    ld a,#16
    jp PLY_AKG_PSES_MANAGEVOLUMEFROMA_HARD
PLY_AKG_PSES_READNOISEIFNEEDEDANDOPENORCLOSENOISECHANNEL: jr c,PLY_AKG_PSES_READNOISEANDOPENNOISECHANNEL_OPENNOISE
    set 5,c
    ret 
PLY_AKG_PSES_READNOISEANDOPENNOISECHANNEL_OPENNOISE: ld a,(hl)
    ld (PLY_AKG_PSGREG6),a
    inc hl
    res 5,c
    ret 
PLY_AKG_PSES_READHARDWAREPERIOD: ld a,(hl)
    ld (PLY_AKG_PSGHARDWAREPERIOD_INSTR+1),a
    inc hl
    ld a,(hl)
    ld (PLY_AKG_PSGHARDWAREPERIOD_INSTR+2),a
    inc hl
    ret 
PLY_AKG_PSES_READSOFTWAREPERIOD: ld a,(hl)
    inc hl
    exx
    ld (hl),a
    inc hl
    exx
    ld a,(hl)
    inc hl
    exx
    ld (hl),a
    exx
    ret 
PLY_AKG_PSES_MANAGEVOLUMEFROMA_FILTER4BITS: and #15
PLY_AKG_PSES_MANAGEVOLUMEFROMA_HARD: sub +2(ix)
    jr nc,PLY_AKG_PSES_MVFA_NOOVERFLOW
    xor a
PLY_AKG_PSES_MVFA_NOOVERFLOW: ld +0(iy),a
    ret 
PLY_AKG_CHANNEL1_SOUNDEFFECTDATA: .dw 0
PLY_AKG_CHANNEL1_SOUNDEFFECTINVERTEDVOLUME: .db 0
PLY_AKG_CHANNEL1_SOUNDEFFECTCURRENTSTEP: .db 0
PLY_AKG_CHANNEL1_SOUNDEFFECTSPEED: .db 0
    .db 0
    .db 0
    .db 0
PLY_AKG_CHANNEL2_SOUNDEFFECTDATA: .db 0
    .db 0
    .db 0
    .db 0
    .db 0
    .db 0
    .db 0
    .db 0
PLY_AKG_CHANNEL3_SOUNDEFFECTDATA: .db 0
    .db 0
    .db 0
    .db 0
    .db 0
    .db 0
    .db 0
    .db 0
_PLY_AKG_INIT::
PLY_AKG_INIT: ld de,#4
    add hl,de
    inc hl
    inc hl
    ld de,#PLY_AKG_PITCHESTABLE+1
    ldi
    ldi
    ld de,#PLY_AKG_INSTRUMENTSTABLE+1
    ldi
    ldi
    ld c,(hl)
    inc hl
    ld b,(hl)
    inc hl
    ld (PLY_AKG_CHANNEL_READEFFECTS_EFFECTBLOCKS1+1),bc
    ld (PLY_AKG_CHANNEL_READEFFECTS_EFFECTBLOCKS2+1),bc
    add a,a
    ld e,a
    ld d,#0
    add hl,de
    ld a,(hl)
    inc hl
    ld h,(hl)
    ld l,a
    ld de,#5
    add hl,de
    ld de,#PLY_AKG_CHANNEL3_READCELLEND+1
    ldi
    ld de,#PLY_AKG_CHANNEL1_NOTE+1
    ldi
    ld (PLY_AKG_READLINKER+1),hl
    ld hl,#PLY_AKG_INITTABLE0
    ld bc,#1792
    call PLY_AKG_INIT_READWORDSANDFILL
    inc c
    ld hl,#PLY_AKG_INITTABLE0_END
    ld b,#3
    call PLY_AKG_INIT_READWORDSANDFILL
    ld hl,#PLY_AKG_INITTABLE1_END
    ld bc,#1207
    call PLY_AKG_INIT_READWORDSANDFILL
    ld hl,(PLY_AKG_INSTRUMENTSTABLE+1)
    ld e,(hl)
    inc hl
    ld d,(hl)
    ex de,hl
    inc hl
    ld (PLY_AKG_ENDWITHOUTLOOP+1),hl
    ld (PLY_AKG_CHANNEL1_PTINSTRUMENT+1),hl
    ld (PLY_AKG_CHANNEL2_PTINSTRUMENT+1),hl
    ld (PLY_AKG_CHANNEL3_PTINSTRUMENT+1),hl
    ld hl,#0
    ld (PLY_AKG_CHANNEL1_SOUNDEFFECTDATA),hl
    ld (PLY_AKG_CHANNEL2_SOUNDEFFECTDATA),hl
    ld (PLY_AKG_CHANNEL3_SOUNDEFFECTDATA),hl
    ret 
PLY_AKG_INIT_READWORDSANDFILL_LOOP: ld e,(hl)
    inc hl
    ld d,(hl)
    inc hl
    ld a,c
    ld (de),a
PLY_AKG_INIT_READWORDSANDFILL: djnz PLY_AKG_INIT_READWORDSANDFILL_LOOP
    ret 
PLY_AKG_INITTABLE0: .dw PLY_AKG_CHANNEL1_INVERTEDVOLUMEINTEGERANDDECIMAL+1
    .dw PLY_AKG_CHANNEL1_INVERTEDVOLUMEINTEGER
    .dw PLY_AKG_CHANNEL2_INVERTEDVOLUMEINTEGERANDDECIMAL+1
    .dw PLY_AKG_CHANNEL2_INVERTEDVOLUMEINTEGER
    .dw PLY_AKG_CHANNEL3_INVERTEDVOLUMEINTEGERANDDECIMAL+1
    .dw PLY_AKG_CHANNEL3_INVERTEDVOLUMEINTEGER
PLY_AKG_INITTABLE0_END:
PLY_AKG_INITTABLE1: .dw PLY_AKG_PATTERNDECREASINGHEIGHT+1
    .dw PLY_AKG_TICKDECREASINGCOUNTER+1
PLY_AKG_INITTABLE1_END:
PLY_AKG_INITTABLEORA: .dw PLY_AKG_CHANNEL1_ISPITCHTABLE
    .dw PLY_AKG_CHANNEL2_ISPITCHTABLE
    .dw PLY_AKG_CHANNEL3_ISPITCHTABLE
PLY_AKG_INITTABLEORA_END:
_PLY_AKG_STOP::
PLY_AKG_STOP: ld (PLY_AKG_PSGREG13_END+1),sp
    xor a
    ld l,a
    ld h,a
    ld (PLY_AKG_PSGREG8),a
    ld (PLY_AKG_PSGREG9),hl
    ld a,#191
    jp PLY_AKG_SENDPSGREGISTERS
_PLY_AKG_PLAY::
PLY_AKG_PLAY: ld (PLY_AKG_PSGREG13_END+1),sp
PLY_AKG_TICKDECREASINGCOUNTER: ld a,#1
    dec a
    jp nz,PLY_AKG_SETSPEEDBEFOREPLAYSTREAMS
PLY_AKG_PATTERNDECREASINGHEIGHT: ld a,#1
    dec a
    jr nz,PLY_AKG_SETCURRENTLINEBEFOREREADLINE
PLY_AKG_READLINKER:
PLY_AKG_READLINKER_PTLINKER: ld sp,#0
    pop hl
    ld a,l
    or h
    jr nz,PLY_AKG_READLINKER_NOLOOP
    pop hl
    ld sp,hl
    pop hl
PLY_AKG_READLINKER_NOLOOP: ld (PLY_AKG_CHANNEL1_READTRACK+1),hl
    pop hl
    ld (PLY_AKG_CHANNEL2_READTRACK+1),hl
    pop hl
    ld (PLY_AKG_CHANNEL3_READTRACK+1),hl
    pop hl
    ld (PLY_AKG_READLINKER+1),sp
    ld sp,hl
    pop hl
    ld c,l
    xor a
    ld (PLY_AKG_READLINE+1),a
    ld (PLY_AKG_CHANNEL1_READCELLEND+1),a
    ld (PLY_AKG_CHANNEL2_READCELLEND+1),a
    ld a,c
PLY_AKG_SETCURRENTLINEBEFOREREADLINE: ld (PLY_AKG_PATTERNDECREASINGHEIGHT+1),a
PLY_AKG_READLINE:
PLY_AKG_CHANNEL1_WAITCOUNTER: ld a,#0
    sub #1
    jr c,PLY_AKG_CHANNEL1_READTRACK
    ld (PLY_AKG_READLINE+1),a
    jp PLY_AKG_CHANNEL1_READCELLEND
PLY_AKG_CHANNEL1_READTRACK:
PLY_AKG_CHANNEL1_PTTRACK: ld hl,#0
    ld c,(hl)
    inc hl
    ld a,c
    and #63
    cp #60
    jr c,PLY_AKG_CHANNEL1_NOTE
    sub #60
    jp z,PLY_AKG_CHANNEL1_MAYBEEFFECTS
    dec a
    jr z,PLY_AKG_CHANNEL1_WAIT
    dec a
    jr z,PLY_AKG_CHANNEL1_SMALLWAIT
    ld a,(hl)
    inc hl
    jr PLY_AKG_CHANNEL1_AFTERNOTEKNOWN
PLY_AKG_CHANNEL1_SMALLWAIT: ld a,c
    rlca 
    rlca 
    and #3
    inc a
    ld (PLY_AKG_READLINE+1),a
    jr PLY_AKG_CHANNEL1_BEFOREEND_STORECELLPOINTER
PLY_AKG_CHANNEL1_WAIT: ld a,(hl)
    ld (PLY_AKG_READLINE+1),a
    inc hl
    jr PLY_AKG_CHANNEL1_BEFOREEND_STORECELLPOINTER
PLY_AKG_CHANNEL1_SAMEINSTRUMENT:
PLY_AKG_CHANNEL1_PTBASEINSTRUMENT: ld de,#0
    ld (PLY_AKG_CHANNEL1_PTINSTRUMENT+1),de
    jr PLY_AKG_CHANNEL1_AFTERINSTRUMENT
PLY_AKG_CHANNEL1_NOTE:
PLY_AKG_BASENOTEINDEX: add a,#0
PLY_AKG_CHANNEL1_AFTERNOTEKNOWN: ld (PLY_AKG_CHANNEL1_TRACKNOTE+1),a
    rl c
    jr nc,PLY_AKG_CHANNEL1_SAMEINSTRUMENT
    ld a,(hl)
    inc hl
    exx
    ld l,a
    ld h,#0
    add hl,hl
PLY_AKG_INSTRUMENTSTABLE: ld de,#0
    add hl,de
    ld sp,hl
    pop hl
    ld a,(hl)
    inc hl
    ld (PLY_AKG_CHANNEL1_INSTRUMENTSPEED+1),a
    ld (PLY_AKG_CHANNEL1_PTINSTRUMENT+1),hl
    ld (PLY_AKG_CHANNEL1_SAMEINSTRUMENT+1),hl
    exx
PLY_AKG_CHANNEL1_AFTERINSTRUMENT: ex de,hl
    xor a
    ld (PLY_AKG_CHANNEL1_PITCHTABLECURRENTSTEP+1),a
    ld (PLY_AKG_CHANNEL1_INSTRUMENTSTEP+2),a
    ld a,(PLY_AKG_CHANNEL1_PITCHBASESPEED)
    ld (PLY_AKG_CHANNEL1_PITCHTABLESPEED),a
    ld hl,(PLY_AKG_CHANNEL1_PITCHTABLEBASE)
    ld (PLY_AKG_CHANNEL1_PITCHTABLE+1),hl
    ex de,hl
    rl c
    jp c,PLY_AKG_CHANNEL1_READEFFECTS
PLY_AKG_CHANNEL1_BEFOREEND_STORECELLPOINTER: ld (PLY_AKG_CHANNEL1_READTRACK+1),hl
PLY_AKG_CHANNEL1_READCELLEND:
PLY_AKG_CHANNEL2_WAITCOUNTER: ld a,#0
    sub #1
    jr c,PLY_AKG_CHANNEL2_READTRACK
    ld (PLY_AKG_CHANNEL1_READCELLEND+1),a
    jp PLY_AKG_CHANNEL2_READCELLEND
PLY_AKG_CHANNEL2_READTRACK:
PLY_AKG_CHANNEL2_PTTRACK: ld hl,#0
    ld c,(hl)
    inc hl
    ld a,c
    and #63
    cp #60
    jr c,PLY_AKG_CHANNEL2_NOTE
    sub #60
    jp z,PLY_AKG_CHANNEL1_READEFFECTSEND
    dec a
    jr z,PLY_AKG_CHANNEL2_WAIT
    dec a
    jr z,PLY_AKG_CHANNEL2_SMALLWAIT
    ld a,(hl)
    inc hl
    jr PLY_AKG_CHANNEL2_AFTERNOTEKNOWN
PLY_AKG_CHANNEL2_SMALLWAIT: ld a,c
    rlca 
    rlca 
    and #3
    inc a
    ld (PLY_AKG_CHANNEL1_READCELLEND+1),a
    jr PLY_AKG_CHANNEL2_BEFOREEND_STORECELLPOINTER
PLY_AKG_CHANNEL2_WAIT: ld a,(hl)
    ld (PLY_AKG_CHANNEL1_READCELLEND+1),a
    inc hl
    jr PLY_AKG_CHANNEL2_BEFOREEND_STORECELLPOINTER
PLY_AKG_CHANNEL2_SAMEINSTRUMENT:
PLY_AKG_CHANNEL2_PTBASEINSTRUMENT: ld de,#0
    ld (PLY_AKG_CHANNEL2_PTINSTRUMENT+1),de
    jr PLY_AKG_CHANNEL2_AFTERINSTRUMENT
PLY_AKG_CHANNEL2_NOTE: ld b,a
    ld a,(PLY_AKG_CHANNEL1_NOTE+1)
    add a,b
PLY_AKG_CHANNEL2_AFTERNOTEKNOWN: ld (PLY_AKG_CHANNEL2_TRACKNOTE+1),a
    rl c
    jr nc,PLY_AKG_CHANNEL2_SAMEINSTRUMENT
    ld a,(hl)
    inc hl
    exx
    ld e,a
    ld d,#0
    ld hl,(PLY_AKG_INSTRUMENTSTABLE+1)
    add hl,de
    add hl,de
    ld sp,hl
    pop hl
    ld a,(hl)
    inc hl
    ld (PLY_AKG_CHANNEL2_INSTRUMENTSPEED+1),a
    ld (PLY_AKG_CHANNEL2_PTINSTRUMENT+1),hl
    ld (PLY_AKG_CHANNEL2_SAMEINSTRUMENT+1),hl
    exx
PLY_AKG_CHANNEL2_AFTERINSTRUMENT: ex de,hl
    xor a
    ld (PLY_AKG_CHANNEL2_PITCHTABLECURRENTSTEP+1),a
    ld (PLY_AKG_CHANNEL2_INSTRUMENTSTEP+2),a
    ld a,(PLY_AKG_CHANNEL2_PITCHBASESPEED)
    ld (PLY_AKG_CHANNEL2_PITCHTABLESPEED),a
    ld hl,(PLY_AKG_CHANNEL2_PITCHTABLEBASE)
    ld (PLY_AKG_CHANNEL2_PITCHTABLE+1),hl
    ex de,hl
    rl c
    jp c,PLY_AKG_CHANNEL2_READEFFECTS
PLY_AKG_CHANNEL2_BEFOREEND_STORECELLPOINTER: ld (PLY_AKG_CHANNEL2_READTRACK+1),hl
PLY_AKG_CHANNEL2_READCELLEND:
PLY_AKG_CHANNEL3_WAITCOUNTER: ld a,#0
    sub #1
    jr c,PLY_AKG_CHANNEL3_READTRACK
    ld (PLY_AKG_CHANNEL2_READCELLEND+1),a
    jp PLY_AKG_CHANNEL3_READCELLEND
PLY_AKG_CHANNEL3_READTRACK:
PLY_AKG_CHANNEL3_PTTRACK: ld hl,#0
    ld c,(hl)
    inc hl
    ld a,c
    and #63
    cp #60
    jr c,PLY_AKG_CHANNEL3_NOTE
    sub #60
    jp z,PLY_AKG_CHANNEL2_READEFFECTSEND
    dec a
    jr z,PLY_AKG_CHANNEL3_WAIT
    dec a
    jr z,PLY_AKG_CHANNEL3_SMALLWAIT
    ld a,(hl)
    inc hl
    jr PLY_AKG_CHANNEL3_AFTERNOTEKNOWN
PLY_AKG_CHANNEL3_SMALLWAIT: ld a,c
    rlca 
    rlca 
    and #3
    inc a
    ld (PLY_AKG_CHANNEL2_READCELLEND+1),a
    jr PLY_AKG_CHANNEL3_BEFOREEND_STORECELLPOINTER
PLY_AKG_CHANNEL3_WAIT: ld a,(hl)
    ld (PLY_AKG_CHANNEL2_READCELLEND+1),a
    inc hl
    jr PLY_AKG_CHANNEL3_BEFOREEND_STORECELLPOINTER
PLY_AKG_CHANNEL3_SAMEINSTRUMENT:
PLY_AKG_CHANNEL3_PTBASEINSTRUMENT: ld de,#0
    ld (PLY_AKG_CHANNEL3_PTINSTRUMENT+1),de
    jr PLY_AKG_CHANNEL3_AFTERINSTRUMENT
PLY_AKG_CHANNEL3_NOTE: ld b,a
    ld a,(PLY_AKG_CHANNEL1_NOTE+1)
    add a,b
PLY_AKG_CHANNEL3_AFTERNOTEKNOWN: ld (PLY_AKG_CHANNEL3_TRACKNOTE+1),a
    rl c
    jr nc,PLY_AKG_CHANNEL3_SAMEINSTRUMENT
    ld a,(hl)
    inc hl
    exx
    ld e,a
    ld d,#0
    ld hl,(PLY_AKG_INSTRUMENTSTABLE+1)
    add hl,de
    add hl,de
    ld sp,hl
    pop hl
    ld a,(hl)
    inc hl
    ld (PLY_AKG_CHANNEL3_INSTRUMENTSPEED+1),a
    ld (PLY_AKG_CHANNEL3_PTINSTRUMENT+1),hl
    ld (PLY_AKG_CHANNEL3_SAMEINSTRUMENT+1),hl
    exx
PLY_AKG_CHANNEL3_AFTERINSTRUMENT: ex de,hl
    xor a
    ld (PLY_AKG_CHANNEL3_PITCHTABLECURRENTSTEP+1),a
    ld (PLY_AKG_CHANNEL3_INSTRUMENTSTEP+2),a
    ld a,(PLY_AKG_CHANNEL3_PITCHBASESPEED)
    ld (PLY_AKG_CHANNEL3_PITCHTABLESPEED),a
    ld hl,(PLY_AKG_CHANNEL3_PITCHTABLEBASE)
    ld (PLY_AKG_CHANNEL3_PITCHTABLE+1),hl
    ex de,hl
    rl c
    jp c,PLY_AKG_CHANNEL3_READEFFECTS
PLY_AKG_CHANNEL3_BEFOREEND_STORECELLPOINTER: ld (PLY_AKG_CHANNEL3_READTRACK+1),hl
PLY_AKG_CHANNEL3_READCELLEND:
PLY_AKG_CURRENTSPEED: ld a,#0
PLY_AKG_SETSPEEDBEFOREPLAYSTREAMS: ld (PLY_AKG_TICKDECREASINGCOUNTER+1),a
PLY_AKG_CHANNEL1_INVERTEDVOLUMEINTEGER = .+2
PLY_AKG_CHANNEL1_INVERTEDVOLUMEINTEGERANDDECIMAL: ld hl,#0
    ld a,h
    ld (PLY_AKG_CHANNEL1_GENERATEDCURRENTINVERTEDVOLUME+1),a
    ld de,#0
PLY_AKG_CHANNEL1_ISPITCHTABLE: or a
    jr nc,PLY_AKG_CHANNEL1_PITCHTABLE_END
PLY_AKG_CHANNEL1_PITCHTABLE: ld sp,#0
    pop de
    pop hl
    ld a,(PLY_AKG_CHANNEL1_PITCHTABLESPEED)
    ld b,a
PLY_AKG_CHANNEL1_PITCHTABLECURRENTSTEP: ld a,#0
    inc a
    cp b
    jr c,PLY_AKG_CHANNEL1_PITCHTABLE_BEFOREEND_SAVESTEP
    ld (PLY_AKG_CHANNEL1_PITCHTABLE+1),hl
    xor a
PLY_AKG_CHANNEL1_PITCHTABLE_BEFOREEND_SAVESTEP: ld (PLY_AKG_CHANNEL1_PITCHTABLECURRENTSTEP+1),a
PLY_AKG_CHANNEL1_PITCHTABLE_END: ld hl,#0
PLY_AKG_CHANNEL1_SOUNDSTREAM_RELATIVEMODIFIERADDRESS: jr PLY_AKG_CHANNEL1_AFTERARPEGGIOPITCHVARIABLES
PLY_AKG_CHANNEL1_PITCHTABLESPEED: .db 0
PLY_AKG_CHANNEL1_PITCHBASESPEED: .db 0
PLY_AKG_CHANNEL1_PITCHTABLEBASE: .db 0
    .db 0
PLY_AKG_CHANNEL1_AFTERARPEGGIOPITCHVARIABLES: add hl,de
    ld (PLY_AKG_CHANNEL1_PLAYINSTRUMENT_RELATIVEMODIFIERADDRESS+1),hl
PLY_AKG_CHANNEL2_INVERTEDVOLUMEINTEGER = .+2
PLY_AKG_CHANNEL2_INVERTEDVOLUMEINTEGERANDDECIMAL: ld hl,#0
    ld a,h
    ld (PLY_AKG_CHANNEL2_GENERATEDCURRENTINVERTEDVOLUME+1),a
    ld de,#0
PLY_AKG_CHANNEL2_ISPITCHTABLE: or a
    jr nc,PLY_AKG_CHANNEL2_PITCHTABLE_END
PLY_AKG_CHANNEL2_PITCHTABLE: ld sp,#0
    pop de
    pop hl
    ld a,(PLY_AKG_CHANNEL2_PITCHTABLESPEED)
    ld b,a
PLY_AKG_CHANNEL2_PITCHTABLECURRENTSTEP: ld a,#0
    inc a
    cp b
    jr c,PLY_AKG_CHANNEL2_PITCHTABLE_BEFOREEND_SAVESTEP
    ld (PLY_AKG_CHANNEL2_PITCHTABLE+1),hl
    xor a
PLY_AKG_CHANNEL2_PITCHTABLE_BEFOREEND_SAVESTEP: ld (PLY_AKG_CHANNEL2_PITCHTABLECURRENTSTEP+1),a
PLY_AKG_CHANNEL2_PITCHTABLE_END: ld hl,#0
PLY_AKG_CHANNEL2_SOUNDSTREAM_RELATIVEMODIFIERADDRESS: jr PLY_AKG_CHANNEL2_AFTERARPEGGIOPITCHVARIABLES
PLY_AKG_CHANNEL2_PITCHTABLESPEED: .db 0
PLY_AKG_CHANNEL2_PITCHBASESPEED: .db 0
PLY_AKG_CHANNEL2_PITCHTABLEBASE: .db 0
    .db 0
PLY_AKG_CHANNEL2_AFTERARPEGGIOPITCHVARIABLES: add hl,de
    ld (PLY_AKG_CHANNEL2_PLAYINSTRUMENT_RELATIVEMODIFIERADDRESS+1),hl
PLY_AKG_CHANNEL3_INVERTEDVOLUMEINTEGER = .+2
PLY_AKG_CHANNEL3_INVERTEDVOLUMEINTEGERANDDECIMAL: ld hl,#0
    ld a,h
    ld (PLY_AKG_CHANNEL3_GENERATEDCURRENTINVERTEDVOLUME+1),a
    ld de,#0
PLY_AKG_CHANNEL3_ISPITCHTABLE: or a
    jr nc,PLY_AKG_CHANNEL3_PITCHTABLE_END
PLY_AKG_CHANNEL3_PITCHTABLE: ld sp,#0
    pop de
    pop hl
    ld a,(PLY_AKG_CHANNEL3_PITCHTABLESPEED)
    ld b,a
PLY_AKG_CHANNEL3_PITCHTABLECURRENTSTEP: ld a,#0
    inc a
    cp b
    jr c,PLY_AKG_CHANNEL3_PITCHTABLE_BEFOREEND_SAVESTEP
    ld (PLY_AKG_CHANNEL3_PITCHTABLE+1),hl
    xor a
PLY_AKG_CHANNEL3_PITCHTABLE_BEFOREEND_SAVESTEP: ld (PLY_AKG_CHANNEL3_PITCHTABLECURRENTSTEP+1),a
PLY_AKG_CHANNEL3_PITCHTABLE_END: ld hl,#0
PLY_AKG_CHANNEL3_SOUNDSTREAM_RELATIVEMODIFIERADDRESS: jr PLY_AKG_CHANNEL3_AFTERARPEGGIOPITCHVARIABLES
PLY_AKG_CHANNEL3_PITCHTABLESPEED: .db 0
PLY_AKG_CHANNEL3_PITCHBASESPEED: .db 0
PLY_AKG_CHANNEL3_PITCHTABLEBASE: .db 0
    .db 0
PLY_AKG_CHANNEL3_AFTERARPEGGIOPITCHVARIABLES: add hl,de
    ld (PLY_AKG_CHANNEL3_PLAYINSTRUMENT_RELATIVEMODIFIERADDRESS+1),hl
    ld sp,(PLY_AKG_PSGREG13_END+1)
PLY_AKG_CHANNEL1_PLAYINSTRUMENT_RELATIVEMODIFIERADDRESS:
PLY_AKG_CHANNEL1_GENERATEDCURRENTPITCH: ld hl,#0
PLY_AKG_CHANNEL1_TRACKNOTE: ld de,#0
    exx
PLY_AKG_CHANNEL1_INSTRUMENTSTEP: .db 253
    .db 46
    .db 0
PLY_AKG_CHANNEL1_PTINSTRUMENT: ld hl,#0
PLY_AKG_CHANNEL1_GENERATEDCURRENTINVERTEDVOLUME: ld de,#57359
    call PLY_AKG_READINSTRUMENTCELL
    .db 253
    .db 125
    inc a
PLY_AKG_CHANNEL1_INSTRUMENTSPEED: cp #0
    jr c,PLY_AKG_CHANNEL1_SETINSTRUMENTSTEP
    ld (PLY_AKG_CHANNEL1_PTINSTRUMENT+1),hl
    xor a
PLY_AKG_CHANNEL1_SETINSTRUMENTSTEP: ld (PLY_AKG_CHANNEL1_INSTRUMENTSTEP+2),a
    ld a,e
    ld (PLY_AKG_PSGREG8),a
    srl d
    exx
    ld (PLY_AKG_PSGREG01_INSTR+1),hl
PLY_AKG_CHANNEL2_PLAYINSTRUMENT_RELATIVEMODIFIERADDRESS:
PLY_AKG_CHANNEL2_GENERATEDCURRENTPITCH: ld hl,#0
PLY_AKG_CHANNEL2_TRACKNOTE: ld de,#0
    exx
PLY_AKG_CHANNEL2_INSTRUMENTSTEP: .db 253
    .db 46
    .db 0
PLY_AKG_CHANNEL2_PTINSTRUMENT: ld hl,#0
PLY_AKG_CHANNEL2_GENERATEDCURRENTINVERTEDVOLUME: ld e,#15
    nop
    call PLY_AKG_READINSTRUMENTCELL
    .db 253
    .db 125
    inc a
PLY_AKG_CHANNEL2_INSTRUMENTSPEED: cp #0
    jr c,PLY_AKG_CHANNEL2_SETINSTRUMENTSTEP
    ld (PLY_AKG_CHANNEL2_PTINSTRUMENT+1),hl
    xor a
PLY_AKG_CHANNEL2_SETINSTRUMENTSTEP: ld (PLY_AKG_CHANNEL2_INSTRUMENTSTEP+2),a
    ld a,e
    ld (PLY_AKG_PSGREG9),a
    scf
    rr d
    exx
    ld (PLY_AKG_PSGREG23_INSTR+1),hl
PLY_AKG_CHANNEL3_PLAYINSTRUMENT_RELATIVEMODIFIERADDRESS:
PLY_AKG_CHANNEL3_GENERATEDCURRENTPITCH: ld hl,#0
PLY_AKG_CHANNEL3_TRACKNOTE: ld de,#0
    exx
PLY_AKG_CHANNEL3_INSTRUMENTSTEP: .db 253
    .db 46
    .db 0
PLY_AKG_CHANNEL3_PTINSTRUMENT: ld hl,#0
PLY_AKG_CHANNEL3_GENERATEDCURRENTINVERTEDVOLUME: ld e,#15
    nop
    call PLY_AKG_READINSTRUMENTCELL
    .db 253
    .db 125
    inc a
PLY_AKG_CHANNEL3_INSTRUMENTSPEED: cp #0
    jr c,PLY_AKG_CHANNEL3_SETINSTRUMENTSTEP
    ld (PLY_AKG_CHANNEL3_PTINSTRUMENT+1),hl
    xor a
PLY_AKG_CHANNEL3_SETINSTRUMENTSTEP: ld (PLY_AKG_CHANNEL3_INSTRUMENTSTEP+2),a
    ld a,e
    ld (PLY_AKG_PSGREG10),a
    ld a,d
    exx
    ld (PLY_AKG_PSGREG45_INSTR+1),hl
    call PLY_AKG_PLAYSOUNDEFFECTSSTREAM
PLY_AKG_SENDPSGREGISTERS: ld b,a
    ld a,#7
    out (160),a
    ld a,b
    out (161),a
PLY_AKG_PSGREG01_INSTR: ld hl,#0
    xor a
    out (160),a
    ld a,l
    out (161),a
    ld a,#1
    out (160),a
    ld a,h
    out (161),a
PLY_AKG_PSGREG23_INSTR: ld hl,#0
    ld a,#2
    out (160),a
    ld a,l
    out (161),a
    ld a,#3
    out (160),a
    ld a,h
    out (161),a
PLY_AKG_PSGREG45_INSTR: ld hl,#0
    ld a,#4
    out (160),a
    ld a,l
    out (161),a
    ld a,#5
    out (160),a
    ld a,h
    out (161),a
PLY_AKG_PSGREG6 = .+1
PLY_AKG_PSGREG8 = .+2
PLY_AKG_PSGREG6_8_INSTR: ld hl,#0
    ld a,#6
    out (160),a
    ld a,l
    out (161),a
    ld a,#8
    out (160),a
    ld a,h
    out (161),a
PLY_AKG_PSGREG9 = .+1
PLY_AKG_PSGREG10 = .+2
PLY_AKG_PSGREG9_10_INSTR: ld hl,#0
    ld a,#9
    out (160),a
    ld a,l
    out (161),a
    ld a,#10
    out (160),a
    ld a,h
    out (161),a
PLY_AKG_PSGHARDWAREPERIOD_INSTR: ld hl,#0
    ld a,#11
    out (160),a
    ld a,l
    out (161),a
    ld a,#12
    out (160),a
    ld a,h
    out (161),a
    ld a,#13
    out (160),a
PLY_AKG_PSGREG13_INSTR: ld a,#0
PLY_AKG_PSGREG13_OLDVALUE: cp #255
    jr z,PLY_AKG_PSGREG13_END
    ld (PLY_AKG_PSGREG13_OLDVALUE+1),a
    out (161),a
PLY_AKG_PSGREG13_END:
PLY_AKG_SAVESP: ld sp,#0
    ret 
PLY_AKG_CHANNEL1_MAYBEEFFECTS: ld (PLY_AKG_READLINE+1),a
    bit 6,c
    jp z,PLY_AKG_CHANNEL1_BEFOREEND_STORECELLPOINTER
PLY_AKG_CHANNEL1_READEFFECTS: ld iy,#PLY_AKG_CHANNEL1_SOUNDSTREAM_RELATIVEMODIFIERADDRESS
    ld ix,#PLY_AKG_CHANNEL1_PLAYINSTRUMENT_RELATIVEMODIFIERADDRESS
    ld de,#PLY_AKG_CHANNEL1_BEFOREEND_STORECELLPOINTER
    jr PLY_AKG_CHANNEL3_READEFFECTSEND
PLY_AKG_CHANNEL1_READEFFECTSEND:
PLY_AKG_CHANNEL2_MAYBEEFFECTS: ld (PLY_AKG_CHANNEL1_READCELLEND+1),a
    bit 6,c
    jp z,PLY_AKG_CHANNEL2_BEFOREEND_STORECELLPOINTER
PLY_AKG_CHANNEL2_READEFFECTS: ld iy,#PLY_AKG_CHANNEL2_SOUNDSTREAM_RELATIVEMODIFIERADDRESS
    ld ix,#PLY_AKG_CHANNEL2_PLAYINSTRUMENT_RELATIVEMODIFIERADDRESS
    ld de,#PLY_AKG_CHANNEL2_BEFOREEND_STORECELLPOINTER
    jr PLY_AKG_CHANNEL3_READEFFECTSEND
PLY_AKG_CHANNEL2_READEFFECTSEND:
PLY_AKG_CHANNEL3_MAYBEEFFECTS: ld (PLY_AKG_CHANNEL2_READCELLEND+1),a
    bit 6,c
    jp z,PLY_AKG_CHANNEL3_BEFOREEND_STORECELLPOINTER
PLY_AKG_CHANNEL3_READEFFECTS: ld iy,#PLY_AKG_CHANNEL3_SOUNDSTREAM_RELATIVEMODIFIERADDRESS
    ld ix,#PLY_AKG_CHANNEL3_PLAYINSTRUMENT_RELATIVEMODIFIERADDRESS
    ld de,#PLY_AKG_CHANNEL3_BEFOREEND_STORECELLPOINTER
PLY_AKG_CHANNEL3_READEFFECTSEND:
PLY_AKG_CHANNEL_READEFFECTS: ld (PLY_AKG_CHANNEL_READEFFECTS_ENDJUMP+1),de
    ex de,hl
    ld a,(de)
    inc de
    sla a
    jr c,PLY_AKG_CHANNEL_READEFFECTS_RELATIVEADDRESS
    exx
    ld l,a
    ld h,#0
PLY_AKG_CHANNEL_READEFFECTS_EFFECTBLOCKS1: ld de,#0
    add hl,de
    ld e,(hl)
    inc hl
    ld d,(hl)
PLY_AKG_CHANNEL_RE_EFFECTADDRESSKNOWN: ld a,(de)
    inc de
    ld (PLY_AKG_CHANNEL_RE_EFFECTRETURN+1),a
    and #254
    ld l,a
    ld h,#0
    ld sp,#PLY_AKG_EFFECTTABLE
    add hl,sp
    ld sp,hl
    ret 
PLY_AKG_CHANNEL_RE_EFFECTRETURN:
PLY_AKG_CHANNEL_RE_READNEXTEFFECTINBLOCK: ld a,#0
    rra 
    jr c,PLY_AKG_CHANNEL_RE_EFFECTADDRESSKNOWN
    exx
    ex de,hl
PLY_AKG_CHANNEL_READEFFECTS_ENDJUMP: jp 0
PLY_AKG_CHANNEL_READEFFECTS_RELATIVEADDRESS: srl a
    exx
    ld h,a
    exx
    ld a,(de)
    inc de
    exx
    ld l,a
PLY_AKG_CHANNEL_READEFFECTS_EFFECTBLOCKS2: ld de,#0
    add hl,de
    jr PLY_AKG_CHANNEL_RE_EFFECTADDRESSKNOWN
PLY_AKG_READINSTRUMENTCELL: ld a,(hl)
    inc hl
    ld b,a
    rra 
    jp c,PLY_AKG_S_OR_H_OR_SAH_OR_ENDWITHLOOP
    rra 
    jr c,PLY_AKG_STH_OR_ENDWITHOUTLOOP
    rra 
PLY_AKG_NOSOFTNOHARD: and #15
    sub e
    jr nc,PLY_AKG_NOSOFTNOHARD+6
    xor a
    ld e,a
    rl b
    jr nc,PLY_AKG_NSNH_NONOISE
    ld a,(hl)
    inc hl
    ld (PLY_AKG_PSGREG6),a
    set 2,d
    res 5,d
    ret 
PLY_AKG_NSNH_NONOISE: set 2,d
    ret 
PLY_AKG_SOFT: and #15
    sub e
    jr nc,PLY_AKG_SOFTONLY_HARDONLY_TESTSIMPLE_COMMON-1
    xor a
    ld e,a
PLY_AKG_SOFTONLY_HARDONLY_TESTSIMPLE_COMMON: rl b
    jr nc,PLY_AKG_S_NOTSIMPLE
    ld c,#0
    jr PLY_AKG_S_AFTERSIMPLETEST
PLY_AKG_S_NOTSIMPLE: ld b,(hl)
    ld c,b
    inc hl
PLY_AKG_S_AFTERSIMPLETEST: call PLY_AKG_S_OR_H_CHECKIFSIMPLEFIRST_CALCULATEPERIOD
    ld a,c
    and #31
    ret z
    ld (PLY_AKG_PSGREG6),a
    res 5,d
    ret 
PLY_AKG_ENDWITHOUTLOOP:
PLY_AKG_EMPTYINSTRUMENTDATAPT: ld hl,#0
    inc hl
    xor a
    ld b,a
    jr PLY_AKG_NOSOFTNOHARD
PLY_AKG_STH_OR_ENDWITHOUTLOOP: rra 
    jr c,PLY_AKG_ENDWITHOUTLOOP
    call PLY_AKG_STOH_HTOS_SANDH_COMMON
    ld (PLY_AKG_SH_JUMPRATIO+1),a
    exx
    ld e,l
    ld d,h
PLY_AKG_SH_JUMPRATIO: jr PLY_AKG_SH_JUMPRATIO+2
    srl h
    rr l
    srl h
    rr l
    srl h
    rr l
    srl h
    rr l
    srl h
    rr l
    srl h
    rr l
    srl h
    rr l
    jr nc,PLY_AKG_SH_JUMPRATIOEND
    inc hl
PLY_AKG_SH_JUMPRATIOEND: ld (PLY_AKG_PSGHARDWAREPERIOD_INSTR+1),hl
    ex de,hl
    exx
    ret 
PLY_AKG_S_OR_H_OR_SAH_OR_ENDWITHLOOP: rra 
    jr c,PLY_AKG_H_OR_ENDWITHLOOP
    rra 
    jp nc,PLY_AKG_SOFT
PLY_AKG_H_OR_ENDWITHLOOP:
PLY_AKG_ENDWITHLOOP: ld a,(hl)
    inc hl
    ld h,(hl)
    ld l,a
    jp PLY_AKG_READINSTRUMENTCELL
PLY_AKG_S_OR_H_CHECKIFSIMPLEFIRST_CALCULATEPERIOD: jr nc,PLY_AKG_S_OR_H_NEXTBYTE
    exx
    ex de,hl
    add hl,hl
    ld bc,#PLY_AKG_PERIODTABLE
    add hl,bc
    ld a,(hl)
    inc hl
    ld h,(hl)
    ld l,a
    add hl,de
    exx
    rl b
    rl b
    rl b
    ret 
PLY_AKG_S_OR_H_NEXTBYTE: rl b
    rl b
    rl b
    jr nc,PLY_AKG_S_OR_H_AFTERPITCH
    ld a,(hl)
    inc hl
    exx
    add a,l
    ld l,a
    exx
    ld a,(hl)
    inc hl
    exx
    adc a,h
    ld h,a
    exx
PLY_AKG_S_OR_H_AFTERPITCH: exx
    ex de,hl
    add hl,hl
    ld bc,#PLY_AKG_PERIODTABLE
    add hl,bc
    ld a,(hl)
    inc hl
    ld h,(hl)
    ld l,a
    add hl,de
    exx
    ret 
PLY_AKG_STOH_HTOS_SANDH_COMMON: ld e,#16
    rra 
    and #7
    add a,#8
    ld (PLY_AKG_PSGREG13_INSTR+1),a
    rl b
    ld c,(hl)
    ld b,c
    inc hl
    rl b
    call PLY_AKG_S_OR_H_CHECKIFSIMPLEFIRST_CALCULATEPERIOD
    ld a,c
    rla 
    rla 
    and #28
    ret 
PLY_AKG_EFFECTTABLE: .dw PLY_AKG_EFFECT_RESETFULLVOLUME
    .dw PLY_AKG_EFFECT_RESET
    .dw PLY_AKG_EFFECT_VOLUME
    .dw DUNGEON_START
    .dw DUNGEON_START
    .dw PLY_AKG_EFFECT_PITCHTABLE
    .dw PLY_AKG_EFFECT_PITCHTABLESTOP
    .dw DUNGEON_START
    .dw DUNGEON_START
    .dw DUNGEON_START
    .dw DUNGEON_START
    .dw DUNGEON_START
    .dw DUNGEON_START
    .dw DUNGEON_START
    .dw DUNGEON_START
    .dw DUNGEON_START
    .dw DUNGEON_START
PLY_AKG_EFFECT_RESETFULLVOLUME: xor a
    jr PLY_AKG_EFFECT_RESETVOLUME_AFTERREADING
PLY_AKG_EFFECT_RESET: ld a,(de)
    inc de
PLY_AKG_EFFECT_RESETVOLUME_AFTERREADING: ld -36(iy),a
    ld a,#183
    ld -28(iy),a
    jp PLY_AKG_CHANNEL_RE_EFFECTRETURN
PLY_AKG_EFFECT_VOLUME: ld a,(de)
    inc de
    ld -36(iy),a
    jp PLY_AKG_CHANNEL_RE_EFFECTRETURN
PLY_AKG_EFFECT_PITCHTABLE: ld a,(de)
    inc de
    ld l,a
    ld h,#0
    add hl,hl
PLY_AKG_PITCHESTABLE: ld bc,#0
    add hl,bc
    ld c,(hl)
    inc hl
    ld b,(hl)
    inc hl
    ld a,(bc)
    inc bc
    ld +2(iy),a
    ld +3(iy),a
    ld -24(iy),c
    ld -23(iy),b
    ld +4(iy),c
    ld +5(iy),b
    ld -28(iy),#55
    xor a
    ld -15(iy),a
    jp PLY_AKG_CHANNEL_RE_EFFECTRETURN
PLY_AKG_EFFECT_PITCHTABLESTOP: ld -28(iy),#183
    jp PLY_AKG_CHANNEL_RE_EFFECTRETURN
PLY_AKG_PERIODTABLE: .dw 6778
    .dw 6398
    .dw 6039
    .dw 5700
    .dw 5380
    .dw 5078
    .dw 4793
    .dw 4524
    .dw 4270
    .dw 4030
    .dw 3804
    .dw 3591
    .dw 3389
    .dw 3199
    .dw 3019
    .dw 2850
    .dw 2690
    .dw 2539
    .dw 2397
    .dw 2262
    .dw 2135
    .dw 2015
    .dw 1902
    .dw 1795
    .dw 1695
    .dw 1599
    .dw 1510
    .dw 1425
    .dw 1345
    .dw 1270
    .dw 1198
    .dw 1131
    .dw 1068
    .dw 1008
    .dw 951
    .dw 898
    .dw 847
    .dw 800
    .dw 755
    .dw 712
    .dw 673
    .dw 635
    .dw 599
    .dw 566
    .dw 534
    .dw 504
    .dw 476
    .dw 449
    .dw 424
    .dw 400
    .dw 377
    .dw 356
    .dw 336
    .dw 317
    .dw 300
    .dw 283
    .dw 267
    .dw 252
    .dw 238
    .dw 224
    .dw 212
    .dw 200
    .dw 189
    .dw 178
    .dw 168
    .dw 159
    .dw 150
    .dw 141
    .dw 133
    .dw 126
    .dw 119
    .dw 112
    .dw 106
    .dw 100
    .dw 94
    .dw 89
    .dw 84
    .dw 79
    .dw 75
    .dw 71
    .dw 67
    .dw 63
    .dw 59
    .dw 56
    .dw 53
    .dw 50
    .dw 47
    .dw 45
    .dw 42
    .dw 40
    .dw 37
    .dw 35
    .dw 33
    .dw 31
    .dw 30
    .dw 28
    .dw 26
    .dw 25
    .dw 24
    .dw 22
    .dw 21
    .dw 20
    .dw 19
    .dw 18
    .dw 17
    .dw 16
    .dw 15
    .dw 14
    .dw 13
    .dw 12
    .dw 12
    .dw 11
    .dw 11
    .dw 10
    .dw 9
    .dw 9
    .dw 8
    .dw 8
    .dw 7
    .dw 7
    .dw 7
    .dw 6
    .dw 6
    .dw 6
    .dw 5
    .dw 5
    .dw 5
    .dw 4
