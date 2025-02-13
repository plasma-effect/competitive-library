cc_library(
    name = "lib_expander",
    srcs = ["lib_expander.cpp"],
    hdrs = ["expander.hpp"],
    copts = [
        "-std=c++20",
        "-Wall",
        "-Wextra",
        "-Wshadow",
        "-Wconversion",
        "-Werror",
    ],
)

cc_test(
    name = "test_expander",
    srcs = ["test_expander.cpp"],
    copts = [
        "-std=c++20",
        "-Wall",
        "-Wextra",
        "-Wshadow",
        "-Wconversion",
        "-Werror",
        "-fsanitize=undefined,address",
        "-fno-sanitize-recover=all",
    ],
    linkopts = [
        "-fsanitize=undefined,address",
    ],
    deps = [
        ":lib_expander",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_binary(
    name = "expander",
    srcs = ["expander.cpp"],
    copts = [
        "-std=c++20",
        "-Wall",
        "-Wextra",
        "-Wshadow",
        "-Wconversion",
        "-Werror",
    ],
    deps = [":lib_expander"],
)
