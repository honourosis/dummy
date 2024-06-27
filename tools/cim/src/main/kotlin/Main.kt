package org.github.honourosis

import com.fasterxml.jackson.module.kotlin.jacksonObjectMapper
import java.nio.file.*
import kotlin.io.path.createDirectories
import kotlin.io.path.exists
import kotlin.text.Charsets.UTF_8

fun main(args: Array<String>) {
    val destination = parseDestination(args)
    if (destination.exists(LinkOption.NOFOLLOW_LINKS)) {
        throw IllegalArgumentException("Unable to generate mapping to the path $destination. File already exists!")
    }
    val json = Mapper.javaClass
        .classLoader
        .getResourceAsStream("opcodes.json").use {
            it?.reader(UTF_8)?.readLines()?.joinToString(" ")
        } ?: throw IllegalStateException("Unable to load default opcodes.json file")
    val opcodes = jacksonObjectMapper()
        .readerFor(Opcodes::class.java)
        .readValue<Opcodes>(json)
    val generated = Mapper.generate(opcodes)
    destination.parent.createDirectories()
    Files.writeString(destination, generated, UTF_8, StandardOpenOption.CREATE_NEW, StandardOpenOption.WRITE)
}

private fun parseDestination(args: Array<String>): Path {
    var destinationFlagFound = false
    for (param in args) {
        if (param == "-d") {
            destinationFlagFound = true
            continue
        }
        if (destinationFlagFound) {
            return Paths.get(param)
        }
    }
    throw IllegalArgumentException("Unknown generator destination. Pass -r %path% as an argument")
}
