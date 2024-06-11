echo |< echo segf

# echo segf >| echo is this invalid #special operator that we dont need to handle

echo >          >           < "echo"

echo >          >         | echo kekw

echo >          >         | echo super valid

echo <          <         > echo

echo <  < <         > ok

echo <  < | echo ok

echo <  < |    < ok

echo <      < |    > echo

echo >>| echo super valid

echo >>< "echo"

echo < < < echo seegf

echo > > < "echo"

echo > > | echo kekw

echo > > | echo super valid

echo < < > echo

echo < < < > ok

echo >>| echo kekw

echo | < echo segf

echo <<| echo ok

echo <<|< ok

echo <<|> echo

echo <<> echo

echo <<<> ok

echo segfault <"<<<"<<amazing
.
amazing

echo seg < > echo seg

echo seg > < echo segf

echo seg < < > echo segf

echo seg < < < > echo segf

echo segf > | echo is this invalid

echo segf < | < echo super valid

echo < < | echo ok

echo < < | < ok

echo < < | > echo

echo segfault < " < < < " < < amazing #actually correct, multiners are messed up
.
amazing

echo seg <  > echo seg

echo seg >  < echo segf

echo seg <      < > echo segf

echo seg <      < <    > echo segf

echo <      <     < echo seegf

echo |      < echo segf

echo segf >     | echo is this invalid

echo segf <         |        < echo super valid

echo segfault <"    <   <   <"  <   <   amazing
.
amazing

# echo seg <> echo seg #special <> operator for opening file for reading and writing

echo seg >< echo segf

echo seg <<> echo segf

echo seg <<<> echo segf

# echo <<< echo seegf #no need to handle herestring

echo segf <|< echo super valid

# echo test |  <<lala #broken test I guess

echo | > la

echo yolo | eco test >> test

echo echo echo echo echo echo

unset $PATH
ECHO -nnnn

unset $PATH
ECHO -n

unset $PATH
ECHo -n

unset $PATH
ECHO "-n"

unset $PATH
EcHO -nnnn

unset $PATH
echo -nnnnnnnn








