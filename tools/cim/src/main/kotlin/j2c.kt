package org.github.honourosis

enum class TemplateOperand(val register: Boolean = true, val condition: Boolean = false) {
    A,
    B,
    C,
    D,
    E,
    H,
    L,
    AF,
    BC,
    DE,
    HL,
    PC,
    SP,
    n8(false),
    n16(false),
    a8(false),
    a16(false),
    e8(false),
    NZ(false, true),
    Z(false, true),
    NC(false, true),
    ADDR(false, false)
}

fun getTemplateOperand(name: String): TemplateOperand {
    return try {
        TemplateOperand.valueOf(name)
    } catch (e: IllegalArgumentException) {
        TemplateOperand.ADDR
    }
}

fun TemplateOperand.templateName(): String {
    if (condition) {
        return "COND_$name".uppercase()
    }
    return if (register) {
        "REG_$name".uppercase()
    } else {
        "ADD_$name".uppercase()
    }
}
