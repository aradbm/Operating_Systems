OS - Task 5

Introduction
The pipeline code demonstrates a simple pipeline architecture using active objects. Each stage of the pipeline performs a specific operation on the numbers passed through. The pipeline stages are as follows:

printAndCheckPrime: Prints the number and checks if it is prime.
subtractThirteen: Subtracts 13 from the number.
addTwoAndPrint: Adds 2 to the number and prints the new number.
The pipeline stages are connected sequentially, with the output of one stage becoming the input of the next stage.

Dependencies
The code has the following dependencies:

gcc (GNU Compiler Collection)
pthread (POSIX threads library)
Make sure you have these dependencies installed before building and running the code.

Building the Code
To build the pipeline code, follow these steps:

Clone the repository to your local machine.
Open a terminal and navigate to the repository's root directory.
Run the following command to build the code:
make
This will compile the source files and create the executable file st_pipeline.
Running the Pipeline
Once you have built the code, you can run the pipeline with the following command:


./st_pipeline [tasks] [seed]
tasks (optional): The number of tasks to be processed by the pipeline. If not provided, the default is 10.
seed (optional): The seed for the random number generator. If not provided, the current time is used as the seed.
The pipeline will process the specified number of tasks. Each task involves generating a random number, enqueueing it into the first stage of the pipeline, and observing the transformations applied by each stage.

Examples:
Task_5$ ./st_pipeline 5 8
Enqueuing: 547896
------------------------------------------------------
Number: 547896, is Prime: False
Number: 547907, is Prime: False
Number: 547894, is Prime: False
New Number: 547896
Enqueuing: 630744
------------------------------------------------------
Number: 630744, is Prime: False
Number: 630755, is Prime: False
Number: 630742, is Prime: False
New Number: 630744
Enqueuing: 246242
------------------------------------------------------
Number: 246242, is Prime: False
Number: 246253, is Prime: False
Number: 246240, is Prime: False
New Number: 246242
Enqueuing: 247549
------------------------------------------------------
Number: 247549, is Prime: False
Number: 247560, is Prime: False
Number: 247547, is Prime: True
New Number: 247549
Enqueuing: 268311
------------------------------------------------------
Number: 268311, is Prime: False
Number: 268322, is Prime: False
Number: 268309, is Prime: False
New Number: 268311

////////////////////////////////////

/Task_5$ ./st_pipeline
Enqueuing: 781735
------------------------------------------------------
Number: 781735, is Prime: False
Number: 781746, is Prime: False
Number: 781733, is Prime: True
New Number: 781735
Enqueuing: 735294
------------------------------------------------------
Number: 735294, is Prime: False
Number: 735305, is Prime: False
Number: 735292, is Prime: False
New Number: 735294
Enqueuing: 571434
------------------------------------------------------
Number: 571434, is Prime: False
Number: 571445, is Prime: False
Number: 571432, is Prime: False
New Number: 571434
Enqueuing: 89981
------------------------------------------------------
Number: 89981, is Prime: False
Number: 89992, is Prime: False
Number: 89979, is Prime: False
New Number: 89981
Enqueuing: 66014
------------------------------------------------------
Number: 66014, is Prime: False
Number: 66025, is Prime: False
Number: 66012, is Prime: False
New Number: 66014
Enqueuing: 560898
------------------------------------------------------
Number: 560898, is Prime: False
Number: 560909, is Prime: False
Number: 560896, is Prime: False
New Number: 560898
Enqueuing: 881661
------------------------------------------------------
Number: 881661, is Prime: False
Number: 881672, is Prime: False
Number: 881659, is Prime: False
New Number: 881661
Enqueuing: 834969
------------------------------------------------------
Number: 834969, is Prime: False
Number: 834980, is Prime: False
Number: 834967, is Prime: False
New Number: 834969
Enqueuing: 806343
------------------------------------------------------
Number: 806343, is Prime: False
Number: 806354, is Prime: False
Number: 806341, is Prime: False
New Number: 806343
Enqueuing: 289069
------------------------------------------------------
Number: 289069, is Prime: False
Number: 289080, is Prime: False
Number: 289067, is Prime: True
New Number: 289069

Cleaning Up
To clean up the compiled object files and executable, you can use the following command:

go
Copy code
make clean
This will remove all the object files (*.o) and the st_pipeline executable from the
