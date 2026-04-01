paths_n2=(
    "/home/calin/Facultate/PPD/Laborator3_Tema/Tema/resources/16_n2.txt"
    "/home/calin/Facultate/PPD/Laborator3_Tema/Tema/resources/18_n2.txt"
    "/home/calin/Facultate/PPD/Laborator3_Tema/Tema/resources/1000_n2.txt"
    "/home/calin/Facultate/PPD/Laborator3_Tema/Tema/resources/100000_n2.txt"
)
paths_n1=(
    "/home/calin/Facultate/PPD/Laborator3_Tema/Tema/resources/16_n1.txt"
    "/home/calin/Facultate/PPD/Laborator3_Tema/Tema/resources/18_n1.txt"
    "/home/calin/Facultate/PPD/Laborator3_Tema/Tema/resources/1000_n1.txt"
    "/home/calin/Facultate/PPD/Laborator3_Tema/Tema/resources/100_n1.txt"
)


p=(2 4 8 16)
output="/home/calin/Facultate/PPD/Laborator3_Tema/Output.txt"
cd Tema || { echo "Directory 'Tema' not found"; exit 1; }
 
for j in "${!paths_n1[@]}"; do
    path_n1="${paths_n1[$j]}"
    path_n2="${paths_n2[$j]}"
    for value in "${p[@]}"; do
 	    for ((i=1; i<=10; i++)); do
            echo "Running Tema_var1 with np=$value, iteration $i for $path_n1 and $path_n2"
            mpirun -v --oversubscribe -np $value /home/calin/Facultate/PPD/Laborator3_Tema/Tema/Tema_var1 "$path_n1" "$path_n2" "$output"
 	done
     done
 done

for j in "${!paths_n1[@]}"; do
    path_n1="${paths_n1[$j]}"
    path_n2="${paths_n2[$j]}"
    for value in "${p[@]}"; do
 	    for ((i=1; i<=10; i++)); do
            echo "Running Tema_var2 with np=$value, iteration $i for $path_n1 and $path_n2"
            mpirun --oversubscribe -np $value /home/calin/Facultate/PPD/Laborator3_Tema/Tema/Tema_var2 "$path_n1" "$path_n2" "$output"
 	done
     done
 done
