add_llvm_library(LLVMPJT MODULE            # Name of the shared library that you will generate
       operation_statistics.cpp            # Your pass
       traverse_bb.cpp
       PLUGIN_TOOL
       opt
)