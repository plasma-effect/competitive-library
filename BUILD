filegroup(
    name = "cl_headers",
    srcs = glob(["include/*.hpp"]),
    visibility = ["//visibility:public"],
)

cc_library(
    name = "competitive_library",
    hdrs = [":cl_headers"],
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
    deps = [
        "@boost//:container",
        "@custom_ac_library//:ac_library",
    ],
)
