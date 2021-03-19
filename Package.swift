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
            url: "https://github.com/zoho/Apptics/releases/download/\(version)/Apptics.zip", checksum: "55c5f7dd10187b090056f4dc587c3d902587a5513148cd8454d432d5d768079b")
    ]
)
