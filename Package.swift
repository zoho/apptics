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
            url: "https://github.com/zoho/Apptics/releases/download/\(version)/Apptics.zip", checksum: "adf254c014ca10d1887b6c03b75a8fa27eb29c13fd5be7064648d52d753dea58")
    ]
)
