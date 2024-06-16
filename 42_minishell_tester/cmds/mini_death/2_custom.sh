# **************************************************************************** #
#                                   CUSTOM                                     #
# **************************************************************************** #

mkdir -p s/s/s/s
cd s/s/s/s
rm -rf ../../../../s
cd ..
cd ..
cd ..
echo $?
cd ..
echo $?
env | grep PWD

mkdir -p s/s/s/s
cd s/s/s/s
rm -rf ../../../../s
cd ..
unset PATH
grep
echo $?
PATH=$HOME
grep
echo $?