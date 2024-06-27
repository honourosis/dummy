package org.github.honourosis

import java.util.Comparator
import java.util.StringJoiner

object Mapper {

    private const val TEMPLATE = """
        #include "instruction.h"

        Instruction instructions[%INSTRUCTION_COUNT%] = {
            %INSTRUCTIONS%
        };

        Instruction *lookup_instruction(uint8_t opcode) {
            return &instructions[opcode];
        }
    """;

    fun generate(opcodes: Opcodes): String {
        val unprefixed = opcodes["unprefixed"]
            ?.filterValues { !it.mnemonic.startsWith("ILLEGAL") }
            ?.toSortedMap(Comparator.comparingInt {
                Integer.valueOf(it.substring(2), 16)
            })
            ?: throw IllegalArgumentException("Unprefixed instruction set should be defined!")
        val joiner = StringJoiner(",\n")
        unprefixed.forEach { (opcode, info) -> joiner.add(mapInstructionRow(opcode, info)) }
        return TEMPLATE
            .replaceFirst("%INSTRUCTION_COUNT%", "0x${Integer.toHexString(opcodes["unprefixed"]!!.size)}")
            .replaceFirst("%INSTRUCTIONS%", joiner.toString())
    }

    private fun mapInstructionRow(opcode: String, info: OpcodeInfo): String {
        return "[$opcode] = { ${info.asTemplateValue()} }"
    }

    private fun OpcodeInfo.asTemplateValue(): String {
        val templateOperands = operands.map { getTemplateOperand(it.name) }
        if (templateOperands.isEmpty()) {
            return "INS_$mnemonic, ADD_INP"
        }
        val operandsForTemplate = templateOperands.filter { it.register }
            .map { it.templateName() }
            .joinToString(", ")
        return "INS_$mnemonic, ${getAddressing(templateOperands)}, $operandsForTemplate"
    }

    private fun getAddressing(operands: List<TemplateOperand>): String {
        if (operands.isEmpty()) {
            return "ADD_INP"
        }
        val firstOperand = operands[0]
        if (operands.size == 1) {
            return "ADD_${firstOperand.regOrValue().uppercase()}"
        }
        val secondOperand = operands[1]
        return "ADD_" + firstOperand.regOrValue().uppercase() + "_" + secondOperand.regOrValue().uppercase()
    }

    private fun TemplateOperand.regOrValue(): String {
        if (register) {
            return "REG"
        }
        return name.uppercase()
    }
}