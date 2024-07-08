#! minishell

echo "print PWD env var"
echo PWD: $PWD
echo OLDPWD: $OLDPWD
echo

echo "move to home directory"
cd
echo "Exit status : $?"
echo PWD: $PWD
echo OLDPWD: $OLDPWD
echo

echo "move again to home directory"
cd
echo "Exit status : $?"
echo PWD: $PWD
echo OLDPWD: $OLDPWD
echo

echo "move to file objs if exist"
cd objs/
echo "Exit status : $?"
echo PWD: $PWD
echo OLDPWD: $OLDPWD
echo

echo "move to file 42_school if exist"
cd 42_school/
echo "Exit status : $?"
echo PWD: $PWD
echo OLDPWD: $OLDPWD
echo

echo "move to file 42_school if exist"
cd 42_school/
echo "Exit status : $?"
echo PWD: $PWD
echo OLDPWD: $OLDPWD
echo

echo "test cmd pwd"
pwd
echo "Exit status : $?"
echo

echo "move one directory back"
cd ..
echo "Exit status : $?"
echo PWD: $PWD
echo OLDPWD: $OLDPWD
echo

echo "try cmd cd with too many argument"
cd .. ..
echo "Exit status : $?"
echo

echo "try cmd cd path not a directory"
cd /bin/ls
echo "Exit status : $?"
echo

echo "try cmd cd path not such file or directory"
cd hfrhfafkghkrfg
echo "Exit status : $?"
echo

echo "print PWD env var"
echo PWD: $PWD
echo OLDPWD: $OLDPWD
echo
