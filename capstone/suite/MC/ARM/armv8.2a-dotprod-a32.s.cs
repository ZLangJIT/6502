# CS_ARCH_ARM, CS_MODE_ARM, None
0x12,0x0d,0x21,0xfc = vudot.u8 d0, d1, d2
0x02,0x0d,0x21,0xfc = vsdot.s8 d0, d1, d2
0x58,0x0d,0x22,0xfc = vudot.u8 q0, q1, q4
0x48,0x0d,0x22,0xfc = vsdot.s8 q0, q1, q4
0x12,0x0d,0x21,0xfe = vudot.u8 d0, d1, d2[0]
0x22,0x0d,0x21,0xfe = vsdot.s8 d0, d1, d2[1]
0x54,0x0d,0x22,0xfe = vudot.u8 q0, q1, d4[0]
0x64,0x0d,0x22,0xfe = vsdot.s8 q0, q1, d4[1]