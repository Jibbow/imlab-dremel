# ---------------------------------------------------------------------------
# IMLAB
# ---------------------------------------------------------------------------

# ---------------------------------------------------------------------------
# Files
# ---------------------------------------------------------------------------

file(GLOB_RECURSE SRC_CC "src/*.cc")

# ---------------------------------------------------------------------------
# Libraries
# ---------------------------------------------------------------------------

add_library(imlab SHARED ${SRC_CC})
target_link_libraries(imlab gflags Threads::Threads)

# ---------------------------------------------------------------------------
# Linting
# ---------------------------------------------------------------------------

add_cpplint_target(lint_src "${SRC_CC}")
list(APPEND lint_targets lint_src)

