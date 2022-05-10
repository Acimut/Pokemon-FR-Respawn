.gba
.thumb
.open "BPRE.gba","build/rom_BPRE.gba", 0x08000000
//---------------------------------------------------

/*
//080800d0 l 0000003e IsPlayerDefeated
.org 0x080800EC
    .word RutiJavi_modificada

.org 0x080800F0
    .word RutiJavi_modificada
*/

//080566a4 g 00000078 CB2_WhiteOut
.org 0x080566a4
.area 0x78, 0xFF
    push {lr}
    ldr r3, = CB2_WhiteOut_new|1
    bl bx_r3
    pop {lr}
bx_r3:
    bx r3
.pool
.endarea


.align 4
.org insertinto
.importobj "build/linked.o"

/*
//https://www.youtube.com/watch?v=jhePNBYDQrQ
RutiJavi_modificada:
    ldr r0, =RutinaRespawn|1
    bl bx_r0
    pop {r1}
    bx r1
bx_r0:
    bx r0

.pool
*/

.close

