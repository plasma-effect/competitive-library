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

def library_cc_test(name, srcs = [], deps = []):
    if not name.endswith("_test"):
        fail("Error: name of 'library_cc_test' must have '_test' suffix ({})".format(name))
    target = name[:-len("_test")]
    if srcs == []:
        srcs = [target + ".cpp"]
    return native.cc_test(
        name = name,
        srcs = srcs,
        deps = deps + [
            "//:" + target,
            ":test_utils",
            "@googletest//:gtest",
            "@googletest//:gtest_main",
        ],
        copts = COPTS,
        linkopts = LINKOPTS,
    )
