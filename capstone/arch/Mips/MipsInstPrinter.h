#include "../../SStream.h"
#include "../../MCInst.h"
/* Capstone Disassembly Engine, http://www.capstone-engine.org */
/* By Nguyen Anh Quynh <aquynh@gmail.com>, 2013-2022, */
/*    Rot127 <unisono@quyllur.org> 2022-2023 */
/* Automatically translated source file from LLVM. */

/* LLVM-commit: <commit> */
/* LLVM-tag: <tag> */

/* Only small edits allowed. */
/* For multiple similar edits, please create a Patch for the translator. */

/* Capstone's C++ file translator: */
/* https://github.com/capstone-engine/capstone/tree/next/suite/auto-sync */

//=== MipsInstPrinter.h - Convert Mips MCInst to assembly syntax -*- C++ -*-==//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This class prints a Mips MCInst to a .s file.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_MIPS_MCTARGETDESC_MIPSINSTPRINTER_H
#define LLVM_LIB_TARGET_MIPS_MCTARGETDESC_MIPSINSTPRINTER_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <capstone/platform.h>

#include "../../MCInstPrinter.h"
#include "../../cs_priv.h"
#define CONCAT(a, b) CONCAT_(a, b)
#define CONCAT_(a, b) a##_##b

// These enumeration declarations were originally in MipsInstrInfo.h but
// had to be moved here to avoid circular dependencies between
// LLVMMipsCodeGen and LLVMMipsAsmPrinter.
// CS namespace begin: Mips

// Mips Branch Codes
typedef enum MipsFPBranchCode {
	Mips_BRANCH_F,
	Mips_BRANCH_T,
	Mips_BRANCH_FL,
	Mips_BRANCH_TL,
	Mips_BRANCH_INVALID
} Mips_FPBranchCode;

// Mips Condition Codes
typedef enum MipsCondCode {
	// To be used with float branch True
	Mips_FCOND_F,
	Mips_FCOND_UN,
	Mips_FCOND_OEQ,
	Mips_FCOND_UEQ,
	Mips_FCOND_OLT,
	Mips_FCOND_ULT,
	Mips_FCOND_OLE,
	Mips_FCOND_ULE,
	Mips_FCOND_SF,
	Mips_FCOND_NGLE,
	Mips_FCOND_SEQ,
	Mips_FCOND_NGL,
	Mips_FCOND_LT,
	Mips_FCOND_NGE,
	Mips_FCOND_LE,
	Mips_FCOND_NGT,

	// To be used with float branch False
	// This conditions have the same mnemonic as the
	// above ones, but are used with a branch False;
	Mips_FCOND_T,
	Mips_FCOND_OR,
	Mips_FCOND_UNE,
	Mips_FCOND_ONE,
	Mips_FCOND_UGE,
	Mips_FCOND_OGE,
	Mips_FCOND_UGT,
	Mips_FCOND_OGT,
	Mips_FCOND_ST,
	Mips_FCOND_GLE,
	Mips_FCOND_SNE,
	Mips_FCOND_GL,
	Mips_FCOND_NLT,
	Mips_FCOND_GE,
	Mips_FCOND_NLE,
	Mips_FCOND_GT
} Mips_CondCode;

static const char *MipsFCCToString(Mips_CondCode CC);

// CS namespace end: Mips

// end namespace Mips

// Autogenerated by tblgen.
static const char *getRegisterName(unsigned RegNo);
static void printInstruction(MCInst *MI, uint64_t Address, SStream *O);
static bool printAliasInstr(MCInst *MI, uint64_t Address, SStream *OS);
static void printCustomAliasOperand(MCInst *MI, uint64_t Address, unsigned OpIdx,
			     unsigned PrintMethodIdx, SStream *O);
static void printOperand(MCInst *MI, unsigned OpNo, SStream *O);
static void printJumpOperand(MCInst *MI, unsigned OpNo, SStream *O);
static void printBranchOperand(MCInst *MI, uint64_t Address, unsigned OpNo,
			SStream *O);

#define DECLARE_printUImm_2(Bits, Offset) \
	static void CONCAT(printUImm, CONCAT(Bits, Offset))( \
		MCInst *MI, int opNum, SStream *O)
#define DECLARE_printUImm(Bits) \
	static void CONCAT(printUImm, CONCAT(Bits, 0))( \
		MCInst *MI, int opNum, SStream *O)
DECLARE_printUImm(0);
DECLARE_printUImm(1);
DECLARE_printUImm(10);
DECLARE_printUImm(12);
DECLARE_printUImm(16);
DECLARE_printUImm(2);
DECLARE_printUImm(20);
DECLARE_printUImm(26);
DECLARE_printUImm(3);
DECLARE_printUImm(32);
DECLARE_printUImm(4);
DECLARE_printUImm(5);
DECLARE_printUImm(6);
DECLARE_printUImm(7);
DECLARE_printUImm(8);
DECLARE_printUImm_2(2, 1);
DECLARE_printUImm_2(5, 1);
DECLARE_printUImm_2(5, 32);
DECLARE_printUImm_2(5, 33);
DECLARE_printUImm_2(6, 1);
DECLARE_printUImm_2(6, 2);

static void printMemOperand(MCInst *MI, int opNum, SStream *O);
static void printMemOperandEA(MCInst *MI, int opNum, SStream *O);
static void printFCCOperand(MCInst *MI, int opNum, SStream *O);
static bool printAlias(const char *Str, const MCInst *MI, uint64_t Address,
		unsigned OpNo, SStream *OS, bool IsBranch);
static bool printAlias2(const char *Str, const MCInst *MI, uint64_t Address,
		unsigned OpNo0, unsigned OpNo1, SStream *OS,
		bool IsBranch);
static bool printAlias3(const char *Str, const MCInst *MI, uint64_t Address,
		unsigned OpNo0, unsigned OpNo1, unsigned OpNo2, SStream *OS);
static bool printAlias4(const MCInst *MI, uint64_t Address, SStream *OS);
static void printRegisterList(MCInst *MI, int opNum, SStream *O);
static void printNanoMipsRegisterList(MCInst *MI, int opNum, SStream *O);
static void printHi20(MCInst *MI, int OpNum, SStream *O);
static void printHi20PCRel(MCInst *MI, uint64_t Address, int OpNum, SStream *O);
static void printPCRel(MCInst *MI, uint64_t Address, int OpNum, SStream *O);

#endif