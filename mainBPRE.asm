.gba
.thumb
.open "BPRE.gba","build/rom_BPRE.gba", 0x08000000
//---------------------------------------------------

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

.close

