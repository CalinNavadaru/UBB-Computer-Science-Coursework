package cs.ubbcluj.ro;


import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Arrays;
import java.util.Scanner;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;

class ThreadLinii extends Thread {
	int[][] conv;
	int[][] matrix;
	int[] before, after;
	int N, M, n, m, startI, endI;
	CyclicBarrier barrier;

	ThreadLinii(int[][] conv, int[][] matrix, int N, int M, int n, int m, int startI, int endI, CyclicBarrier barrier) {
		this.startI = startI;
		this.endI = endI;
		this.conv = conv;
		this.N = N;
		this.n = n;
		this.M = M;
		this.m = m;
		this.matrix = matrix;
		this.barrier = barrier;
	}

	public void run() {
		if (startI > N) {
			try {
				barrier.await();
			} catch (InterruptedException | BrokenBarrierException e) {
				throw new RuntimeException(e);
			}
			return;
		}
		before = matrix[startI - 1];
		after = matrix[endI];
		try {
			barrier.await();
		} catch (InterruptedException | BrokenBarrierException e) {
			throw new RuntimeException(e);
		}
		int[] line = matrix[startI];
		int[] buffer_before;
		int[] buffer_after;
		int[] b1, b2;
		if (endI == startI + 1) {
			buffer_before = Main.operation(before, matrix[startI], after, conv);
			matrix[startI] = buffer_before;
			return;
		} else {
			buffer_before = Main.operation(before, matrix[startI], matrix[startI + 1], conv);
			buffer_after = Main.operation(matrix[endI - 2], matrix[endI - 1], after, conv);
		}
		int i;
		b1 = buffer_before;
		for (i = startI + 1; i < endI - 1; i++) {
			before = line;
			line = matrix[i];
			b2 = Main.operation(before, line, matrix[i + 1], conv);
			matrix[i - 1] = b1;
			b1 = b2;

		}
		matrix[endI - 2] = b1;
		matrix[startI] = buffer_before;
		matrix[endI - 1] = buffer_after;
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

	public static int[] operation(int[] before, int[] line, int[] after, int[][] conv) {
		int[] aux = new int[M + (m - 1)];
		aux[(m - 1) / 2 - 1] = line[(m - 1) / 2 - 1];
		aux[M + (m - 1) / 2] = line[M + (m - 1) / 2];
		for (int j = (m - 1) / 2; j <= M + (m - 1) / 2 - 1; j++) {
			aux[j] = 0;
			for (int q = 0; q < 3; q++) {
				aux[j] += before[j + q - 1] * conv[0][q] + line[j + q - 1] * conv[1][q] + after[j + q - 1] * conv[2][q];
			}
		}
		return aux;
	}

	public static void seq(int[][] matrix, int[][] conv) {
		int[] buffer = operation(matrix[(n - 1) / 2 - 1], matrix[(n - 1) / 2], matrix[(n - 1) / 2 + 1], conv);
		int[] buffer2;
		int i;
		for (i = (n - 1) / 2 + 1; i <= N + (n - 1) / 2 - 1; i++) {
			buffer2 = operation(matrix[i - 1], matrix[i], matrix[i + 1], conv);
			matrix[i - 1] = buffer;
			buffer = buffer2;
		}
		matrix[i - 1] = buffer;
	}

	public static void main(String[] args) throws IOException {
		System.out.println(Arrays.toString(args));
		String pathInput = args[0];
		String pathOutput = args[1];
		FileWriter outputFile = new FileWriter(pathOutput, true);
		try {

			File myFile = new File(pathInput);
			Scanner scanner = new Scanner(myFile);

			N = scanner.nextInt();
			M = scanner.nextInt();
			n = scanner.nextInt();
			m = scanner.nextInt();
			p = Integer.parseInt(args[2]);

			CyclicBarrier barrier = new CyclicBarrier(p);
			int[][] matrix = new int[N + (n - 1)][M + (m - 1)];
			int[][] conv = new int[n][m];
			int[][] result_seq;


			initMatrix(matrix, (n - 1) / 2, (n - 1) / 2 + N - 1, (m - 1) / 2, (m - 1) / 2 + M - 1, scanner);
			initMatrix(conv, 0, n - 1, 0, m - 1, scanner);
			border(matrix);

			long startTime = System.nanoTime();
			seq(matrix, conv);
			long stopTime = System.nanoTime();
			System.out.println("Secvential " + (stopTime - startTime) + "\n");
			outputFile.write(N + " " + M + " " + "Java Secvential " + (stopTime - startTime) + "\n");
			result_seq = matrix;

			scanner.close();
			scanner = new Scanner(myFile);

			N = scanner.nextInt();
			M = scanner.nextInt();
			n = scanner.nextInt();
			m = scanner.nextInt();
			p = Integer.parseInt(args[2]);

			matrix = new int[N + (n - 1)][M + (m - 1)];
			conv = new int[n][m];

			initMatrix(matrix, (n - 1) / 2, (n - 1) / 2 + N - 1, (m - 1) / 2, (m - 1) / 2 + M - 1, scanner);
			initMatrix(conv, 0, n - 1, 0, m - 1, scanner);
			border(matrix);

			startTime = System.nanoTime();
			int start = 0, end = N / p, rest = N % p;
			ThreadLinii[] threadList = new ThreadLinii[p];
			for (int i = 0; i < threadList.length; i++) {
				if (rest > 0) {
					end += 1;
					rest -= 1;
				}
				threadList[i] = new ThreadLinii(conv, matrix, N, M, n, m, start + (n - 1) / 2, end + (n - 1) / 2, barrier);
				threadList[i].start();
				start = end;
				end = end + N / p;
			}
			for (ThreadLinii threadLinii : threadList) {
				threadLinii.join();
			}
			stopTime = System.nanoTime();
			System.out.println("Thread-uri " + (stopTime - startTime));
			System.out.println(Arrays.deepEquals(result_seq, matrix));
			outputFile.write(N + " " + M + " " + "Java cu " + p + " " + (stopTime - startTime) + "\n");
			outputFile.close();
			scanner.close();
		} catch (IOException e) {
			System.out.println("An error occurred.");
			System.out.println(Arrays.toString(e.getStackTrace()));

		} catch (InterruptedException e) {
			throw new RuntimeException(e);
		}
	}
}