# NYU ProcDesign Development Template

## Questions
### Why do you think the reason for these different testing approaches are? What are their advantages and disadvantages?
Registries contain information about packages which you can use to import into your projects. They can be found in the vcpkg-configuration.json file.

### What is a package?
Packages are source code files that can be imported into projects and used in order to accelerate development and avoid remaking commonly used code. 

### What's the difference between an interface library and a "normal" library or executable? Can you think of any uses for this besides System Verilog files? (Think about source code used for generic programming)
Interface libraries are libraries that have code that isn't compiled immediately whereas normal libraries and executables are compiled like normal.

### What is a top module?
Top modules are models that are created by the verilator tool and are used expose the inputs and outputs for the module to the testing code.