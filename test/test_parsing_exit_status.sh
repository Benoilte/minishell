#! /bin/bash

# print command no found
echo 'hello (command not found) exit_status 127'
hello
echo $?
echo

# print space
echo "(print space) (exit_status == 0)"
echo "       	"
echo $?
echo

# syntax error near unexpected token `>'
echo '>>>test1 (exit_status == 2)'
>>>test1
echo $?
echo

# syntax error near unexpected token `>>'
echo '>>>>test1 (exit_status == 2)'
>>>>test1
echo $?
echo

# syntax error near unexpected token `>>'
echo '>>>>>test1 (exit_status == 2)'
>>>>>test1
echo $?
echo

# syntax error near unexpected token `|'
echo '   | ls (exit_status == 2)'
    | ls
echo $?
echo

# syntax error near unexpected token `|'
echo '   | ls (exit_status == 2)'
ls |    | ls
echo $?
echo
