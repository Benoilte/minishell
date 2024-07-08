#! minishell

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

# syntax error near unexpected token `<'
echo '<<<test1 (exit_status == 2)'
<<<test1
echo $?
echo

# syntax error near unexpected token `<<'
echo '<<<<test1 (exit_status == 2)'
<<<<test1
echo $?
echo

# syntax error near unexpected token `<<<'
echo '<<<<<test1 (exit_status == 2)'
<<<<<test1
echo $?
echo

# syntax error near unexpected token `<<<'
echo '<<<<<<test1 (exit_status == 2)'
<<<<<<test1
echo $?
echo

# syntax error near unexpected token `<'
echo '>< (exit_status == 2)'
><
echo $?
echo

# syntax error near unexpected token `>'
echo '<> (exit_status == 2)'
<>
echo $?
echo

# syntax error near unexpected token `('
echo '< file( (exit_status == 2)'
< file(
echo $?
echo

# syntax error near unexpected token `)'
echo '> file) (exit_status == 2)'
> file)
echo $?
echo

# syntax error near unexpected token `&'
echo '> file& (exit_status == 2)'
> file&
echo $?
echo

# syntax error near unexpected token `;'
echo '> file; (exit_status == 2)'
> file;
echo $?
echo

# syntax error near unexpected token `newline'
echo '> (exit_status == 2)'
>
echo $?
echo

# syntax error near unexpected token `newline'
echo '> (exit_status == 2)'
<
echo $?
echo

# syntax error near unexpected token `newline'
echo '> (exit_status == 2)'
< #file
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

# syntax error near unexpected token `('
echo 'salut( (exit_status == 2)'
salut(
echo $?
echo

# syntax error near unexpected token `)'
echo 'salut( (exit_status == 2)'
salut)
echo $?
echo

# syntax error near unexpected token `;'
echo 'salut; (exit_status == 2)'
salut;
echo $?
echo

# syntax error near unexpected token `&'
echo 'salut& (exit_status == 2)'
salut&
echo $?
echo

# syntax error near unexpected token `unclosed quotes'
echo "echo' (exit_status == 2)"
echo'
echo $?
echo

# syntax error near unexpected token `unclosed quotes'
echo 'echo" (exit_status == 2)'
echo"
echo $?
echo
