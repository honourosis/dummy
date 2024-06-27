package org.github.honourosis

import com.fasterxml.jackson.annotation.JsonIgnoreProperties

typealias Opcode = String

@JsonIgnoreProperties(ignoreUnknown = true)
class Opcodes : HashMap<String, OpcodeMap>()

@JsonIgnoreProperties(ignoreUnknown = true)
class Operand(val name: String, val bytes: Int, val immediate: Boolean)

@JsonIgnoreProperties(ignoreUnknown = true)
class OpcodeInfo(
    val mnemonic: String,
    val bytes: Int,
    val cycles: List<Int>,
    val operands: List<Operand>,
    val immediate: Boolean,
    val flags: Map<String, String>
)

@JsonIgnoreProperties(ignoreUnknown = true)
class OpcodeMap : HashMap<Opcode, OpcodeInfo>()