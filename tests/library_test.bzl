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

def library_cc_test(target):
    return native.cc_test(
        name = target + "_test",
        srcs = [target + ".cpp"],
        deps = [
            "//:" + target,
            "@googletest//:gtest",
            "@googletest//:gtest_main",
        ],
        copts = COPTS,
        linkopts = LINKOPTS,
    )
