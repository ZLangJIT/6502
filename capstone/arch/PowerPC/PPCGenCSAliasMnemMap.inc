/* Capstone Disassembly Engine, https://www.capstone-engine.org */
/* By Nguyen Anh Quynh <aquynh@gmail.com>, 2013-2022, */
/*    Rot127 <unisono@quyllur.org> 2022-2024 */
/* Automatically generated file by Capstone's LLVM TableGen Disassembler Backend. */

/* LLVM-commit: <commit> */
/* LLVM-tag: <tag> */

/* Do not edit. */

/* Capstone's LLVM TableGen Backends: */
/* https://github.com/capstone-engine/llvm-capstone */

	{ PPC_INS_ALIAS_RFEBB, "rfebb" },
	{ PPC_INS_ALIAS_LI, "li" },
	{ PPC_INS_ALIAS_LIS, "lis" },
	{ PPC_INS_ALIAS_MR, "mr" },
	{ PPC_INS_ALIAS_MR_, "mr." },
	{ PPC_INS_ALIAS_NOT, "not" },
	{ PPC_INS_ALIAS_NOT_, "not." },
	{ PPC_INS_ALIAS_NOP, "nop" },
	{ PPC_INS_ALIAS_MTUDSCR, "mtudscr" },
	{ PPC_INS_ALIAS_MFUDSCR, "mfudscr" },
	{ PPC_INS_ALIAS_MTVRSAVE, "mtvrsave" },
	{ PPC_INS_ALIAS_MFVRSAVE, "mfvrsave" },
	{ PPC_INS_ALIAS_MTCR, "mtcr" },
	{ PPC_INS_ALIAS_SUB, "sub" },
	{ PPC_INS_ALIAS_SUB_, "sub." },
	{ PPC_INS_ALIAS_SUBC, "subc" },
	{ PPC_INS_ALIAS_SUBC_, "subc." },
	{ PPC_INS_ALIAS_VMR, "vmr" },
	{ PPC_INS_ALIAS_VNOT, "vnot" },
	{ PPC_INS_ALIAS_ROTLWI, "rotlwi" },
	{ PPC_INS_ALIAS_ROTLWI_, "rotlwi." },
	{ PPC_INS_ALIAS_ROTLW, "rotlw" },
	{ PPC_INS_ALIAS_ROTLW_, "rotlw." },
	{ PPC_INS_ALIAS_CLRLWI, "clrlwi" },
	{ PPC_INS_ALIAS_CLRLWI_, "clrlwi." },
	{ PPC_INS_ALIAS_ISELLT, "isellt" },
	{ PPC_INS_ALIAS_ISELGT, "iselgt" },
	{ PPC_INS_ALIAS_ISELEQ, "iseleq" },
	{ PPC_INS_ALIAS_XNOP, "xnop" },
	{ PPC_INS_ALIAS_CNTLZW, "cntlzw" },
	{ PPC_INS_ALIAS_CNTLZW_, "cntlzw." },
	{ PPC_INS_ALIAS_MTXER, "mtxer" },
	{ PPC_INS_ALIAS_MFXER, "mfxer" },
	{ PPC_INS_ALIAS_MFRTCU, "mfrtcu" },
	{ PPC_INS_ALIAS_MFRTCL, "mfrtcl" },
	{ PPC_INS_ALIAS_MTLR, "mtlr" },
	{ PPC_INS_ALIAS_MFLR, "mflr" },
	{ PPC_INS_ALIAS_MTCTR, "mtctr" },
	{ PPC_INS_ALIAS_MFCTR, "mfctr" },
	{ PPC_INS_ALIAS_MTUAMR, "mtuamr" },
	{ PPC_INS_ALIAS_MFUAMR, "mfuamr" },
	{ PPC_INS_ALIAS_MTDSCR, "mtdscr" },
	{ PPC_INS_ALIAS_MFDSCR, "mfdscr" },
	{ PPC_INS_ALIAS_MTDSISR, "mtdsisr" },
	{ PPC_INS_ALIAS_MFDSISR, "mfdsisr" },
	{ PPC_INS_ALIAS_MTDAR, "mtdar" },
	{ PPC_INS_ALIAS_MFDAR, "mfdar" },
	{ PPC_INS_ALIAS_MTDEC, "mtdec" },
	{ PPC_INS_ALIAS_MFDEC, "mfdec" },
	{ PPC_INS_ALIAS_MTSDR1, "mtsdr1" },
	{ PPC_INS_ALIAS_MFSDR1, "mfsdr1" },
	{ PPC_INS_ALIAS_MTSRR0, "mtsrr0" },
	{ PPC_INS_ALIAS_MFSRR0, "mfsrr0" },
	{ PPC_INS_ALIAS_MTSRR1, "mtsrr1" },
	{ PPC_INS_ALIAS_MFSRR1, "mfsrr1" },
	{ PPC_INS_ALIAS_MTCFAR, "mtcfar" },
	{ PPC_INS_ALIAS_MFCFAR, "mfcfar" },
	{ PPC_INS_ALIAS_MTAMR, "mtamr" },
	{ PPC_INS_ALIAS_MFAMR, "mfamr" },
	{ PPC_INS_ALIAS_MFSPRG, "mfsprg" },
	{ PPC_INS_ALIAS_MFSPRG0, "mfsprg0" },
	{ PPC_INS_ALIAS_MTSPRG, "mtsprg" },
	{ PPC_INS_ALIAS_MTSPRG0, "mtsprg0" },
	{ PPC_INS_ALIAS_MFSPRG1, "mfsprg1" },
	{ PPC_INS_ALIAS_MTSPRG1, "mtsprg1" },
	{ PPC_INS_ALIAS_MFSPRG2, "mfsprg2" },
	{ PPC_INS_ALIAS_MTSPRG2, "mtsprg2" },
	{ PPC_INS_ALIAS_MFSPRG3, "mfsprg3" },
	{ PPC_INS_ALIAS_MTSPRG3, "mtsprg3" },
	{ PPC_INS_ALIAS_MFASR, "mfasr" },
	{ PPC_INS_ALIAS_MTASR, "mtasr" },
	{ PPC_INS_ALIAS_MTTBL, "mttbl" },
	{ PPC_INS_ALIAS_MTTBU, "mttbu" },
	{ PPC_INS_ALIAS_MFPVR, "mfpvr" },
	{ PPC_INS_ALIAS_MFSPEFSCR, "mfspefscr" },
	{ PPC_INS_ALIAS_MTSPEFSCR, "mtspefscr" },
	{ PPC_INS_ALIAS_XVMOVDP, "xvmovdp" },
	{ PPC_INS_ALIAS_XVMOVSP, "xvmovsp" },
	{ PPC_INS_ALIAS_XXSPLTD, "xxspltd" },
	{ PPC_INS_ALIAS_XXMRGHD, "xxmrghd" },
	{ PPC_INS_ALIAS_XXMRGLD, "xxmrgld" },
	{ PPC_INS_ALIAS_XXSWAPD, "xxswapd" },
	{ PPC_INS_ALIAS_MFFPRD, "mffprd" },
	{ PPC_INS_ALIAS_MTFPRD, "mtfprd" },
	{ PPC_INS_ALIAS_MFFPRWZ, "mffprwz" },
	{ PPC_INS_ALIAS_MTFPRWA, "mtfprwa" },
	{ PPC_INS_ALIAS_MTFPRWZ, "mtfprwz" },
	{ PPC_INS_ALIAS_TEND_, "tend." },
	{ PPC_INS_ALIAS_TENDALL_, "tendall." },
	{ PPC_INS_ALIAS_TSUSPEND_, "tsuspend." },
	{ PPC_INS_ALIAS_TRESUME_, "tresume." },
	{ PPC_INS_ALIAS_WAIT, "wait" },
	{ PPC_INS_ALIAS_WAITRSV, "waitrsv" },
	{ PPC_INS_ALIAS_SYNC, "sync" },
	{ PPC_INS_ALIAS_PTESYNC, "ptesync" },
	{ PPC_INS_ALIAS_PHWSYNC, "phwsync" },
	{ PPC_INS_ALIAS_PLWSYNC, "plwsync" },
	{ PPC_INS_ALIAS_STNCISYNC, "stncisync" },
	{ PPC_INS_ALIAS_STCISYNC, "stcisync" },
	{ PPC_INS_ALIAS_STSYNC, "stsync" },
	{ PPC_INS_ALIAS_PADDI, "paddi" },
	{ PPC_INS_ALIAS_DCI, "dci" },
	{ PPC_INS_ALIAS_DCCCI, "dccci" },
	{ PPC_INS_ALIAS_ICI, "ici" },
	{ PPC_INS_ALIAS_ICCCI, "iccci" },
	{ PPC_INS_ALIAS_MTFSFI, "mtfsfi" },
	{ PPC_INS_ALIAS_MTFSFI_, "mtfsfi." },
	{ PPC_INS_ALIAS_MTFSF, "mtfsf" },
	{ PPC_INS_ALIAS_MTFSF_, "mtfsf." },
	{ PPC_INS_ALIAS_SC, "sc" },
	{ PPC_INS_ALIAS_LWSYNC, "lwsync" },
	{ PPC_INS_ALIAS_WAITIMPL, "waitimpl" },
	{ PPC_INS_ALIAS_MBAR, "mbar" },
	{ PPC_INS_ALIAS_CRSET, "crset" },
	{ PPC_INS_ALIAS_CRCLR, "crclr" },
	{ PPC_INS_ALIAS_CRMOVE, "crmove" },
	{ PPC_INS_ALIAS_CRNOT, "crnot" },
	{ PPC_INS_ALIAS_MFTB, "mftb" },
	{ PPC_INS_ALIAS_MFTBL, "mftbl" },
	{ PPC_INS_ALIAS_MFTBU, "mftbu" },
	{ PPC_INS_ALIAS_MFBR0, "mfbr0" },
	{ PPC_INS_ALIAS_MTBR0, "mtbr0" },
	{ PPC_INS_ALIAS_MFBR1, "mfbr1" },
	{ PPC_INS_ALIAS_MTBR1, "mtbr1" },
	{ PPC_INS_ALIAS_MFBR2, "mfbr2" },
	{ PPC_INS_ALIAS_MTBR2, "mtbr2" },
	{ PPC_INS_ALIAS_MFBR3, "mfbr3" },
	{ PPC_INS_ALIAS_MTBR3, "mtbr3" },
	{ PPC_INS_ALIAS_MFBR4, "mfbr4" },
	{ PPC_INS_ALIAS_MTBR4, "mtbr4" },
	{ PPC_INS_ALIAS_MFBR5, "mfbr5" },
	{ PPC_INS_ALIAS_MTBR5, "mtbr5" },
	{ PPC_INS_ALIAS_MFBR6, "mfbr6" },
	{ PPC_INS_ALIAS_MTBR6, "mtbr6" },
	{ PPC_INS_ALIAS_MFBR7, "mfbr7" },
	{ PPC_INS_ALIAS_MTBR7, "mtbr7" },
	{ PPC_INS_ALIAS_MTMSRD, "mtmsrd" },
	{ PPC_INS_ALIAS_MTMSR, "mtmsr" },
	{ PPC_INS_ALIAS_MTPID, "mtpid" },
	{ PPC_INS_ALIAS_MFPID, "mfpid" },
	{ PPC_INS_ALIAS_MFSPRG4, "mfsprg4" },
	{ PPC_INS_ALIAS_MTSPRG4, "mtsprg4" },
	{ PPC_INS_ALIAS_MFSPRG5, "mfsprg5" },
	{ PPC_INS_ALIAS_MTSPRG5, "mtsprg5" },
	{ PPC_INS_ALIAS_MFSPRG6, "mfsprg6" },
	{ PPC_INS_ALIAS_MTSPRG6, "mtsprg6" },
	{ PPC_INS_ALIAS_MFSPRG7, "mfsprg7" },
	{ PPC_INS_ALIAS_MTSPRG7, "mtsprg7" },
	{ PPC_INS_ALIAS_MTDBATU, "mtdbatu" },
	{ PPC_INS_ALIAS_MFDBATU, "mfdbatu" },
	{ PPC_INS_ALIAS_MTDBATL, "mtdbatl" },
	{ PPC_INS_ALIAS_MFDBATL, "mfdbatl" },
	{ PPC_INS_ALIAS_MTIBATU, "mtibatu" },
	{ PPC_INS_ALIAS_MFIBATU, "mfibatu" },
	{ PPC_INS_ALIAS_MTIBATL, "mtibatl" },
	{ PPC_INS_ALIAS_MFIBATL, "mfibatl" },
	{ PPC_INS_ALIAS_MTPPR, "mtppr" },
	{ PPC_INS_ALIAS_MFPPR, "mfppr" },
	{ PPC_INS_ALIAS_MTESR, "mtesr" },
	{ PPC_INS_ALIAS_MFESR, "mfesr" },
	{ PPC_INS_ALIAS_MTDEAR, "mtdear" },
	{ PPC_INS_ALIAS_MFDEAR, "mfdear" },
	{ PPC_INS_ALIAS_MTTCR, "mttcr" },
	{ PPC_INS_ALIAS_MFTCR, "mftcr" },
	{ PPC_INS_ALIAS_MFTBHI, "mftbhi" },
	{ PPC_INS_ALIAS_MTTBHI, "mttbhi" },
	{ PPC_INS_ALIAS_MFTBLO, "mftblo" },
	{ PPC_INS_ALIAS_MTTBLO, "mttblo" },
	{ PPC_INS_ALIAS_MTSRR2, "mtsrr2" },
	{ PPC_INS_ALIAS_MFSRR2, "mfsrr2" },
	{ PPC_INS_ALIAS_MTSRR3, "mtsrr3" },
	{ PPC_INS_ALIAS_MFSRR3, "mfsrr3" },
	{ PPC_INS_ALIAS_MTDCCR, "mtdccr" },
	{ PPC_INS_ALIAS_MFDCCR, "mfdccr" },
	{ PPC_INS_ALIAS_MTICCR, "mticcr" },
	{ PPC_INS_ALIAS_MFICCR, "mficcr" },
	{ PPC_INS_ALIAS_TLBIE, "tlbie" },
	{ PPC_INS_ALIAS_TLBREHI, "tlbrehi" },
	{ PPC_INS_ALIAS_TLBRELO, "tlbrelo" },
	{ PPC_INS_ALIAS_TLBWEHI, "tlbwehi" },
	{ PPC_INS_ALIAS_TLBWELO, "tlbwelo" },
	{ PPC_INS_ALIAS_TLBILXLPID, "tlbilxlpid" },
	{ PPC_INS_ALIAS_TLBILXPID, "tlbilxpid" },
	{ PPC_INS_ALIAS_TLBILXVA, "tlbilxva" },
	{ PPC_INS_ALIAS_ROTLDI, "rotldi" },
	{ PPC_INS_ALIAS_ROTLDI_, "rotldi." },
	{ PPC_INS_ALIAS_ROTLD, "rotld" },
	{ PPC_INS_ALIAS_ROTLD_, "rotld." },
	{ PPC_INS_ALIAS_CLRLDI, "clrldi" },
	{ PPC_INS_ALIAS_CLRLDI_, "clrldi." },
	{ PPC_INS_ALIAS_LNIA, "lnia" },
	{ PPC_INS_ALIAS_BCp, "bcp" },
	{ PPC_INS_ALIAS_BCAp, "bcap" },
	{ PPC_INS_ALIAS_BCLp, "bclp" },
	{ PPC_INS_ALIAS_BCLAp, "bclap" },
	{ PPC_INS_ALIAS_BCm, "bcm" },
	{ PPC_INS_ALIAS_BCAm, "bcam" },
	{ PPC_INS_ALIAS_BCLm, "bclm" },
	{ PPC_INS_ALIAS_BCLAm, "bclam" },
	{ PPC_INS_ALIAS_BT, "bt" },
	{ PPC_INS_ALIAS_BTA, "bta" },
	{ PPC_INS_ALIAS_BTLR, "btlr" },
	{ PPC_INS_ALIAS_BTL, "btl" },
	{ PPC_INS_ALIAS_BTLA, "btla" },
	{ PPC_INS_ALIAS_BTLRL, "btlrl" },
	{ PPC_INS_ALIAS_BTCTR, "btctr" },
	{ PPC_INS_ALIAS_BTCTRL, "btctrl" },
	{ PPC_INS_ALIAS_BDZLR, "bdzlr" },
	{ PPC_INS_ALIAS_BDZLRL, "bdzlrl" },
	{ PPC_INS_ALIAS_BDZL, "bdzl" },
	{ PPC_INS_ALIAS_BDZLA, "bdzla" },
	{ PPC_INS_ALIAS_BDZ, "bdz" },
	{ PPC_INS_ALIAS_BDNZL, "bdnzl" },
	{ PPC_INS_ALIAS_BDNZLA, "bdnzla" },
	{ PPC_INS_ALIAS_BDNZ, "bdnz" },
	{ PPC_INS_ALIAS_BDZLp, "bdzlp" },
	{ PPC_INS_ALIAS_BDZLAp, "bdzlap" },
	{ PPC_INS_ALIAS_BDZp, "bdzp" },
	{ PPC_INS_ALIAS_BDNZLp, "bdnzlp" },
	{ PPC_INS_ALIAS_BDNZLAp, "bdnzlap" },
	{ PPC_INS_ALIAS_BDNZp, "bdnzp" },
	{ PPC_INS_ALIAS_BDZLm, "bdzlm" },
	{ PPC_INS_ALIAS_BDZLAm, "bdzlam" },
	{ PPC_INS_ALIAS_BDZm, "bdzm" },
	{ PPC_INS_ALIAS_BDNZLm, "bdnzlm" },
	{ PPC_INS_ALIAS_BDNZLAm, "bdnzlam" },
	{ PPC_INS_ALIAS_BDNZm, "bdnzm" },
	{ PPC_INS_ALIAS_BDNZLR, "bdnzlr" },
	{ PPC_INS_ALIAS_BDNZLRL, "bdnzlrl" },
	{ PPC_INS_ALIAS_BDZLRp, "bdzlrp" },
	{ PPC_INS_ALIAS_BDZLRLp, "bdzlrlp" },
	{ PPC_INS_ALIAS_BDNZLRp, "bdnzlrp" },
	{ PPC_INS_ALIAS_BDNZLRLp, "bdnzlrlp" },
	{ PPC_INS_ALIAS_BDZLRm, "bdzlrm" },
	{ PPC_INS_ALIAS_BDZLRLm, "bdzlrlm" },
	{ PPC_INS_ALIAS_BDNZLRm, "bdnzlrm" },
	{ PPC_INS_ALIAS_BDNZLRLm, "bdnzlrlm" },
	{ PPC_INS_ALIAS_BF, "bf" },
	{ PPC_INS_ALIAS_BFA, "bfa" },
	{ PPC_INS_ALIAS_BFLR, "bflr" },
	{ PPC_INS_ALIAS_BFL, "bfl" },
	{ PPC_INS_ALIAS_BFLA, "bfla" },
	{ PPC_INS_ALIAS_BFLRL, "bflrl" },
	{ PPC_INS_ALIAS_BFCTR, "bfctr" },
	{ PPC_INS_ALIAS_BFCTRL, "bfctrl" },
	{ PPC_INS_ALIAS_BTm, "btm" },
	{ PPC_INS_ALIAS_BTAm, "btam" },
	{ PPC_INS_ALIAS_BTLRm, "btlrm" },
	{ PPC_INS_ALIAS_BTLm, "btlm" },
	{ PPC_INS_ALIAS_BTLAm, "btlam" },
	{ PPC_INS_ALIAS_BTLRLm, "btlrlm" },
	{ PPC_INS_ALIAS_BTCTRm, "btctrm" },
	{ PPC_INS_ALIAS_BTCTRLm, "btctrlm" },
	{ PPC_INS_ALIAS_BFm, "bfm" },
	{ PPC_INS_ALIAS_BFAm, "bfam" },
	{ PPC_INS_ALIAS_BFLRm, "bflrm" },
	{ PPC_INS_ALIAS_BFLm, "bflm" },
	{ PPC_INS_ALIAS_BFLAm, "bflam" },
	{ PPC_INS_ALIAS_BFLRLm, "bflrlm" },
	{ PPC_INS_ALIAS_BFCTRm, "bfctrm" },
	{ PPC_INS_ALIAS_BFCTRLm, "bfctrlm" },
	{ PPC_INS_ALIAS_BTp, "btp" },
	{ PPC_INS_ALIAS_BTAp, "btap" },
	{ PPC_INS_ALIAS_BTLRp, "btlrp" },
	{ PPC_INS_ALIAS_BTLp, "btlp" },
	{ PPC_INS_ALIAS_BTLAp, "btlap" },
	{ PPC_INS_ALIAS_BTLRLp, "btlrlp" },
	{ PPC_INS_ALIAS_BTCTRp, "btctrp" },
	{ PPC_INS_ALIAS_BTCTRLp, "btctrlp" },
	{ PPC_INS_ALIAS_BFp, "bfp" },
	{ PPC_INS_ALIAS_BFAp, "bfap" },
	{ PPC_INS_ALIAS_BFLRp, "bflrp" },
	{ PPC_INS_ALIAS_BFLp, "bflp" },
	{ PPC_INS_ALIAS_BFLAp, "bflap" },
	{ PPC_INS_ALIAS_BFLRLp, "bflrlp" },
	{ PPC_INS_ALIAS_BFCTRp, "bfctrp" },
	{ PPC_INS_ALIAS_BFCTRLp, "bfctrlp" },
	{ PPC_INS_ALIAS_BDNZT, "bdnzt" },
	{ PPC_INS_ALIAS_BDNZTA, "bdnzta" },
	{ PPC_INS_ALIAS_BDNZTLR, "bdnztlr" },
	{ PPC_INS_ALIAS_BDNZTL, "bdnztl" },
	{ PPC_INS_ALIAS_BDNZTLA, "bdnztla" },
	{ PPC_INS_ALIAS_BDNZTLRL, "bdnztlrl" },
	{ PPC_INS_ALIAS_BDNZF, "bdnzf" },
	{ PPC_INS_ALIAS_BDNZFA, "bdnzfa" },
	{ PPC_INS_ALIAS_BDNZFLR, "bdnzflr" },
	{ PPC_INS_ALIAS_BDNZFL, "bdnzfl" },
	{ PPC_INS_ALIAS_BDNZFLA, "bdnzfla" },
	{ PPC_INS_ALIAS_BDNZFLRL, "bdnzflrl" },
	{ PPC_INS_ALIAS_BDZT, "bdzt" },
	{ PPC_INS_ALIAS_BDZTA, "bdzta" },
	{ PPC_INS_ALIAS_BDZTLR, "bdztlr" },
	{ PPC_INS_ALIAS_BDZTL, "bdztl" },
	{ PPC_INS_ALIAS_BDZTLA, "bdztla" },
	{ PPC_INS_ALIAS_BDZTLRL, "bdztlrl" },
	{ PPC_INS_ALIAS_BDZF, "bdzf" },
	{ PPC_INS_ALIAS_BDZFA, "bdzfa" },
	{ PPC_INS_ALIAS_BDZFLR, "bdzflr" },
	{ PPC_INS_ALIAS_BDZFL, "bdzfl" },
	{ PPC_INS_ALIAS_BDZFLA, "bdzfla" },
	{ PPC_INS_ALIAS_BDZFLRL, "bdzflrl" },
	{ PPC_INS_ALIAS_B, "b" },
	{ PPC_INS_ALIAS_BA, "ba" },
	{ PPC_INS_ALIAS_BL, "bl" },
	{ PPC_INS_ALIAS_BLA, "bla" },
	{ PPC_INS_ALIAS_BLR, "blr" },
	{ PPC_INS_ALIAS_BLRL, "blrl" },
	{ PPC_INS_ALIAS_BCTR, "bctr" },
	{ PPC_INS_ALIAS_BCTRL, "bctrl" },
	{ PPC_INS_ALIAS_BLT, "blt" },
	{ PPC_INS_ALIAS_BLTA, "blta" },
	{ PPC_INS_ALIAS_BLTLR, "bltlr" },
	{ PPC_INS_ALIAS_BLTCTR, "bltctr" },
	{ PPC_INS_ALIAS_BLTL, "bltl" },
	{ PPC_INS_ALIAS_BLTLA, "bltla" },
	{ PPC_INS_ALIAS_BLTLRL, "bltlrl" },
	{ PPC_INS_ALIAS_BLTCTRL, "bltctrl" },
	{ PPC_INS_ALIAS_BLTm, "bltm" },
	{ PPC_INS_ALIAS_BLTAm, "bltam" },
	{ PPC_INS_ALIAS_BLTLRm, "bltlrm" },
	{ PPC_INS_ALIAS_BLTCTRm, "bltctrm" },
	{ PPC_INS_ALIAS_BLTLm, "bltlm" },
	{ PPC_INS_ALIAS_BLTLAm, "bltlam" },
	{ PPC_INS_ALIAS_BLTLRLm, "bltlrlm" },
	{ PPC_INS_ALIAS_BLTCTRLm, "bltctrlm" },
	{ PPC_INS_ALIAS_BLTp, "bltp" },
	{ PPC_INS_ALIAS_BLTAp, "bltap" },
	{ PPC_INS_ALIAS_BLTLRp, "bltlrp" },
	{ PPC_INS_ALIAS_BLTCTRp, "bltctrp" },
	{ PPC_INS_ALIAS_BLTLp, "bltlp" },
	{ PPC_INS_ALIAS_BLTLAp, "bltlap" },
	{ PPC_INS_ALIAS_BLTLRLp, "bltlrlp" },
	{ PPC_INS_ALIAS_BLTCTRLp, "bltctrlp" },
	{ PPC_INS_ALIAS_BGT, "bgt" },
	{ PPC_INS_ALIAS_BGTA, "bgta" },
	{ PPC_INS_ALIAS_BGTLR, "bgtlr" },
	{ PPC_INS_ALIAS_BGTCTR, "bgtctr" },
	{ PPC_INS_ALIAS_BGTL, "bgtl" },
	{ PPC_INS_ALIAS_BGTLA, "bgtla" },
	{ PPC_INS_ALIAS_BGTLRL, "bgtlrl" },
	{ PPC_INS_ALIAS_BGTCTRL, "bgtctrl" },
	{ PPC_INS_ALIAS_BGTm, "bgtm" },
	{ PPC_INS_ALIAS_BGTAm, "bgtam" },
	{ PPC_INS_ALIAS_BGTLRm, "bgtlrm" },
	{ PPC_INS_ALIAS_BGTCTRm, "bgtctrm" },
	{ PPC_INS_ALIAS_BGTLm, "bgtlm" },
	{ PPC_INS_ALIAS_BGTLAm, "bgtlam" },
	{ PPC_INS_ALIAS_BGTLRLm, "bgtlrlm" },
	{ PPC_INS_ALIAS_BGTCTRLm, "bgtctrlm" },
	{ PPC_INS_ALIAS_BGTp, "bgtp" },
	{ PPC_INS_ALIAS_BGTAp, "bgtap" },
	{ PPC_INS_ALIAS_BGTLRp, "bgtlrp" },
	{ PPC_INS_ALIAS_BGTCTRp, "bgtctrp" },
	{ PPC_INS_ALIAS_BGTLp, "bgtlp" },
	{ PPC_INS_ALIAS_BGTLAp, "bgtlap" },
	{ PPC_INS_ALIAS_BGTLRLp, "bgtlrlp" },
	{ PPC_INS_ALIAS_BGTCTRLp, "bgtctrlp" },
	{ PPC_INS_ALIAS_BEQ, "beq" },
	{ PPC_INS_ALIAS_BEQA, "beqa" },
	{ PPC_INS_ALIAS_BEQLR, "beqlr" },
	{ PPC_INS_ALIAS_BEQCTR, "beqctr" },
	{ PPC_INS_ALIAS_BEQL, "beql" },
	{ PPC_INS_ALIAS_BEQLA, "beqla" },
	{ PPC_INS_ALIAS_BEQLRL, "beqlrl" },
	{ PPC_INS_ALIAS_BEQCTRL, "beqctrl" },
	{ PPC_INS_ALIAS_BEQm, "beqm" },
	{ PPC_INS_ALIAS_BEQAm, "beqam" },
	{ PPC_INS_ALIAS_BEQLRm, "beqlrm" },
	{ PPC_INS_ALIAS_BEQCTRm, "beqctrm" },
	{ PPC_INS_ALIAS_BEQLm, "beqlm" },
	{ PPC_INS_ALIAS_BEQLAm, "beqlam" },
	{ PPC_INS_ALIAS_BEQLRLm, "beqlrlm" },
	{ PPC_INS_ALIAS_BEQCTRLm, "beqctrlm" },
	{ PPC_INS_ALIAS_BEQp, "beqp" },
	{ PPC_INS_ALIAS_BEQAp, "beqap" },
	{ PPC_INS_ALIAS_BEQLRp, "beqlrp" },
	{ PPC_INS_ALIAS_BEQCTRp, "beqctrp" },
	{ PPC_INS_ALIAS_BEQLp, "beqlp" },
	{ PPC_INS_ALIAS_BEQLAp, "beqlap" },
	{ PPC_INS_ALIAS_BEQLRLp, "beqlrlp" },
	{ PPC_INS_ALIAS_BEQCTRLp, "beqctrlp" },
	{ PPC_INS_ALIAS_BUN, "bun" },
	{ PPC_INS_ALIAS_BUNA, "buna" },
	{ PPC_INS_ALIAS_BUNLR, "bunlr" },
	{ PPC_INS_ALIAS_BUNCTR, "bunctr" },
	{ PPC_INS_ALIAS_BUNL, "bunl" },
	{ PPC_INS_ALIAS_BUNLA, "bunla" },
	{ PPC_INS_ALIAS_BUNLRL, "bunlrl" },
	{ PPC_INS_ALIAS_BUNCTRL, "bunctrl" },
	{ PPC_INS_ALIAS_BUNm, "bunm" },
	{ PPC_INS_ALIAS_BUNAm, "bunam" },
	{ PPC_INS_ALIAS_BUNLRm, "bunlrm" },
	{ PPC_INS_ALIAS_BUNCTRm, "bunctrm" },
	{ PPC_INS_ALIAS_BUNLm, "bunlm" },
	{ PPC_INS_ALIAS_BUNLAm, "bunlam" },
	{ PPC_INS_ALIAS_BUNLRLm, "bunlrlm" },
	{ PPC_INS_ALIAS_BUNCTRLm, "bunctrlm" },
	{ PPC_INS_ALIAS_BUNp, "bunp" },
	{ PPC_INS_ALIAS_BUNAp, "bunap" },
	{ PPC_INS_ALIAS_BUNLRp, "bunlrp" },
	{ PPC_INS_ALIAS_BUNCTRp, "bunctrp" },
	{ PPC_INS_ALIAS_BUNLp, "bunlp" },
	{ PPC_INS_ALIAS_BUNLAp, "bunlap" },
	{ PPC_INS_ALIAS_BUNLRLp, "bunlrlp" },
	{ PPC_INS_ALIAS_BUNCTRLp, "bunctrlp" },
	{ PPC_INS_ALIAS_BSO, "bso" },
	{ PPC_INS_ALIAS_BSOA, "bsoa" },
	{ PPC_INS_ALIAS_BSOLR, "bsolr" },
	{ PPC_INS_ALIAS_BSOCTR, "bsoctr" },
	{ PPC_INS_ALIAS_BSOL, "bsol" },
	{ PPC_INS_ALIAS_BSOLA, "bsola" },
	{ PPC_INS_ALIAS_BSOLRL, "bsolrl" },
	{ PPC_INS_ALIAS_BSOCTRL, "bsoctrl" },
	{ PPC_INS_ALIAS_BSOm, "bsom" },
	{ PPC_INS_ALIAS_BSOAm, "bsoam" },
	{ PPC_INS_ALIAS_BSOLRm, "bsolrm" },
	{ PPC_INS_ALIAS_BSOCTRm, "bsoctrm" },
	{ PPC_INS_ALIAS_BSOLm, "bsolm" },
	{ PPC_INS_ALIAS_BSOLAm, "bsolam" },
	{ PPC_INS_ALIAS_BSOLRLm, "bsolrlm" },
	{ PPC_INS_ALIAS_BSOCTRLm, "bsoctrlm" },
	{ PPC_INS_ALIAS_BSOp, "bsop" },
	{ PPC_INS_ALIAS_BSOAp, "bsoap" },
	{ PPC_INS_ALIAS_BSOLRp, "bsolrp" },
	{ PPC_INS_ALIAS_BSOCTRp, "bsoctrp" },
	{ PPC_INS_ALIAS_BSOLp, "bsolp" },
	{ PPC_INS_ALIAS_BSOLAp, "bsolap" },
	{ PPC_INS_ALIAS_BSOLRLp, "bsolrlp" },
	{ PPC_INS_ALIAS_BSOCTRLp, "bsoctrlp" },
	{ PPC_INS_ALIAS_BGE, "bge" },
	{ PPC_INS_ALIAS_BGEA, "bgea" },
	{ PPC_INS_ALIAS_BGELR, "bgelr" },
	{ PPC_INS_ALIAS_BGECTR, "bgectr" },
	{ PPC_INS_ALIAS_BGEL, "bgel" },
	{ PPC_INS_ALIAS_BGELA, "bgela" },
	{ PPC_INS_ALIAS_BGELRL, "bgelrl" },
	{ PPC_INS_ALIAS_BGECTRL, "bgectrl" },
	{ PPC_INS_ALIAS_BGEm, "bgem" },
	{ PPC_INS_ALIAS_BGEAm, "bgeam" },
	{ PPC_INS_ALIAS_BGELRm, "bgelrm" },
	{ PPC_INS_ALIAS_BGECTRm, "bgectrm" },
	{ PPC_INS_ALIAS_BGELm, "bgelm" },
	{ PPC_INS_ALIAS_BGELAm, "bgelam" },
	{ PPC_INS_ALIAS_BGELRLm, "bgelrlm" },
	{ PPC_INS_ALIAS_BGECTRLm, "bgectrlm" },
	{ PPC_INS_ALIAS_BGEp, "bgep" },
	{ PPC_INS_ALIAS_BGEAp, "bgeap" },
	{ PPC_INS_ALIAS_BGELRp, "bgelrp" },
	{ PPC_INS_ALIAS_BGECTRp, "bgectrp" },
	{ PPC_INS_ALIAS_BGELp, "bgelp" },
	{ PPC_INS_ALIAS_BGELAp, "bgelap" },
	{ PPC_INS_ALIAS_BGELRLp, "bgelrlp" },
	{ PPC_INS_ALIAS_BGECTRLp, "bgectrlp" },
	{ PPC_INS_ALIAS_BNL, "bnl" },
	{ PPC_INS_ALIAS_BNLA, "bnla" },
	{ PPC_INS_ALIAS_BNLLR, "bnllr" },
	{ PPC_INS_ALIAS_BNLCTR, "bnlctr" },
	{ PPC_INS_ALIAS_BNLL, "bnll" },
	{ PPC_INS_ALIAS_BNLLA, "bnlla" },
	{ PPC_INS_ALIAS_BNLLRL, "bnllrl" },
	{ PPC_INS_ALIAS_BNLCTRL, "bnlctrl" },
	{ PPC_INS_ALIAS_BNLm, "bnlm" },
	{ PPC_INS_ALIAS_BNLAm, "bnlam" },
	{ PPC_INS_ALIAS_BNLLRm, "bnllrm" },
	{ PPC_INS_ALIAS_BNLCTRm, "bnlctrm" },
	{ PPC_INS_ALIAS_BNLLm, "bnllm" },
	{ PPC_INS_ALIAS_BNLLAm, "bnllam" },
	{ PPC_INS_ALIAS_BNLLRLm, "bnllrlm" },
	{ PPC_INS_ALIAS_BNLCTRLm, "bnlctrlm" },
	{ PPC_INS_ALIAS_BNLp, "bnlp" },
	{ PPC_INS_ALIAS_BNLAp, "bnlap" },
	{ PPC_INS_ALIAS_BNLLRp, "bnllrp" },
	{ PPC_INS_ALIAS_BNLCTRp, "bnlctrp" },
	{ PPC_INS_ALIAS_BNLLp, "bnllp" },
	{ PPC_INS_ALIAS_BNLLAp, "bnllap" },
	{ PPC_INS_ALIAS_BNLLRLp, "bnllrlp" },
	{ PPC_INS_ALIAS_BNLCTRLp, "bnlctrlp" },
	{ PPC_INS_ALIAS_BLE, "ble" },
	{ PPC_INS_ALIAS_BLEA, "blea" },
	{ PPC_INS_ALIAS_BLELR, "blelr" },
	{ PPC_INS_ALIAS_BLECTR, "blectr" },
	{ PPC_INS_ALIAS_BLEL, "blel" },
	{ PPC_INS_ALIAS_BLELA, "blela" },
	{ PPC_INS_ALIAS_BLELRL, "blelrl" },
	{ PPC_INS_ALIAS_BLECTRL, "blectrl" },
	{ PPC_INS_ALIAS_BLEm, "blem" },
	{ PPC_INS_ALIAS_BLEAm, "bleam" },
	{ PPC_INS_ALIAS_BLELRm, "blelrm" },
	{ PPC_INS_ALIAS_BLECTRm, "blectrm" },
	{ PPC_INS_ALIAS_BLELm, "blelm" },
	{ PPC_INS_ALIAS_BLELAm, "blelam" },
	{ PPC_INS_ALIAS_BLELRLm, "blelrlm" },
	{ PPC_INS_ALIAS_BLECTRLm, "blectrlm" },
	{ PPC_INS_ALIAS_BLEp, "blep" },
	{ PPC_INS_ALIAS_BLEAp, "bleap" },
	{ PPC_INS_ALIAS_BLELRp, "blelrp" },
	{ PPC_INS_ALIAS_BLECTRp, "blectrp" },
	{ PPC_INS_ALIAS_BLELp, "blelp" },
	{ PPC_INS_ALIAS_BLELAp, "blelap" },
	{ PPC_INS_ALIAS_BLELRLp, "blelrlp" },
	{ PPC_INS_ALIAS_BLECTRLp, "blectrlp" },
	{ PPC_INS_ALIAS_BNG, "bng" },
	{ PPC_INS_ALIAS_BNGA, "bnga" },
	{ PPC_INS_ALIAS_BNGLR, "bnglr" },
	{ PPC_INS_ALIAS_BNGCTR, "bngctr" },
	{ PPC_INS_ALIAS_BNGL, "bngl" },
	{ PPC_INS_ALIAS_BNGLA, "bngla" },
	{ PPC_INS_ALIAS_BNGLRL, "bnglrl" },
	{ PPC_INS_ALIAS_BNGCTRL, "bngctrl" },
	{ PPC_INS_ALIAS_BNGm, "bngm" },
	{ PPC_INS_ALIAS_BNGAm, "bngam" },
	{ PPC_INS_ALIAS_BNGLRm, "bnglrm" },
	{ PPC_INS_ALIAS_BNGCTRm, "bngctrm" },
	{ PPC_INS_ALIAS_BNGLm, "bnglm" },
	{ PPC_INS_ALIAS_BNGLAm, "bnglam" },
	{ PPC_INS_ALIAS_BNGLRLm, "bnglrlm" },
	{ PPC_INS_ALIAS_BNGCTRLm, "bngctrlm" },
	{ PPC_INS_ALIAS_BNGp, "bngp" },
	{ PPC_INS_ALIAS_BNGAp, "bngap" },
	{ PPC_INS_ALIAS_BNGLRp, "bnglrp" },
	{ PPC_INS_ALIAS_BNGCTRp, "bngctrp" },
	{ PPC_INS_ALIAS_BNGLp, "bnglp" },
	{ PPC_INS_ALIAS_BNGLAp, "bnglap" },
	{ PPC_INS_ALIAS_BNGLRLp, "bnglrlp" },
	{ PPC_INS_ALIAS_BNGCTRLp, "bngctrlp" },
	{ PPC_INS_ALIAS_BNE, "bne" },
	{ PPC_INS_ALIAS_BNEA, "bnea" },
	{ PPC_INS_ALIAS_BNELR, "bnelr" },
	{ PPC_INS_ALIAS_BNECTR, "bnectr" },
	{ PPC_INS_ALIAS_BNEL, "bnel" },
	{ PPC_INS_ALIAS_BNELA, "bnela" },
	{ PPC_INS_ALIAS_BNELRL, "bnelrl" },
	{ PPC_INS_ALIAS_BNECTRL, "bnectrl" },
	{ PPC_INS_ALIAS_BNEm, "bnem" },
	{ PPC_INS_ALIAS_BNEAm, "bneam" },
	{ PPC_INS_ALIAS_BNELRm, "bnelrm" },
	{ PPC_INS_ALIAS_BNECTRm, "bnectrm" },
	{ PPC_INS_ALIAS_BNELm, "bnelm" },
	{ PPC_INS_ALIAS_BNELAm, "bnelam" },
	{ PPC_INS_ALIAS_BNELRLm, "bnelrlm" },
	{ PPC_INS_ALIAS_BNECTRLm, "bnectrlm" },
	{ PPC_INS_ALIAS_BNEp, "bnep" },
	{ PPC_INS_ALIAS_BNEAp, "bneap" },
	{ PPC_INS_ALIAS_BNELRp, "bnelrp" },
	{ PPC_INS_ALIAS_BNECTRp, "bnectrp" },
	{ PPC_INS_ALIAS_BNELp, "bnelp" },
	{ PPC_INS_ALIAS_BNELAp, "bnelap" },
	{ PPC_INS_ALIAS_BNELRLp, "bnelrlp" },
	{ PPC_INS_ALIAS_BNECTRLp, "bnectrlp" },
	{ PPC_INS_ALIAS_BNU, "bnu" },
	{ PPC_INS_ALIAS_BNUA, "bnua" },
	{ PPC_INS_ALIAS_BNULR, "bnulr" },
	{ PPC_INS_ALIAS_BNUCTR, "bnuctr" },
	{ PPC_INS_ALIAS_BNUL, "bnul" },
	{ PPC_INS_ALIAS_BNULA, "bnula" },
	{ PPC_INS_ALIAS_BNULRL, "bnulrl" },
	{ PPC_INS_ALIAS_BNUCTRL, "bnuctrl" },
	{ PPC_INS_ALIAS_BNUm, "bnum" },
	{ PPC_INS_ALIAS_BNUAm, "bnuam" },
	{ PPC_INS_ALIAS_BNULRm, "bnulrm" },
	{ PPC_INS_ALIAS_BNUCTRm, "bnuctrm" },
	{ PPC_INS_ALIAS_BNULm, "bnulm" },
	{ PPC_INS_ALIAS_BNULAm, "bnulam" },
	{ PPC_INS_ALIAS_BNULRLm, "bnulrlm" },
	{ PPC_INS_ALIAS_BNUCTRLm, "bnuctrlm" },
	{ PPC_INS_ALIAS_BNUp, "bnup" },
	{ PPC_INS_ALIAS_BNUAp, "bnuap" },
	{ PPC_INS_ALIAS_BNULRp, "bnulrp" },
	{ PPC_INS_ALIAS_BNUCTRp, "bnuctrp" },
	{ PPC_INS_ALIAS_BNULp, "bnulp" },
	{ PPC_INS_ALIAS_BNULAp, "bnulap" },
	{ PPC_INS_ALIAS_BNULRLp, "bnulrlp" },
	{ PPC_INS_ALIAS_BNUCTRLp, "bnuctrlp" },
	{ PPC_INS_ALIAS_BNS, "bns" },
	{ PPC_INS_ALIAS_BNSA, "bnsa" },
	{ PPC_INS_ALIAS_BNSLR, "bnslr" },
	{ PPC_INS_ALIAS_BNSCTR, "bnsctr" },
	{ PPC_INS_ALIAS_BNSL, "bnsl" },
	{ PPC_INS_ALIAS_BNSLA, "bnsla" },
	{ PPC_INS_ALIAS_BNSLRL, "bnslrl" },
	{ PPC_INS_ALIAS_BNSCTRL, "bnsctrl" },
	{ PPC_INS_ALIAS_BNSm, "bnsm" },
	{ PPC_INS_ALIAS_BNSAm, "bnsam" },
	{ PPC_INS_ALIAS_BNSLRm, "bnslrm" },
	{ PPC_INS_ALIAS_BNSCTRm, "bnsctrm" },
	{ PPC_INS_ALIAS_BNSLm, "bnslm" },
	{ PPC_INS_ALIAS_BNSLAm, "bnslam" },
	{ PPC_INS_ALIAS_BNSLRLm, "bnslrlm" },
	{ PPC_INS_ALIAS_BNSCTRLm, "bnsctrlm" },
	{ PPC_INS_ALIAS_BNSp, "bnsp" },
	{ PPC_INS_ALIAS_BNSAp, "bnsap" },
	{ PPC_INS_ALIAS_BNSLRp, "bnslrp" },
	{ PPC_INS_ALIAS_BNSCTRp, "bnsctrp" },
	{ PPC_INS_ALIAS_BNSLp, "bnslp" },
	{ PPC_INS_ALIAS_BNSLAp, "bnslap" },
	{ PPC_INS_ALIAS_BNSLRLp, "bnslrlp" },
	{ PPC_INS_ALIAS_BNSCTRLp, "bnsctrlp" },
	{ PPC_INS_ALIAS_CMPWI, "cmpwi" },
	{ PPC_INS_ALIAS_CMPW, "cmpw" },
	{ PPC_INS_ALIAS_CMPLWI, "cmplwi" },
	{ PPC_INS_ALIAS_CMPLW, "cmplw" },
	{ PPC_INS_ALIAS_CMPDI, "cmpdi" },
	{ PPC_INS_ALIAS_CMPD, "cmpd" },
	{ PPC_INS_ALIAS_CMPLDI, "cmpldi" },
	{ PPC_INS_ALIAS_CMPLD, "cmpld" },
	{ PPC_INS_ALIAS_CMPI, "cmpi" },
	{ PPC_INS_ALIAS_CMP, "cmp" },
	{ PPC_INS_ALIAS_CMPLI, "cmpli" },
	{ PPC_INS_ALIAS_CMPL, "cmpl" },
	{ PPC_INS_ALIAS_TRAP, "trap" },
	{ PPC_INS_ALIAS_TDLTI, "tdlti" },
	{ PPC_INS_ALIAS_TDLT, "tdlt" },
	{ PPC_INS_ALIAS_TWLTI, "twlti" },
	{ PPC_INS_ALIAS_TWLT, "twlt" },
	{ PPC_INS_ALIAS_TDLEI, "tdlei" },
	{ PPC_INS_ALIAS_TDLE, "tdle" },
	{ PPC_INS_ALIAS_TWLEI, "twlei" },
	{ PPC_INS_ALIAS_TWLE, "twle" },
	{ PPC_INS_ALIAS_TDEQI, "tdeqi" },
	{ PPC_INS_ALIAS_TDEQ, "tdeq" },
	{ PPC_INS_ALIAS_TWEQI, "tweqi" },
	{ PPC_INS_ALIAS_TWEQ, "tweq" },
	{ PPC_INS_ALIAS_TDGEI, "tdgei" },
	{ PPC_INS_ALIAS_TDGE, "tdge" },
	{ PPC_INS_ALIAS_TWGEI, "twgei" },
	{ PPC_INS_ALIAS_TWGE, "twge" },
	{ PPC_INS_ALIAS_TDGTI, "tdgti" },
	{ PPC_INS_ALIAS_TDGT, "tdgt" },
	{ PPC_INS_ALIAS_TWGTI, "twgti" },
	{ PPC_INS_ALIAS_TWGT, "twgt" },
	{ PPC_INS_ALIAS_TDNLI, "tdnli" },
	{ PPC_INS_ALIAS_TDNL, "tdnl" },
	{ PPC_INS_ALIAS_TWNLI, "twnli" },
	{ PPC_INS_ALIAS_TWNL, "twnl" },
	{ PPC_INS_ALIAS_TDNEI, "tdnei" },
	{ PPC_INS_ALIAS_TDNE, "tdne" },
	{ PPC_INS_ALIAS_TWNEI, "twnei" },
	{ PPC_INS_ALIAS_TWNE, "twne" },
	{ PPC_INS_ALIAS_TDNGI, "tdngi" },
	{ PPC_INS_ALIAS_TDNG, "tdng" },
	{ PPC_INS_ALIAS_TWNGI, "twngi" },
	{ PPC_INS_ALIAS_TWNG, "twng" },
	{ PPC_INS_ALIAS_TDLLTI, "tdllti" },
	{ PPC_INS_ALIAS_TDLLT, "tdllt" },
	{ PPC_INS_ALIAS_TWLLTI, "twllti" },
	{ PPC_INS_ALIAS_TWLLT, "twllt" },
	{ PPC_INS_ALIAS_TDLLEI, "tdllei" },
	{ PPC_INS_ALIAS_TDLLE, "tdlle" },
	{ PPC_INS_ALIAS_TWLLEI, "twllei" },
	{ PPC_INS_ALIAS_TWLLE, "twlle" },
	{ PPC_INS_ALIAS_TDLGEI, "tdlgei" },
	{ PPC_INS_ALIAS_TDLGE, "tdlge" },
	{ PPC_INS_ALIAS_TWLGEI, "twlgei" },
	{ PPC_INS_ALIAS_TWLGE, "twlge" },
	{ PPC_INS_ALIAS_TDLGTI, "tdlgti" },
	{ PPC_INS_ALIAS_TDLGT, "tdlgt" },
	{ PPC_INS_ALIAS_TWLGTI, "twlgti" },
	{ PPC_INS_ALIAS_TWLGT, "twlgt" },
	{ PPC_INS_ALIAS_TDLNLI, "tdlnli" },
	{ PPC_INS_ALIAS_TDLNL, "tdlnl" },
	{ PPC_INS_ALIAS_TWLNLI, "twlnli" },
	{ PPC_INS_ALIAS_TWLNL, "twlnl" },
	{ PPC_INS_ALIAS_TDLNGI, "tdlngi" },
	{ PPC_INS_ALIAS_TDLNG, "tdlng" },
	{ PPC_INS_ALIAS_TWLNGI, "twlngi" },
	{ PPC_INS_ALIAS_TWLNG, "twlng" },
	{ PPC_INS_ALIAS_TDUI, "tdui" },
	{ PPC_INS_ALIAS_TDU, "tdu" },
	{ PPC_INS_ALIAS_TWUI, "twui" },
	{ PPC_INS_ALIAS_TWU, "twu" },
	{ PPC_INS_ALIAS_PASTE_, "paste." },
	{ PPC_INS_ALIAS_QVFCLR, "qvfclr" },
	{ PPC_INS_ALIAS_QVFAND, "qvfand" },
	{ PPC_INS_ALIAS_QVFANDC, "qvfandc" },
	{ PPC_INS_ALIAS_QVFCTFB, "qvfctfb" },
	{ PPC_INS_ALIAS_QVFXOR, "qvfxor" },
	{ PPC_INS_ALIAS_QVFOR, "qvfor" },
	{ PPC_INS_ALIAS_QVFNOR, "qvfnor" },
	{ PPC_INS_ALIAS_QVFEQU, "qvfequ" },
	{ PPC_INS_ALIAS_QVFNOT, "qvfnot" },
	{ PPC_INS_ALIAS_QVFORC, "qvforc" },
	{ PPC_INS_ALIAS_QVFNAND, "qvfnand" },
	{ PPC_INS_ALIAS_QVFSET, "qvfset" },