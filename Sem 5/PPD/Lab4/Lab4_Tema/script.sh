p=(4 6 8 16)
p_r=(1 2)
output="/home/calin/Facultate/PPD/Laborator4_Tema_1/Output.txt"
cd Laborator4 || { echo "Directory 'Tema' not found"; exit 1; }
 
for value in "${p[@]}"; do
    for value1 in "${p_r[@]}"; do
        for ((i=1; i<=10; i++)); do
            echo "Running Tema_4_1 with np=$value, nr=$value1, iteration $i"
            ./gradlew run --args="'$value' '$value1' '$output'" 
            done
    done
done