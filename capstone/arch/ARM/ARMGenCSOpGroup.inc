/* Capstone Disassembly Engine, https://www.capstone-engine.org */
/* By Nguyen Anh Quynh <aquynh@gmail.com>, 2013-2022, */
/*    Rot127 <unisono@quyllur.org> 2022-2024 */
/* Automatically generated file by Capstone's LLVM TableGen Disassembler Backend. */

/* LLVM-commit: <commit> */
/* LLVM-tag: <tag> */

/* Do not edit. */

/* Capstone's LLVM TableGen Backends: */
/* https://github.com/capstone-engine/llvm-capstone */

  ARM_OP_GROUP_LdStmModeOperand = 0,
  ARM_OP_GROUP_MandatoryInvertedPredicateOperand = 1,
  ARM_OP_GROUP_RegImmShift = 2,
  ARM_OP_GROUP_Operand = 3,
  ARM_OP_GROUP_ModImmOperand = 4,
  ARM_OP_GROUP_PredicateOperand = 5,
  ARM_OP_GROUP_SORegImmOperand = 6,
  ARM_OP_GROUP_SORegRegOperand = 7,
  ARM_OP_GROUP_SBitModifierOperand = 8,
  ARM_OP_GROUP_AddrModeImm12Operand_0 = 9,
  ARM_OP_GROUP_AddrMode2Operand = 10,
  ARM_OP_GROUP_CPInstOperand = 11,
  ARM_OP_GROUP_MandatoryPredicateOperand = 12,
  ARM_OP_GROUP_ThumbITMask = 13,
  ARM_OP_GROUP_RegisterList = 14,
  ARM_OP_GROUP_AddrMode7Operand = 15,
  ARM_OP_GROUP_GPRPairOperand = 16,
  ARM_OP_GROUP_AddrMode3Operand_0 = 17,
  ARM_OP_GROUP_PCLabel = 18,
  ARM_OP_GROUP_AddrModePCOperand = 19,
  ARM_OP_GROUP_AddrMode2OffsetOperand = 20,
  ARM_OP_GROUP_AddrMode3OffsetOperand = 21,
  ARM_OP_GROUP_AddrMode6Operand = 22,
  ARM_OP_GROUP_VectorListThreeAllLanes = 23,
  ARM_OP_GROUP_VectorListThreeSpacedAllLanes = 24,
  ARM_OP_GROUP_VectorListThree = 25,
  ARM_OP_GROUP_VectorListThreeSpaced = 26,
  ARM_OP_GROUP_VectorListFourAllLanes = 27,
  ARM_OP_GROUP_VectorListFourSpacedAllLanes = 28,
  ARM_OP_GROUP_VectorListFour = 29,
  ARM_OP_GROUP_VectorListFourSpaced = 30,
  ARM_OP_GROUP_T2SOOperand = 31,
  ARM_OP_GROUP_T2AddrModeImm8Operand_0 = 32,
  ARM_OP_GROUP_T2AddrModeImm8OffsetOperand = 33,
  ARM_OP_GROUP_T2AddrModeImm8Operand_1 = 34,
  ARM_OP_GROUP_AdrLabelOperand_0 = 35,
  ARM_OP_GROUP_VectorIndex = 36,
  ARM_OP_GROUP_BitfieldInvMaskImmOperand = 37,
  ARM_OP_GROUP_PImmediate = 38,
  ARM_OP_GROUP_VPTPredicateOperand = 39,
  ARM_OP_GROUP_CImmediate = 40,
  ARM_OP_GROUP_CPSIMod = 41,
  ARM_OP_GROUP_CPSIFlag = 42,
  ARM_OP_GROUP_MemBOption = 43,
  ARM_OP_GROUP_FPImmOperand = 44,
  ARM_OP_GROUP_InstSyncBOption = 45,
  ARM_OP_GROUP_AddrMode5Operand_0 = 46,
  ARM_OP_GROUP_CoprocOptionImm = 47,
  ARM_OP_GROUP_PostIdxImm8s4Operand = 48,
  ARM_OP_GROUP_AddrMode5Operand_1 = 49,
  ARM_OP_GROUP_AddrModeImm12Operand_1 = 50,
  ARM_OP_GROUP_AddrMode3Operand_1 = 51,
  ARM_OP_GROUP_PostIdxImm8Operand = 52,
  ARM_OP_GROUP_PostIdxRegOperand = 53,
  ARM_OP_GROUP_BankedRegOperand = 54,
  ARM_OP_GROUP_MSRMaskOperand = 55,
  ARM_OP_GROUP_MveSaturateOp = 56,
  ARM_OP_GROUP_VMOVModImmOperand = 57,
  ARM_OP_GROUP_ComplexRotationOp_180_90 = 58,
  ARM_OP_GROUP_ComplexRotationOp_90_0 = 59,
  ARM_OP_GROUP_MandatoryRestrictedPredicateOperand = 60,
  ARM_OP_GROUP_MVEVectorList_2 = 61,
  ARM_OP_GROUP_MVEVectorList_4 = 62,
  ARM_OP_GROUP_MveAddrModeRQOperand_0 = 63,
  ARM_OP_GROUP_MveAddrModeRQOperand_3 = 64,
  ARM_OP_GROUP_MveAddrModeRQOperand_1 = 65,
  ARM_OP_GROUP_MveAddrModeRQOperand_2 = 66,
  ARM_OP_GROUP_VPTMask = 67,
  ARM_OP_GROUP_PKHLSLShiftImm = 68,
  ARM_OP_GROUP_PKHASRShiftImm = 69,
  ARM_OP_GROUP_ImmPlusOneOperand = 70,
  ARM_OP_GROUP_SetendOperand = 71,
  ARM_OP_GROUP_ShiftImmOperand = 72,
  ARM_OP_GROUP_RotImmOperand = 73,
  ARM_OP_GROUP_TraceSyncBOption = 74,
  ARM_OP_GROUP_VectorListOneAllLanes = 75,
  ARM_OP_GROUP_VectorListTwoAllLanes = 76,
  ARM_OP_GROUP_NoHashImmediate = 77,
  ARM_OP_GROUP_AddrMode6OffsetOperand = 78,
  ARM_OP_GROUP_VectorListOne = 79,
  ARM_OP_GROUP_VectorListTwo = 80,
  ARM_OP_GROUP_VectorListTwoSpacedAllLanes = 81,
  ARM_OP_GROUP_VectorListTwoSpaced = 82,
  ARM_OP_GROUP_AddrMode5FP16Operand_0 = 83,
  ARM_OP_GROUP_T2AddrModeImm8s4Operand_0 = 84,
  ARM_OP_GROUP_T2AddrModeImm8s4OffsetOperand = 85,
  ARM_OP_GROUP_T2AddrModeImm8s4Operand_1 = 86,
  ARM_OP_GROUP_FBits16 = 87,
  ARM_OP_GROUP_FBits32 = 88,
  ARM_OP_GROUP_ThumbSRImm = 89,
  ARM_OP_GROUP_ThumbLdrLabelOperand = 90,
  ARM_OP_GROUP_T2AddrModeSoRegOperand = 91,
  ARM_OP_GROUP_T2AddrModeImm0_1020s4Operand = 92,
  ARM_OP_GROUP_AddrModeTBB = 93,
  ARM_OP_GROUP_AddrModeTBH = 94,
  ARM_OP_GROUP_ThumbS4ImmOperand = 95,
  ARM_OP_GROUP_AdrLabelOperand_2 = 96,
  ARM_OP_GROUP_ThumbAddrModeImm5S1Operand = 97,
  ARM_OP_GROUP_ThumbAddrModeRROperand = 98,
  ARM_OP_GROUP_ThumbAddrModeImm5S2Operand = 99,
  ARM_OP_GROUP_ThumbAddrModeImm5S4Operand = 100,
  ARM_OP_GROUP_ThumbAddrModeSPOperand = 101,