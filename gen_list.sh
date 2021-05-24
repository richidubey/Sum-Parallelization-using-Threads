#  Generates list of numbers
#  
#  Copyright (C) 2021 Richi Dubey <richidubey@gmail.com>
# 
#  This work is licensed under the terms of the GNU GPL, version 2.  See
#  the LICENSE file in the top-level directory.
#
 
#!/bin/bash
#echo "Bash version ${BASH_VERSION}..."

begin="NULL"
step="NULL"
out="NULL"
 
#getopts is used to parse command line arguments 
#(Learn more: https://wiki.bash-hackers.org/howto/getopts_tutorial)
 
#getopts is builtin and is defined in POSIX.
while getopts ":b:s:e:o:" opt; do
  case $opt in
    b)
      echo "Beginning: $OPTARG" >&1 #In bash File Descriptor 1 (&1) is the STDOUT 
      begin=$OPTARG
      ;;
    s)
      echo "Step value: $OPTARG" >&1 #In bash File Descriptor 1 (&1) is the STDOUT
      step=$OPTARG
      ;;
    e)
      echo "Ending: $OPTARG" >&1 #In bash File Descriptor 1 (&1) is the STDOUT 
      end=$OPTARG
      ;;
    o)
      echo "Output: $OPTARG" >&1 #In bash File Descriptor 1 (&1) is the STDOUT
      out=$OPTARG
      ;;
    \?)
      echo ""
      echo "----------------------------------------------"
      echo "Invalid option: -$OPTARG" >&2
      echo "Correct usage: ./gen_list.sh  -b beginning_num -s step_value -e ending_number -o required_output_file.txt  ">&2
      echo "Example: $ ./gen_list.sh  -b 1 -s 2 -e 100 -o num_list_100_2.txt  ">&2
      echo "ERROR! EXITING SCRIPT without generating output" >&2
      echo "----------------------------------------------"
      exit 1
      ;;
    :)
      echo ""
      echo "----------------------------------------------"
      echo "Option -$OPTARG requires an argument." >&2
      echo "Correct usage: ./gen_list.sh  -b beginning_num -s step_value -e ending_number -o required_output_file.txt  ">&2
      echo "Example: $ ./gen_list.sh  -b 1 -s 2 -e 100 -o num_list_100_2.txt  ">&2
      echo "ERROR! EXITING SCRIPT without generating output" >&2
      echo "----------------------------------------------"
      exit 1
      ;;
  esac
done

#Check if all the arguments were passed. 
#Important because getopts only parses the arguments that were passed, and does not check for missing arguments. 
if [[ $begin -eq "NULL"  ||  $step -eq "NULL"  ||  $end -eq "NULL" || "$out" = "NULL" || $begin -gt $end || $step -le 0 ]]
then
      echo ""
      echo "----------------------------------------------"
      echo "Not all arguments specified or bad command usage" >&2
      echo "Beginning number has to be positive and less than or equal to ending number; step has to be positive" >&2
      echo "Correct usage: ./gen_list.sh  -b beginning_num -s step_value -e ending_number -o required_output_file.txt" >&2
      echo "Example: $ ./gen_list.sh -b 1 -s 3 -e 1000000 -o output.txt"
      echo "ERROR! EXITING SCRIPT without generating output" >&2
      echo "----------------------------------------------"
      exit 1
fi

SUM=0

echo ""
echo ""


COUNT=$(( (end - begin)/step + 1 ))
echo "Writing ..."
echo ""
echo $COUNT>$out
i=1
for (( i = $begin; i<=$end; i+=$step))
  do 
     SUM=$(( SUM + i))
     echo "$i" >>${out}
 done
 
echo $SUM>>$out

echo "******************************"
echo "Output Successfully saved in file" $out "in format: "
echo "Total Count of Nums (="$COUNT")"
echo "First Num(="$begin")"
echo "Second Num" 
echo "..."
echo "Last Num(="$((i - step))")"
echo "Total Sum(="$SUM")"
echo "******************************"
