package cs.ubbcluj.ro;

import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.io.File;
import java.util.List;
import java.util.Scanner;

class ThreadLinii extends Thread {
	int[][] matrix;
	int[][] conv;
	int[][] result;
	int N, M, n, m, startI, endI;

	ThreadLinii(int[][] matrix, int[][] conv, int[][] result, int N, int M, int n, int m, int startI, int endI) {
		this.startI = startI;
		this.endI = endI;
		this.matrix = matrix;
		this.conv = conv;
		this.result = result;
		this.N = N;
		this.n = n;
		this.M = M;
		this.m = m;
	}

	public void run() {
		for (int i = startI; i < endI; i++) {
			for (int j = (m - 1) / 2; j <= M + (m - 1) / 2 - 1; j++) {
				Main.operation(matrix, conv, result, i, j);
			}
		}
	}
}

class ThreadDistributie extends Thread {
	int[][] matrix;
	int[][] conv;
	int[][] result;
	int N;
	int M;
	int n;
	int m;
	List<Integer> index_i = new ArrayList<>();
	List<Integer> index_j = new ArrayList<>();

	ThreadDistributie(int[][] matrix, int[][] conv, int[][] result, int N, int M, int n, int m) {
		this.matrix = matrix;
		this.conv = conv;
		this.result = result;
		this.N = N;
		this.n = n;
		this.M = M;
		this.m = m;
	}

	public void add(int i, int j) {
		index_i.add(i);
		index_j.add(j);
	}

	public void run() {
		for (int i = 0; i < index_j.size(); i++) {
			Main.operation(matrix, conv, result, index_i.get(i), index_j.get(i));
		}
	}
}

class ThreadColoane extends Thread {
	int[][] matrix;
	int[][] conv;
	int[][] result;
	int N, M, n, m, startJ, endJ;

	ThreadColoane(int[][] matrix, int[][] conv, int[][] result, int N, int M, int n, int m, int startJ, int endJ) {
		this.startJ = startJ;
		this.endJ = endJ;
		this.matrix = matrix;
		this.conv = conv;
		this.result = result;
		this.N = N;
		this.n = n;
		this.M = M;
		this.m = m;
	}

	public void run() {
		for (int j = startJ; j < endJ; j++) {
			for (int i = (n - 1) / 2; i <= N + (n - 1) / 2 - 1; i++) {
				Main.operation(matrix, conv, result, i, j);
			}
		}
	}
}

class ThreadBlocuri extends Thread {
	int[][] matrix;
	int[][] conv;
	int[][] result;
	int N, M, n, m, startI, endI, startJ, endJ;

	ThreadBlocuri(int[][] matrix, int[][] conv, int[][] result, int N, int M, int n, int m, int startI, int endI, int startJ, int endJ) {
		this.startI = startI;
		this.endI = endI;
		this.matrix = matrix;
		this.conv = conv;
		this.result = result;
		this.N = N;
		this.n = n;
		this.M = M;
		this.m = m;
		this.startJ = startJ;
		this.endJ = endJ;
	}

	public void run() {
		for (int i = startI; i <= endI; i++) {
			for (int j = startJ; j <= endJ; j++) {
				Main.operation(matrix, conv, result, i, j);
			}
		}
	}
}

public class Main {

	static int N, M, n, m, p;

	private static void initMatrix(int[][] matrix, int iStart, int iFinal, int jStart, int jFinal, Scanner scanner) {
		for (int i = iStart; i <= iFinal; i++) {
			for (int j = jStart; j <= jFinal; j++) {
				matrix[i][j] = scanner.nextInt();
			}
		}
	}

	private static void border(int[][] matrix) {
		for (int j = (m - 1) / 2; j <= M + (m - 1) / 2; j++) {
			matrix[(n - 1) / 2 - 1][j] = matrix[(n - 1) / 2][j];
			matrix[(n - 1) / 2 + N][j] = matrix[(n - 1) / 2 + N - 1][j];
		}

		for (int i = (n - 1) / 2; i <= N + (n - 1) / 2; i++) {
			matrix[i][(m - 1) / 2 - 1] = matrix[i][(n - 1) / 2];
			matrix[i][(m - 1) / 2 + M] = matrix[i][(m - 1) / 2 + M - 1];
		}

		matrix[(n - 1) / 2 - 1][(m - 1) / 2 - 1] = matrix[(n - 1) / 2][(m - 1) / 2];
		matrix[(n - 1) / 2 + N - 1][(m - 1) / 2 + M - 1] = matrix[N + (n - 1) / 2][M + (m - 1) / 2];
		matrix[(n - 1) / 2 - 1][(m - 1) / 2 + M] = matrix[(n - 1) / 2][(m - 1) / 2 + M - 1];
		matrix[N + 1][0] = matrix[N][1];
		matrix[N + (n - 1) / 2][(m - 1) / 2 - 1] = matrix[N + (n - 1) / 2 - 1][(m - 1) / 2];
	}

	public static void operation(int[][] matrix, int[][] conv, int[][] result, int i, int j) {

		result[i - (n - 1) / 2][j - (m - 1) / 2] = 0;
		for (int l = i - (n - 1) / 2, t = 0; l <= i + (n - 1) / 2; l++, t++) {
			for (int c = j - (m - 1) / 2, q = 0; c <= j + (m - 1) / 2; c++, q++) {
				result[i - (n - 1) / 2][j - (m - 1) / 2] += matrix[l][c] * conv[t][q];
			}
		}
	}

	private static void sequential(int[][] matrix, int[][] conv, int[][] result) {
		for (int i = (n - 1) / 2; i <= N + (n - 1) / 2 - 1; i++) {
			for (int j = (m - 1) / 2; j <= M + (m - 1) / 2 - 1; j++) {
				operation(matrix, conv, result, i, j);
			}
		}
	}

	public static void main(String[] args) {
		System.out.println(Arrays.toString(args));
		String pathInput = args[0];
		String pathOutput = args[1];
		try {
			File myFile = new File(pathInput);
			FileWriter outputFile = new FileWriter(pathOutput, true);
			Scanner scanner = new Scanner(myFile);
			N = scanner.nextInt();
			M = scanner.nextInt();
			n = scanner.nextInt();
			m = scanner.nextInt();
			p = Integer.parseInt(args[2]);

			int[][] matrix = new int[N + (n - 1)][M + (m - 1)];
			int[][] result = new int[N][M];
			int[][] conv = new int[n][m];
			initMatrix(matrix, (n - 1) / 2, (n - 1) / 2 + N - 1, (m - 1) / 2, (m - 1) / 2 + M - 1, scanner);
			initMatrix(conv, 0, n - 1, 0, m - 1, scanner);
			border(matrix);

			long startTime = System.nanoTime();
			sequential(matrix, conv, result);
			long stopTime = System.nanoTime();
			System.out.println("Secvential " + (stopTime - startTime));
			outputFile.write(N + " " + M + " " + n + " " + m + " secvential" + " " + "JAVA " + (stopTime - startTime) + "\n");

			int[][] result2 = new int[N][M];
			ThreadLinii[] threadList = new ThreadLinii[p];
			startTime = System.nanoTime();
			int start = 0, end = N / p, rest = N % p;
			for (int i = 0; i < threadList.length; i++) {
				if (rest > 0) {
					end += 1;
					rest -= 1;
				}
				threadList[i] = new ThreadLinii(matrix, conv, result2, N, M, n, m, (n - 1) / 2 + start, (n - 1) / 2 + end);
				threadList[i].start();
				start = end;
				end = start + N / p;
			}
			for (ThreadLinii threadLinii : threadList) {
				threadLinii.join();
			}
			stopTime = System.nanoTime();
			System.out.println("Pe linii " + (stopTime - startTime));
			System.out.println(Arrays.deepEquals(result, result2));
			outputFile.write(N + " " + M + " " + n + " " + m + " linii " + p + " " + "JAVA " + (stopTime - startTime) + "\n");

			int[][] result3 = new int[N][M];
			ThreadColoane[] thread2List = new ThreadColoane[p];
			startTime = System.nanoTime();
			start = 0;
			end = M / p;
			rest = M % p;
			for (int i = 0; i < thread2List.length; i++) {
				if (rest > 0) {
					end += 1;
					rest -= 1;
				}
				thread2List[i] = new ThreadColoane(matrix, conv, result3, N, M, n, m, (m - 1) / 2 + start, (m - 1) / 2 + end);
				thread2List[i].start();
				start = end;
				end = start + M / p;
			}
			for (ThreadColoane myThread : thread2List) {
				myThread.join();
			}
			stopTime = System.nanoTime();
			System.out.println("Pe coloane " + (stopTime - startTime));
			System.out.println(Arrays.deepEquals(result, result3));
			outputFile.write(N + " " + M + " " + n + " " + m + " coloane " + p + " " + "JAVA " + (stopTime - startTime) + "\n");

			int[][] result4 = new int[N][M];
			ThreadBlocuri[] thread3List = new ThreadBlocuri[p];
			startTime = System.nanoTime();
			int startI = 0, startJ = 0, endI = N / p, endJ = M / p, restI = N % p, restJ = M % p;
			for (int i = 0; i < thread3List.length; i++) {
				if (restI > 0) {
					endI += 1;
					restI -= 1;
				}
				if (restJ > 0) {
					endJ += 1;
					restJ -= 1;
				}
				thread3List[i] = new ThreadBlocuri(matrix, conv, result4, N, M, n, m, (n - 1) / 2 + startI, (n - 1) / 2 + endI - 1, (m - 1) / 2 + startJ, (m - 1) / 2 + endJ - 1);
				thread3List[i].start();
				startI = endI;
				startJ = endJ;
				endI = startI + N / p;
				endJ = startJ + M / p;
			}
			for (ThreadBlocuri myThread : thread3List) {
				myThread.join();
			}
			stopTime = System.nanoTime();
			System.out.println("Pe blocuri " + (stopTime - startTime));
			outputFile.write(N + " " + M + " " + n + " " + m + " blocuri " + p + " " + "JAVA " + (stopTime - startTime) + "\n");

			startTime = System.nanoTime();
			int[][] result5 = new int[N][M];
			ThreadDistributie[] thread4List = new ThreadDistributie[p];
			int blockSize = N * M / p + 1;
			for (int i = 0; i < thread4List.length; i++) {
				thread4List[i] = new ThreadDistributie(matrix, conv, result5, N, M, n, m);
			}
			for (int i = (n - 1) / 2; i <= (n - 1) / 2 + N - 1; i++) {
				for (int j = (m - 1) / 2; j <= (m - 1) / 2 + M - 1; j++) {
					var index_t = ((i - (n - 1) / 2) * M + (j - (m - 1) / 2)) / blockSize;
					thread4List[index_t].add(i, j);
				}
			}
			for (ThreadDistributie threadDistributie : thread4List) {
				threadDistributie.start();
			}
			for (ThreadDistributie threadDistributie : thread4List) {
				threadDistributie.join();
			}
			stopTime = System.nanoTime();
			System.out.println("Pe distributie liniara " + (stopTime - startTime));
			System.out.println(Arrays.deepEquals(result, result5));
			outputFile.write(N + " " + M + " " + n + " " + m + " distributie liniara " + p + " " + "JAVA " + (stopTime - startTime) + "\n");


			int[][] result6 = new int[N][M];
			ThreadDistributie[] thread5List = new ThreadDistributie[p];
			startTime = System.nanoTime();
			for (int i = 0; i < thread5List.length; i++) {
				thread5List[i] = new ThreadDistributie(matrix, conv, result6, N, M, n, m);
			}
			for (int i = (n - 1) / 2; i <= (n - 1) / 2 + N - 1; i++) {
				for (int j = (m - 1) / 2; j <= (m - 1) / 2 + M - 1; j++) {
					var index_t = (i * M + j) % p;
					thread5List[index_t].add(i, j);
				}
			}
			for (ThreadDistributie threadDistributie : thread5List) {
				threadDistributie.start();
			}
			for (ThreadDistributie threadDistributie : thread5List) {
				threadDistributie.join();
			}
			stopTime = System.nanoTime();
			System.out.println("Pe distributie ciclica " + (stopTime - startTime));
			System.out.println(Arrays.deepEquals(result, result6));
			outputFile.write(N + " " + M + " " + n + " " + m + " distributie ciclica " + p + " " + "JAVA " + (stopTime - startTime) + "\n");

			outputFile.close();
			scanner.close();
		} catch (InterruptedException | IOException e) {
			System.out.println("An error occurred.");
			System.out.println(Arrays.toString(e.getStackTrace()));
		}
	}
}