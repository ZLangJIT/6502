from . import CS_OP_INVALID, CS_OP_REG, CS_OP_IMM, CS_OP_FP, CS_OP_PRED, CS_OP_SPECIAL, CS_OP_MEM, CS_OP_MEM_REG, CS_OP_MEM_IMM, UINT16_MAX, UINT8_MAX
# For Capstone Engine. AUTO-GENERATED FILE, DO NOT EDIT [tricore_const.py]
TRICORE_OP_INVALID = CS_OP_INVALID
TRICORE_OP_REG = CS_OP_REG
TRICORE_OP_IMM = CS_OP_IMM
TRICORE_OP_MEM = CS_OP_MEM

TRICORE_REG_INVALID = 0
TRICORE_REG_FCX = 1
TRICORE_REG_PC = 2
TRICORE_REG_PCXI = 3
TRICORE_REG_PSW = 4
TRICORE_REG_A0 = 5
TRICORE_REG_A1 = 6
TRICORE_REG_A2 = 7
TRICORE_REG_A3 = 8
TRICORE_REG_A4 = 9
TRICORE_REG_A5 = 10
TRICORE_REG_A6 = 11
TRICORE_REG_A7 = 12
TRICORE_REG_A8 = 13
TRICORE_REG_A9 = 14
TRICORE_REG_A10 = 15
TRICORE_REG_A11 = 16
TRICORE_REG_A12 = 17
TRICORE_REG_A13 = 18
TRICORE_REG_A14 = 19
TRICORE_REG_A15 = 20
TRICORE_REG_D0 = 21
TRICORE_REG_D1 = 22
TRICORE_REG_D2 = 23
TRICORE_REG_D3 = 24
TRICORE_REG_D4 = 25
TRICORE_REG_D5 = 26
TRICORE_REG_D6 = 27
TRICORE_REG_D7 = 28
TRICORE_REG_D8 = 29
TRICORE_REG_D9 = 30
TRICORE_REG_D10 = 31
TRICORE_REG_D11 = 32
TRICORE_REG_D12 = 33
TRICORE_REG_D13 = 34
TRICORE_REG_D14 = 35
TRICORE_REG_D15 = 36
TRICORE_REG_E0 = 37
TRICORE_REG_E2 = 38
TRICORE_REG_E4 = 39
TRICORE_REG_E6 = 40
TRICORE_REG_E8 = 41
TRICORE_REG_E10 = 42
TRICORE_REG_E12 = 43
TRICORE_REG_E14 = 44
TRICORE_REG_P0 = 45
TRICORE_REG_P2 = 46
TRICORE_REG_P4 = 47
TRICORE_REG_P6 = 48
TRICORE_REG_P8 = 49
TRICORE_REG_P10 = 50
TRICORE_REG_P12 = 51
TRICORE_REG_P14 = 52
TRICORE_REG_A0_A1 = 53
TRICORE_REG_A2_A3 = 54
TRICORE_REG_A4_A5 = 55
TRICORE_REG_A6_A7 = 56
TRICORE_REG_A8_A9 = 57
TRICORE_REG_A10_A11 = 58
TRICORE_REG_A12_A13 = 59
TRICORE_REG_A14_A15 = 60
TRICORE_REG_ENDING = 61

TRICORE_INS_INVALID = 0
TRICORE_INS_ABSDIFS_B = 1
TRICORE_INS_ABSDIFS_H = 2
TRICORE_INS_ABSDIFS = 3
TRICORE_INS_ABSDIF_B = 4
TRICORE_INS_ABSDIF_H = 5
TRICORE_INS_ABSDIF = 6
TRICORE_INS_ABSS_B = 7
TRICORE_INS_ABSS_H = 8
TRICORE_INS_ABSS = 9
TRICORE_INS_ABS_B = 10
TRICORE_INS_ABS_H = 11
TRICORE_INS_ABS = 12
TRICORE_INS_ADDC = 13
TRICORE_INS_ADDIH_A = 14
TRICORE_INS_ADDIH = 15
TRICORE_INS_ADDI = 16
TRICORE_INS_ADDSC_AT = 17
TRICORE_INS_ADDSC_A = 18
TRICORE_INS_ADDS_BU = 19
TRICORE_INS_ADDS_B = 20
TRICORE_INS_ADDS_H = 21
TRICORE_INS_ADDS_HU = 22
TRICORE_INS_ADDS_U = 23
TRICORE_INS_ADDS = 24
TRICORE_INS_ADDX = 25
TRICORE_INS_ADD_A = 26
TRICORE_INS_ADD_B = 27
TRICORE_INS_ADD_F = 28
TRICORE_INS_ADD_H = 29
TRICORE_INS_ADD = 30
TRICORE_INS_ANDN_T = 31
TRICORE_INS_ANDN = 32
TRICORE_INS_AND_ANDN_T = 33
TRICORE_INS_AND_AND_T = 34
TRICORE_INS_AND_EQ = 35
TRICORE_INS_AND_GE_U = 36
TRICORE_INS_AND_GE = 37
TRICORE_INS_AND_LT_U = 38
TRICORE_INS_AND_LT = 39
TRICORE_INS_AND_NE = 40
TRICORE_INS_AND_NOR_T = 41
TRICORE_INS_AND_OR_T = 42
TRICORE_INS_AND_T = 43
TRICORE_INS_AND = 44
TRICORE_INS_BISR = 45
TRICORE_INS_BMERGE = 46
TRICORE_INS_BSPLIT = 47
TRICORE_INS_CACHEA_I = 48
TRICORE_INS_CACHEA_WI = 49
TRICORE_INS_CACHEA_W = 50
TRICORE_INS_CACHEI_I = 51
TRICORE_INS_CACHEI_WI = 52
TRICORE_INS_CACHEI_W = 53
TRICORE_INS_CADDN_A = 54
TRICORE_INS_CADDN = 55
TRICORE_INS_CADD_A = 56
TRICORE_INS_CADD = 57
TRICORE_INS_CALLA = 58
TRICORE_INS_CALLI = 59
TRICORE_INS_CALL = 60
TRICORE_INS_CLO_B = 61
TRICORE_INS_CLO_H = 62
TRICORE_INS_CLO = 63
TRICORE_INS_CLS_B = 64
TRICORE_INS_CLS_H = 65
TRICORE_INS_CLS = 66
TRICORE_INS_CLZ_B = 67
TRICORE_INS_CLZ_H = 68
TRICORE_INS_CLZ = 69
TRICORE_INS_CMOVN = 70
TRICORE_INS_CMOV = 71
TRICORE_INS_CMPSWAP_W = 72
TRICORE_INS_CMP_F = 73
TRICORE_INS_CRC32B_W = 74
TRICORE_INS_CRC32L_W = 75
TRICORE_INS_CRC32_B = 76
TRICORE_INS_CRCN = 77
TRICORE_INS_CSUBN_A = 78
TRICORE_INS_CSUBN = 79
TRICORE_INS_CSUB_A = 80
TRICORE_INS_CSUB = 81
TRICORE_INS_DEBUG = 82
TRICORE_INS_DEXTR = 83
TRICORE_INS_DIFSC_A = 84
TRICORE_INS_DISABLE = 85
TRICORE_INS_DIV_F = 86
TRICORE_INS_DIV_U = 87
TRICORE_INS_DIV = 88
TRICORE_INS_DSYNC = 89
TRICORE_INS_DVADJ = 90
TRICORE_INS_DVINIT_BU = 91
TRICORE_INS_DVINIT_B = 92
TRICORE_INS_DVINIT_HU = 93
TRICORE_INS_DVINIT_H = 94
TRICORE_INS_DVINIT_U = 95
TRICORE_INS_DVINIT = 96
TRICORE_INS_DVSTEP_U = 97
TRICORE_INS_DVSTEP = 98
TRICORE_INS_ENABLE = 99
TRICORE_INS_EQANY_B = 100
TRICORE_INS_EQANY_H = 101
TRICORE_INS_EQZ_A = 102
TRICORE_INS_EQ_A = 103
TRICORE_INS_EQ_B = 104
TRICORE_INS_EQ_H = 105
TRICORE_INS_EQ_W = 106
TRICORE_INS_EQ = 107
TRICORE_INS_EXTR_U = 108
TRICORE_INS_EXTR = 109
TRICORE_INS_FCALLA = 110
TRICORE_INS_FCALLI = 111
TRICORE_INS_FCALL = 112
TRICORE_INS_FRET = 113
TRICORE_INS_FTOHP = 114
TRICORE_INS_FTOIZ = 115
TRICORE_INS_FTOI = 116
TRICORE_INS_FTOQ31Z = 117
TRICORE_INS_FTOQ31 = 118
TRICORE_INS_FTOUZ = 119
TRICORE_INS_FTOU = 120
TRICORE_INS_GE_A = 121
TRICORE_INS_GE_U = 122
TRICORE_INS_GE = 123
TRICORE_INS_HPTOF = 124
TRICORE_INS_IMASK = 125
TRICORE_INS_INSERT = 126
TRICORE_INS_INSN_T = 127
TRICORE_INS_INS_T = 128
TRICORE_INS_ISYNC = 129
TRICORE_INS_ITOF = 130
TRICORE_INS_IXMAX_U = 131
TRICORE_INS_IXMAX = 132
TRICORE_INS_IXMIN_U = 133
TRICORE_INS_IXMIN = 134
TRICORE_INS_JA = 135
TRICORE_INS_JEQ_A = 136
TRICORE_INS_JEQ = 137
TRICORE_INS_JGEZ = 138
TRICORE_INS_JGE_U = 139
TRICORE_INS_JGE = 140
TRICORE_INS_JGTZ = 141
TRICORE_INS_JI = 142
TRICORE_INS_JLA = 143
TRICORE_INS_JLEZ = 144
TRICORE_INS_JLI = 145
TRICORE_INS_JLTZ = 146
TRICORE_INS_JLT_U = 147
TRICORE_INS_JLT = 148
TRICORE_INS_JL = 149
TRICORE_INS_JNED = 150
TRICORE_INS_JNEI = 151
TRICORE_INS_JNE_A = 152
TRICORE_INS_JNE = 153
TRICORE_INS_JNZ_A = 154
TRICORE_INS_JNZ_T = 155
TRICORE_INS_JNZ = 156
TRICORE_INS_JZ_A = 157
TRICORE_INS_JZ_T = 158
TRICORE_INS_JZ = 159
TRICORE_INS_J = 160
TRICORE_INS_LDLCX = 161
TRICORE_INS_LDMST = 162
TRICORE_INS_LDUCX = 163
TRICORE_INS_LD_A = 164
TRICORE_INS_LD_BU = 165
TRICORE_INS_LD_B = 166
TRICORE_INS_LD_DA = 167
TRICORE_INS_LD_D = 168
TRICORE_INS_LD_HU = 169
TRICORE_INS_LD_H = 170
TRICORE_INS_LD_Q = 171
TRICORE_INS_LD_W = 172
TRICORE_INS_LEA = 173
TRICORE_INS_LHA = 174
TRICORE_INS_LOOPU = 175
TRICORE_INS_LOOP = 176
TRICORE_INS_LT_A = 177
TRICORE_INS_LT_B = 178
TRICORE_INS_LT_BU = 179
TRICORE_INS_LT_H = 180
TRICORE_INS_LT_HU = 181
TRICORE_INS_LT_U = 182
TRICORE_INS_LT_W = 183
TRICORE_INS_LT_WU = 184
TRICORE_INS_LT = 185
TRICORE_INS_MADDMS_H = 186
TRICORE_INS_MADDMS_U = 187
TRICORE_INS_MADDMS = 188
TRICORE_INS_MADDM_H = 189
TRICORE_INS_MADDM_Q = 190
TRICORE_INS_MADDM_U = 191
TRICORE_INS_MADDM = 192
TRICORE_INS_MADDRS_H = 193
TRICORE_INS_MADDRS_Q = 194
TRICORE_INS_MADDR_H = 195
TRICORE_INS_MADDR_Q = 196
TRICORE_INS_MADDSUMS_H = 197
TRICORE_INS_MADDSUM_H = 198
TRICORE_INS_MADDSURS_H = 199
TRICORE_INS_MADDSUR_H = 200
TRICORE_INS_MADDSUS_H = 201
TRICORE_INS_MADDSU_H = 202
TRICORE_INS_MADDS_H = 203
TRICORE_INS_MADDS_Q = 204
TRICORE_INS_MADDS_U = 205
TRICORE_INS_MADDS = 206
TRICORE_INS_MADD_F = 207
TRICORE_INS_MADD_H = 208
TRICORE_INS_MADD_Q = 209
TRICORE_INS_MADD_U = 210
TRICORE_INS_MADD = 211
TRICORE_INS_MAX_B = 212
TRICORE_INS_MAX_BU = 213
TRICORE_INS_MAX_H = 214
TRICORE_INS_MAX_HU = 215
TRICORE_INS_MAX_U = 216
TRICORE_INS_MAX = 217
TRICORE_INS_MFCR = 218
TRICORE_INS_MIN_B = 219
TRICORE_INS_MIN_BU = 220
TRICORE_INS_MIN_H = 221
TRICORE_INS_MIN_HU = 222
TRICORE_INS_MIN_U = 223
TRICORE_INS_MIN = 224
TRICORE_INS_MOVH_A = 225
TRICORE_INS_MOVH = 226
TRICORE_INS_MOVZ_A = 227
TRICORE_INS_MOV_AA = 228
TRICORE_INS_MOV_A = 229
TRICORE_INS_MOV_D = 230
TRICORE_INS_MOV_U = 231
TRICORE_INS_MOV = 232
TRICORE_INS_MSUBADMS_H = 233
TRICORE_INS_MSUBADM_H = 234
TRICORE_INS_MSUBADRS_H = 235
TRICORE_INS_MSUBADR_H = 236
TRICORE_INS_MSUBADS_H = 237
TRICORE_INS_MSUBAD_H = 238
TRICORE_INS_MSUBMS_H = 239
TRICORE_INS_MSUBMS_U = 240
TRICORE_INS_MSUBMS = 241
TRICORE_INS_MSUBM_H = 242
TRICORE_INS_MSUBM_Q = 243
TRICORE_INS_MSUBM_U = 244
TRICORE_INS_MSUBM = 245
TRICORE_INS_MSUBRS_H = 246
TRICORE_INS_MSUBRS_Q = 247
TRICORE_INS_MSUBR_H = 248
TRICORE_INS_MSUBR_Q = 249
TRICORE_INS_MSUBS_H = 250
TRICORE_INS_MSUBS_Q = 251
TRICORE_INS_MSUBS_U = 252
TRICORE_INS_MSUBS = 253
TRICORE_INS_MSUB_F = 254
TRICORE_INS_MSUB_H = 255
TRICORE_INS_MSUB_Q = 256
TRICORE_INS_MSUB_U = 257
TRICORE_INS_MSUB = 258
TRICORE_INS_MTCR = 259
TRICORE_INS_MULMS_H = 260
TRICORE_INS_MULM_H = 261
TRICORE_INS_MULM_U = 262
TRICORE_INS_MULM = 263
TRICORE_INS_MULR_H = 264
TRICORE_INS_MULR_Q = 265
TRICORE_INS_MULS_U = 266
TRICORE_INS_MULS = 267
TRICORE_INS_MUL_F = 268
TRICORE_INS_MUL_H = 269
TRICORE_INS_MUL_Q = 270
TRICORE_INS_MUL_U = 271
TRICORE_INS_MUL = 272
TRICORE_INS_NAND_T = 273
TRICORE_INS_NAND = 274
TRICORE_INS_NEZ_A = 275
TRICORE_INS_NE_A = 276
TRICORE_INS_NE = 277
TRICORE_INS_NOP = 278
TRICORE_INS_NOR_T = 279
TRICORE_INS_NOR = 280
TRICORE_INS_NOT = 281
TRICORE_INS_ORN_T = 282
TRICORE_INS_ORN = 283
TRICORE_INS_OR_ANDN_T = 284
TRICORE_INS_OR_AND_T = 285
TRICORE_INS_OR_EQ = 286
TRICORE_INS_OR_GE_U = 287
TRICORE_INS_OR_GE = 288
TRICORE_INS_OR_LT_U = 289
TRICORE_INS_OR_LT = 290
TRICORE_INS_OR_NE = 291
TRICORE_INS_OR_NOR_T = 292
TRICORE_INS_OR_OR_T = 293
TRICORE_INS_OR_T = 294
TRICORE_INS_OR = 295
TRICORE_INS_PACK = 296
TRICORE_INS_PARITY = 297
TRICORE_INS_POPCNT_W = 298
TRICORE_INS_Q31TOF = 299
TRICORE_INS_QSEED_F = 300
TRICORE_INS_RESTORE = 301
TRICORE_INS_RET = 302
TRICORE_INS_RFE = 303
TRICORE_INS_RFM = 304
TRICORE_INS_RSLCX = 305
TRICORE_INS_RSTV = 306
TRICORE_INS_RSUBS_U = 307
TRICORE_INS_RSUBS = 308
TRICORE_INS_RSUB = 309
TRICORE_INS_SAT_BU = 310
TRICORE_INS_SAT_B = 311
TRICORE_INS_SAT_HU = 312
TRICORE_INS_SAT_H = 313
TRICORE_INS_SELN_A = 314
TRICORE_INS_SELN = 315
TRICORE_INS_SEL_A = 316
TRICORE_INS_SEL = 317
TRICORE_INS_SHAS = 318
TRICORE_INS_SHA_B = 319
TRICORE_INS_SHA_H = 320
TRICORE_INS_SHA = 321
TRICORE_INS_SHUFFLE = 322
TRICORE_INS_SH_ANDN_T = 323
TRICORE_INS_SH_AND_T = 324
TRICORE_INS_SH_B = 325
TRICORE_INS_SH_EQ = 326
TRICORE_INS_SH_GE_U = 327
TRICORE_INS_SH_GE = 328
TRICORE_INS_SH_H = 329
TRICORE_INS_SH_LT_U = 330
TRICORE_INS_SH_LT = 331
TRICORE_INS_SH_NAND_T = 332
TRICORE_INS_SH_NE = 333
TRICORE_INS_SH_NOR_T = 334
TRICORE_INS_SH_ORN_T = 335
TRICORE_INS_SH_OR_T = 336
TRICORE_INS_SH_XNOR_T = 337
TRICORE_INS_SH_XOR_T = 338
TRICORE_INS_SH = 339
TRICORE_INS_STLCX = 340
TRICORE_INS_STUCX = 341
TRICORE_INS_ST_A = 342
TRICORE_INS_ST_B = 343
TRICORE_INS_ST_DA = 344
TRICORE_INS_ST_D = 345
TRICORE_INS_ST_H = 346
TRICORE_INS_ST_Q = 347
TRICORE_INS_ST_T = 348
TRICORE_INS_ST_W = 349
TRICORE_INS_SUBC = 350
TRICORE_INS_SUBSC_A = 351
TRICORE_INS_SUBS_BU = 352
TRICORE_INS_SUBS_B = 353
TRICORE_INS_SUBS_HU = 354
TRICORE_INS_SUBS_H = 355
TRICORE_INS_SUBS_U = 356
TRICORE_INS_SUBS = 357
TRICORE_INS_SUBX = 358
TRICORE_INS_SUB_A = 359
TRICORE_INS_SUB_B = 360
TRICORE_INS_SUB_F = 361
TRICORE_INS_SUB_H = 362
TRICORE_INS_SUB = 363
TRICORE_INS_SVLCX = 364
TRICORE_INS_SWAPMSK_W = 365
TRICORE_INS_SWAP_A = 366
TRICORE_INS_SWAP_W = 367
TRICORE_INS_SYSCALL = 368
TRICORE_INS_TLBDEMAP = 369
TRICORE_INS_TLBFLUSH_A = 370
TRICORE_INS_TLBFLUSH_B = 371
TRICORE_INS_TLBMAP = 372
TRICORE_INS_TLBPROBE_A = 373
TRICORE_INS_TLBPROBE_I = 374
TRICORE_INS_TRAPSV = 375
TRICORE_INS_TRAPV = 376
TRICORE_INS_UNPACK = 377
TRICORE_INS_UPDFL = 378
TRICORE_INS_UTOF = 379
TRICORE_INS_WAIT = 380
TRICORE_INS_XNOR_T = 381
TRICORE_INS_XNOR = 382
TRICORE_INS_XOR_EQ = 383
TRICORE_INS_XOR_GE_U = 384
TRICORE_INS_XOR_GE = 385
TRICORE_INS_XOR_LT_U = 386
TRICORE_INS_XOR_LT = 387
TRICORE_INS_XOR_NE = 388
TRICORE_INS_XOR_T = 389
TRICORE_INS_XOR = 390
TRICORE_INS_ENDING = 391

TRICORE_GRP_INVALID = 0
TRICORE_GRP_CALL = 1
TRICORE_GRP_JUMP = 2
TRICORE_GRP_ENDING = 3

TRICORE_FEATURE_INVALID = 0
TRICORE_FEATURE_HASV110 = 128
TRICORE_FEATURE_HASV120 = 129
TRICORE_FEATURE_HASV130 = 130
TRICORE_FEATURE_HASV131 = 131
TRICORE_FEATURE_HASV160 = 132
TRICORE_FEATURE_HASV161 = 133
TRICORE_FEATURE_HASV162 = 134
TRICORE_FEATURE_HASV120_UP = 135
TRICORE_FEATURE_HASV130_UP = 136
TRICORE_FEATURE_HASV131_UP = 137
TRICORE_FEATURE_HASV160_UP = 138
TRICORE_FEATURE_HASV161_UP = 139
TRICORE_FEATURE_HASV162_UP = 140
TRICORE_FEATURE_HASV120_DN = 141
TRICORE_FEATURE_HASV130_DN = 142
TRICORE_FEATURE_HASV131_DN = 143
TRICORE_FEATURE_HASV160_DN = 144
TRICORE_FEATURE_HASV161_DN = 145
TRICORE_FEATURE_HASV162_DN = 146
TRICORE_FEATURE_ENDING = 147