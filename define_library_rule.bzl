def cl_library(name, deps = []):
    return native.cc_library(
        name = name,
        hdrs = ["include/" + name + ".hpp"],
        deps = deps,
        strip_include_prefix = "include",
        visibility = ["//visibility:public"],
    )
