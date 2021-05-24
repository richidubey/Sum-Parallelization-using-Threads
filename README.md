# Sum-Parallelization-using-Threads

Visualize performance benefits (in microsecond granularity) in finding sum of large array of numbers using threads.    
Includes a tool that generates a list of number when provided the step value (difference between consecutive numbers) and the starting, ending number.    
A sample input file is provided (*input.txt*) that stores 500000 numbers, starting at 1 with a step value of 2.    

## Set up

To download the repository and compile the program, run the following commands:    

```bash
git clone https://github.com/richidubey/Sum-Parallelization-using-Threads.git # replace [richidubey] with your github username if you fork first.
cd Sum-Parallelization-using-Threads
make
``` 

## Running

Run the following command to start the program. You have to specify the input file as the first parameter and the number of threads that should be used to calculate sum as the second parameter.    

```bash
./main input.txt 6
```

## Sample Runs

Output on a system with Intel® Core™ i7-7500U (4MB Cache), 4 Cores, 8 GB DDR4 SDRAM: 

```
$ ./main input.txt 2
Using 2 threads for parallelization
Number of elements in input: 500000

-----------------------------------------------------------------
Expected sum: 250000000000 
Sum calculated with help of threads: 250000000000
Sum calculated without help of threads: 250000000000

================================================================
    TASK              TIME TAKEN(in micro seconds)
================================================================
  With 2 Threads       1166
  Without Thread       936
----------------------------------------------------------------
```

```
$ ./main input.txt 8
Using 8 threads for parallelization
Number of elements in input: 500000

-----------------------------------------------------------------
Expected sum: 250000000000 
Sum calculated with help of threads: 250000000000
Sum calculated without help of threads: 250000000000

================================================================
    TASK              TIME TAKEN(in micro seconds)
================================================================
  With 8 Threads       739
  Without Thread       927
----------------------------------------------------------------
```


## Generating your own input file

Run the following command to generate a file having a list of numbers each seperated by a new line. The script *gen_list.sh* accepts the following parameters:     
- **-b** : Beginning Number    
- **-s** : Step value    
- **-e** : Ending Number    
- **-o** : Output File (This can act as the input file for main)  

Example:
```bash
$ ./gen_list.sh -b 1 -s 5 -e 1000000 -o output_1.txt
```
Output:
```
Beginning: 1
Step value: 5
Ending: 1000000
Output: output_1.txt

Writing ...

******************************
Output Successfully saved in file output_1.txt in format: 
Total Count of Nums (=200000)
First Num(=1)
Second Num
...
Last Num(=999996)
Total Sum(=99999700000)
```

The output file produced has the value of count of numbers (input size) in the first line, followed by the numbers (each separated on a new line) and the sum of all the numbers on the last line. The C file expects an input file in this format. This sum value provided in the last line is used to by the C program to check if the sum calculated is correct.     

If the command `./gen_list` gives an error, update its permission:    

```bash
sudo chmod +x ./gen_list
```

## Contributing

Contributions are actively encouraged. Please suggest changes/improvements by submitting issues. If you find a bug, please [email](mailto:richidubey@gmail.com) me, submit a pull request (I'll buy you a coffee as a thank you), or submit an issue.

