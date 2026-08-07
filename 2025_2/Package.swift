// swift-tools-version: 6.2
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "2025_2",
    targets: [
        // Targets are the basic building blocks of a package, defining a module or a test suite.
        // Targets can depend on other targets in this package and products from dependencies.
        .executableTarget(
            name: "2025_2",
            resources: [
                .copy("Resources/1_input.txt"),
                .copy("Resources/1_test_input.txt"),
            ]
        ),
    ]
)
