// swift-tools-version:5.3
import PackageDescription

let version = "1.0.0-beta4"
let package = Package(
    name: "Apptics",
    platforms: [.macOS(.v10_10), .iOS(.v9), .tvOS(.v9), .watchOS(.v2)],
    products: [
        .library(
            name: "Apptics",
            targets: ["Apptics"]),
    ],
    targets: [
        .binaryTarget(
            name: "Apptics",
            path: "Apptics.xcframework"
        ),
        .target(
            name: "scripts",
            path:"scripts"
        )
    ]
)
