// swift-tools-version:5.3
import PackageDescription

let version = "1.0.0-alpha"
let package = Package(
    name: "Apptics",
    platforms: [.iOS(.v10)],
    products: [
        .library(
            name: "Apptics",
            targets: ["Apptics"]),
    ],
    targets: [
        .binaryTarget(
            name: "Apptics",
            url: "https://github.com/zoho/Apptics/blob/v\(version)/Apptics.zip?raw=true", checksum: "383f7951bc7429d85d19c7bc4edb2ce6b4fadcbf8e1ff47238a80c6c4f246c62")
    ]
)
