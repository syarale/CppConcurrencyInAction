
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

cc_library(
    name = "threadsafe_stack",
    srcs = ["threadsafe_stack.h"],
)

cc_binary(
    name = "threadsafe_stack_test",
    srcs = ["threadsafe_stack_test.cc"],
    deps = [
        ":threadsafe_stack",
    ],
    linkopts = ["-pthread"],
)

cc_library(
    name = "hierarchical_mutex",
    srcs = ["hierarchical_mutex.h"],
)

cc_binary(
    name = "hierarchical_mutex_test",
    srcs = ["hierarchical_mutex_test.cc"],
    deps = [
        ":hierarchical_mutex",
    ],
    linkopts = ["-pthread"]
)