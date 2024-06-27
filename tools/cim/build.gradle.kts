plugins {
    kotlin("jvm") version "2.0.0"
    application
    java
}

group = "org.github.honourosis"
version = "1.0-SNAPSHOT"

repositories {
    mavenCentral()
}

dependencies {
    implementation("com.fasterxml.jackson.module:jackson-module-kotlin:2.17.1")
    implementation("com.fasterxml.jackson.core:jackson-core:2.17.1")
    implementation("com.fasterxml.jackson.core:jackson-databind:2.17.1")
    testImplementation(kotlin("test"))
}

tasks.test {
    useJUnitPlatform()
}

kotlin {
    jvmToolchain(17)
}

application {
    mainClass = "org.github.honourosis.MainKt"
}

tasks.jar {
    manifest.attributes["Main-Class"] = "org.github.honourosis.MainKt"
    duplicatesStrategy = DuplicatesStrategy.EXCLUDE
    from(
        configurations
            .runtimeClasspath
            .get()
            .map(::zipTree)
    )
}