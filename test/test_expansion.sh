#! minishell

# print only a dollar sign
echo 'echo $'
echo $
echo

# print exit status
echo 'echo $?'
echo $?
echo

# print process id
echo 'echo $$'
echo $$
echo

# print existing env variable
echo 'echo $USER'
echo $USER
echo

# print wrong env variable
echo 'echo $WRONG_ENV_VAR'
echo $WRONG_ENV_VAR
echo
