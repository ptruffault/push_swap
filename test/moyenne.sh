NB_ESSAI=10
FILE="./test/last"
COURBE="./test/courbe"
PUSH_SWAP="./push_swap"

echo '' > $COURBE
echo '' > $FILE
echo '' > ./test/tmp
for ((j = 4; j < 50; j = j + 2 )); do
	SOMME=0
	for (( i = 0; i < $NB_ESSAI; i++ )); do
		SOMME=$((SOMME + $(($(ARG=`ruby -e "puts (1..$j).to_a.shuffle.join(' ')"`&&  $PUSH_SWAP  $ARG | wc -l))))) 
	done
	echo "[" $j "] ->\t" $((SOMME / $NB_ESSAI))
	echo "[" $j "] ->\t" $((SOMME / $NB_ESSAI)) >> ./test/tmp
	echo "$j,$((SOMME / $NB_ESSAI))" >> $COURBE
done

for ((j = 50; j < 100; j = j + 10)); do
	SOMME=0
	for (( i = 0; i < $NB_ESSAI; i++ )); do
		SOMME=$((SOMME + $(($(ARG=`ruby -e "puts (1..$j).to_a.shuffle.join(' ')"`&&  $PUSH_SWAP  $ARG | wc -l))))) 
	done
	echo "[" $j "] ->\t" $((SOMME / $NB_ESSAI))
	echo "[" $j "] ->\t" $((SOMME / $NB_ESSAI)) >> ./test/tmp
	echo "$j,$((SOMME / $NB_ESSAI))" >> $COURBE
done


for ((j = 100; j <= 500; j = j + 25 )); do
	SOMME=0
	for (( i = 0; i < $NB_ESSAI; i++ )); do
		SOMME=$((SOMME + $(($(ARG=`ruby -e "puts (1..$j).to_a.shuffle.join(' ')"`&&  $PUSH_SWAP  $ARG | wc -l))))) 
	done
	echo "[" $j "] ->\t" $((SOMME / $NB_ESSAI))
	echo "[" $j "] ->\t" $((SOMME / $NB_ESSAI)) >> ./test/tmp
	echo "$j,$((SOMME / $NB_ESSAI))" >> $COURBE
done

for ((j = 600; j <= 1500; j = j + 100 )); do
	SOMME=0
	for (( i = 0; i < $NB_ESSAI; i++ )); do
		SOMME=$((SOMME + $(($(ARG=`ruby -e "puts (1..$j).to_a.shuffle.join(' ')"`&&  $PUSH_SWAP  $ARG | wc -l))))) 
	done
	echo "[" $j "] ->\t" $((SOMME / $NB_ESSAI))
	echo "[" $j "] ->\t" $((SOMME / $NB_ESSAI)) >> ./test/tmp
	echo "$j,$((SOMME / $NB_ESSAI))" >> $COURBE
done
cat ./test/tmp > $FILE