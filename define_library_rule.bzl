def cl_library(name, hdrs = [], deps = []):
    if hdrs == []:
        hdrs = ["include/" + name + ".hpp"]
    else:
        hdrs = ["include/" + n for n in hdrs]
    return native.cc_library(
        name = name,
        hdrs = hdrs,
        deps = deps,
        strip_include_prefix = "include",
        visibility = ["//visibility:public"],
    )
