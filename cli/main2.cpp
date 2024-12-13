#include <vrEmu6502.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdarg.h>
#include <cassert>
#include <cstring>
#include <string>

uint8_t * ram;

uint8_t MemRead(uint16_t addr, bool isDbg) {
  (void)isDbg;
  return ram[addr];
}

void MemWrite(uint16_t addr, uint8_t val) {
  ram[addr] = val;
}

const char* processorModel(int cpuModel) {
  switch (cpuModel) {
    case CPU_6502: return "Standard NMOS 6502";
    case CPU_6502U: return "Standard NMOS 6502 (with undocumented opcodes)";
    case CPU_65C02: return "Standard CMOS 65C02";
    case CPU_W65C02: return "Western Design Centre 65C02";
    case CPU_R65C02: return "Rockwell 65C02";
    default: return "Unknown";
  }
}

uint16_t showMemFrom = 0;
uint16_t showMemBytes = 4;
uint16_t pc = 0;
uint16_t lastPc = 0;
int status = 0;
uint64_t instructionCount = 0;
uint64_t cycleCount = 0;

void outputStep(VrEmu6502* vr6502, uint16_t pc) {
  char buffer[32];
  vrEmu6502DisassembleInstruction(vr6502, pc, sizeof(buffer), buffer, NULL, NULL);
  uint8_t a = vrEmu6502GetAcc(vr6502);
  uint8_t x = vrEmu6502GetX(vr6502);
  uint8_t y = vrEmu6502GetY(vr6502);
  uint8_t sp = vrEmu6502GetStackPointer(vr6502);
  uint8_t status = vrEmu6502GetStatus(vr6502);

  if (0 == 0)
  {
    putchar('\n');

    printf("Step #      | PC    | Instruction    | Acc | InX | InY | SP   Top |   Status    ");
    if (showMemBytes > 1)
    {
      printf("| $%04x - $%04x", showMemFrom, showMemFrom + showMemBytes - 1);
    }
    else if (showMemBytes)
    {
      printf("| $%04x", showMemFrom);
    }

    printf("\n------------+-------+----------------+-----+-----+-----+----------+-------------");
    if (showMemBytes)
    {
      printf("+------");
      if (showMemBytes > 1) printf("--------");
    }
    putchar('\n');
  }


  printf("#%-10" PRId64 " | $%04x | %-14s | $%02x | $%02x | $%02x | $%02x: $%02x | $%02x: %c%c%c%c%c%c ",
    instructionCount, pc, buffer, a, x, y, sp, MemRead(0x100 + ((sp + 1) & 0xff), 0), status,
    status & FlagN ? 'N' : '.',
    status & FlagV ? 'V' : '.',
    status & FlagD ? 'D' : '.',
    status & FlagI ? 'I' : '.',
    status & FlagZ ? 'Z' : '.',
    status & FlagC ? 'C' : '.');

  if (showMemBytes) printf("| ");

  for (int i = 0; i < showMemBytes; ++i)
  {
    printf("$%02x ", MemRead((showMemFrom + i) & 0xffff, 0));
  }
  putchar('\n');
}

int main(int argc, char* argv[]) {
  VrEmu6502* vr6502 = vrEmu6502New(CPU_6502, MemRead, MemWrite);
  if (vr6502 == nullptr) {
    puts("failed to create vcpu");
    return 1;
  }
  ram = reinterpret_cast<uint8_t*>(malloc(4096*65));
  memset(ram, 0x0, 4096*65);
  pc = 0x0;
  lastPc = 0x1; // can be any address != pc
  ram[pc+0] = 0xa5; ram[pc+1] = 0x06; // lda 6
  ram[pc+2] = 0xa5; ram[pc+3] = 0x07; // lda 7
  ram[pc+4] = 0xa5; ram[pc+5] = 0x06; // lda 6
  ram[pc+6] = 0xa5; ram[pc+7] = 0x07; // lda 7
  ram[pc+8] = 0xdb;                   // STP
  printf("\nResetting...\n");
  vrEmu6502Reset(vr6502);
  vrEmu6502SetPC(vr6502, pc);
  printf("\nRunning...\n");
  while (1) {
    if (vrEmu6502GetOpcodeCycle(vr6502) == 0) {
      /* trap detection */
      uint16_t pc = vrEmu6502GetCurrentOpcodeAddr(vr6502);
      printf("\nCurrent instruction:");
      outputStep(vr6502, pc);
      if (lastPc == pc) {
        printf("\nFinal instruction (lastPc == pc):");
        outputStep(vr6502, pc);
        status = pc == 0x4c ? 0 : -1;
        break;
      }
      lastPc = pc;
      ++instructionCount;

      /* break on STP instruction */
      if (vrEmu6502GetCurrentOpcode(vr6502) == 0xdb) {
        printf("\nFinal instruction (opcode == 0xdb):");
        outputStep(vr6502, vrEmu6502GetCurrentOpcodeAddr(vr6502));
        status = 0;
        break;
      }
    }

    /* call me once for each clock cycle (eg. 1,000,000 times per second for a 1MHz clock) */
    cycleCount += vrEmu6502InstCycle(vr6502);
  }

  vrEmu6502Destroy(vr6502);
  free(ram);
  return 0;
}