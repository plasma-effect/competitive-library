COPTS = [
    "-std=c++20",
    "-Wall",
    "-Wextra",
    "-Wshadow",
    "-Wconversion",
    "-Wno-sign-conversion",
    "-Werror",
    "-fsanitize=undefined,address",
    "-fno-sanitize-recover=all",
]
LINKOPTS = [
    "-fsanitize=undefined,address",
]

def library_cc_test(name, srcs = []):
    return native.cc_test(
        name = name,
        srcs = srcs,
        deps = [
            "//:competitive_library",
            "@googletest//:gtest",
            "@googletest//:gtest_main",
        ],
        copts = COPTS,
        linkopts = LINKOPTS,
    )
