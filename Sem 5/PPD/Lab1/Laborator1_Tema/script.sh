paths=(
    "/resources/3_3_3_3.txt"
    "/resources/10_10_3_3.txt"
    "/resources/10_10000_5_5.txt"
    "/resources/1000_1000_5_5.txt"
    "/resources/10000_10_5_5.txt"
    "/resources/10000_10000_5_5.txt"
)

p=(1 2 4 8 16)
output="/home/calin/Facultate/PPD/Laborator1_Tema/Output.txt"
 cd Java || { echo "Directory 'Java' not found"; exit 1; }
 for path in "${paths[@]}"; do
     for value in "${p[@]}"; do
 	for ((i=1; i<=10; i++)); do
 		./gradlew run --args="'/home/calin/Facultate/PPD/Laborator1_Tema/Java/src/main$path' '$output' '$value'"
 	done
     done
 done

# cd ..
cd Cplusplus || { echo "Directory 'Cplusplus' not found"; exit 1; }
g++ -O3 -o main2.exe main.cpp
for path in "${paths[@]}"; do
	for value in "${p[@]}"; do
		for ((i=1; i<=10; i++)); do
			./main2.exe "/home/calin/Facultate/PPD/Laborator1_Tema/Cplusplus$path" "$output" "$value"
		done
	done
done
cd ..
cd Cplusplus2 || { echo "Directory 'Cplusplus2' not found"; exit 1; }
g++ -O3 -o main2.exe main.cpp
for path in "${paths[@]}"; do
	for value in "${p[@]}"; do
		for ((i=1; i<=10; i++)); do
			./main2.exe "/home/calin/Facultate/PPD/Laborator1_Tema/Cplusplus2$path" "$output" "$value"
		done
	done
done
