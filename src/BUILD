
cc_binary(
    name = "thread_guard",
    srcs = ["thread_guard.cc"],
    linkopts = ["-pthread"]
)

cc_binary(
    name = "scoped_thread",
    srcs = ["scoped_thread.cc"],
    linkopts = ["-pthread"]
)


cc_library(
    name = "joining_thread",
    srcs = ["joining_thread.h"],
)

cc_binary(
    name = "joining_thread_test",
    srcs = ["joining_thread_test.cc"],
    deps = [
      ":joining_thread",
    ],
    linkopts = ["-pthread"]
)