#1. Count the number of students in the CSE department:
grep -i "CSE" record.txt | wc -l
#2  Display the record of students in the IT department:
grep -i "IT" record.txt
#3  Display the record of students who are not in the CSE department:
grep -vi "CSE" record.txt
#Count the number of girl students in the CSE department:
grep -i "CSE" record.txt | grep -i "F" | wc -l
#Display the record of girl students in the CSE department:
grep -i "CSE" record.txt | grep -i "F"