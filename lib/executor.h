#pragma once

#include "common.h"
#include "cpu.h"

typedef void (*Executor)(CPU_context *);

Executor lookup_executor(Instruction *instruction);
