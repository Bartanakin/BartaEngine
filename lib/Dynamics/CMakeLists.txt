add_subdirectory(Timers)

target_sources(${LIBRARY_NAME} PUBLIC
    "ConstVelocityDynamicsUpdateStrategy.cpp"
)