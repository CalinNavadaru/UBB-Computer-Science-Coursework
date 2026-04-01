p=(6 8 16)
p_r=(2 4)
m=(50 100)
output="/home/calin/Facultate/Materii/PPD/Laborator5/Output.txt"

for value in "${p[@]}"; do
    for value1 in "${p_r[@]}"; do
      for value2 in "${m[@]}"; do
        for ((i=1; i<=10; i++)); do
            echo "Running Tema_5 with np=$value, nr=$value1, maxSize=$value2, iteration $i"
            ./gradlew run --args="'$value' '$value1' '$output' '$value2'"
            done
        done
    done
done