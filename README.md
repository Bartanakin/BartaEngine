## Requirements:
1. CMake
2. C++20 compiler other than UCRT
3. System Windows (at least this one was tested :) )
4. Make runner (optionally)


## Installation
- Clone the repo to your machine ```git clone https://github.com/Bartanakin/BartaEngine.git```

- Checkout to the correct branch with ```git checkout main-collision-for-UJ``` 
- Use ```make configure``` to set up the cmake project. You can use a different CMake Generator.
- Use ```make build_p``` to build the program.
- Use ```make run``` to run the program.

You should see a scene with green bounds, a red rectangle in the middle and three moving circles that bounce with each other.

You can open file `lib/Collisions/CheckCollisionVisitors/CircleAABBCheckCollisionVisitor.cpp`. This is where the code will be added.