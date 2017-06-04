add_executable(caf_test caf_test.cpp)

# Uncomment to temporarily add CAF source to project for debugging (make sure it's the same version!)
#add_subdirectory(/Users/eric/IdeaProjects/actor-framework caf-source)

target_link_libraries(caf_test CONAN_PKG::caf)