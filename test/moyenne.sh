NB_ESSAI=100
FILE="./last"


echo -n > $FILE
for ((j = 3; j < 10; j++ )); do
	N=0
	for (( i = 0; i < $NB_ESSAI; i++ )); do
		N=$(($(ARG=`ruby -e "puts (1..$j).to_a.shuffle.join(' ')"`&&  ./push_swap  $ARG | wc -l) + N))
	done
	echo "[" $j "] ->\t" $((N / $NB_ESSAI))
	echo "[" $j "] ->\t" $((N / $NB_ESSAI)) >> $FILE
done

for ((j = 10; j <= 100; j = j + 10 )); do
	N=0
	for (( i = 0; i < $NB_ESSAI; i++ )); do
		N=$(($(ARG=`ruby -e "puts (1..$j).to_a.shuffle.join(' ')"`&&  ./push_swap  $ARG | wc -l) + N))
	done
	echo "[" $j "] ->\t" $((N / $NB_ESSAI))
	echo "[" $j "] ->\t" $((N / $NB_ESSAI)) >> $FILE
done

N=0
for (( i = 0; i < $NB_ESSAI ; i++ )); do
	N=$(($(ARG=`ruby -e "puts (1..500).to_a.shuffle.join(' ')"`&&  ./push_swap  $ARG | wc -l) + N))
done
echo "[ 500 ] ->\t" $((N / $NB_ESSAI))
echo "[ 500 ] ->\t" $((N / $NB_ESSAI)) >> $FILE