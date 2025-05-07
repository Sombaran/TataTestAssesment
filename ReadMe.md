## Set up to run the project via VSCODE
1. Clone the project in vscode ENV(Linux)
2. Click on run from IDE
3. Program will ask for user input

## Set up to run the project via Terminal
1. Run command g++ ${fileName.cpp} -o ${executableFile} -o stdc++=11


## ## Set up to run the project via MakeFile
1. Create a file by the name "MakeFile"
2. Put below command in the Makefile.

```MakeFile
all : prog01

prog01 : tataTechnologiesAssesment.cpp
        g++ -o prog01  tataTechnologiesAssesment.cpp

clean:
        rm prog01
```
3. Navigate to root folder of the project and run Make
 
