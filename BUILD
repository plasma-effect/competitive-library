cc_library(
    name = "competitive_library",
    hdrs = glob(["include/*.hpp"]),
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
    deps = [
        "@custom_ac_library//:ac_library",
        "@boost//:range"
    ],
)
