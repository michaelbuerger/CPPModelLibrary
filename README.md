# CPPModelLibrary
###### Ideals: Fast, Cross-Platform, Easy to use with OpenGL and Direct3D
----
## Model formats to support reading from and writing to (likely in this order):
#### Priority:
- ASCII OBJ
- STL
- Collada
- FBX
- 3DS

#### Later:
- IGES
- STEP
- VRML/X3D
----
## Notes:
CPP Version: 17
Uses libraries: 
- spdlog (included, required)
- cloc (not included, not required)
- valgrind (not included, not required)
----
## Running
**The following commands can be run from a terminal in the project directory**:

- ```make all``` or ```make```: Says what each make function does
- ```make make-project```: Builds necessary dependencies with CMake
- ```make build-project```: Builds the library
- ```make execute-project```: Executes main.cpp
- ```make build-execute project```: Runs ```build-project``` then ```execute-project```
- ```make qea```: Runs ```make-project``` then ```build-project``` then ```execute-project```
- ```make line-count```: Queries line counts of various parts of the library's code
- ```make clean```: Runs all of the following clean commands
- ```make clean-bin```: Clears bin directory of engine (not including sub-directories)
----
## Links:
**Trello:** [https://trello.com/b/bgSspJZA/cppmodellibrary](https://trello.com/b/bgSspJZA/cppmodellibrary "Hi there :)") 
**GitHub:** [https://github.com/popwser/CPPModelLibrary](https://github.com/popwser/CPPModelLibrary "How are you today") 
**Good Markdown Editor**: [https://pandao.github.io/editor.md](https://pandao.github.io/editor.md "I hope you are well :D") 