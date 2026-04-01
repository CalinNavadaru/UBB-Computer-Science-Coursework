paths=(
    "/resources/10_10_3_3.txt"
    "/resources/1000_1000_3_3.txt"
    "/resources/10000_10000_3_3.txt"
)


p=(2 4 8 16)
output="/home/calin/Facultate/PPD/Laborator2_Tema/Output.txt"
 cd Java || { echo "Directory 'Java' not found"; exit 1; }
 for path in "${paths[@]}"; do
     for value in "${p[@]}"; do
 	for ((i=1; i<=10; i++)); do
 		./gradlew run --args="'/home/calin/Facultate/PPD/Laborator2_Tema/Java$path' '$output' '$value'"
 	done
     done
 done

cd ../Cplusplus || { echo "Directory 'Cplusplus' not found"; exit 1; }
g++ -O3 -std=c++20 -pthread -o main.exe main.cpp
for path in "${paths[@]}"; do
	for value in "${p[@]}"; do
		for ((i=1; i<=10; i++)); do
			./main.exe "/home/calin/Facultate/PPD/Laborator2_Tema/Cplusplus$path" "$output" "$value"
		done
	done
done
