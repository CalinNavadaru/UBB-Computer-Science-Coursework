package cs.ubbcluj.ro;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.Objects;
import java.util.Scanner;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Main {

	private static MyBlockingList seq(String[] files) throws FileNotFoundException {
		MyBlockingList resultList = new MyBlockingList(null,null);
		BlackList blackList = new BlackList();

		for (String filename: files) {
			File file = new File(filename);
			assert file.isFile();
			Scanner scanner = new Scanner(file);
			while (scanner.hasNext()) {
				Integer id = scanner.nextInt();
				int points = scanner.nextInt();
				int country = scanner.nextInt();

				if (points == -1 && !blackList.containsElement(id)) {
					blackList.addElement(id);
					resultList.removeElement(id);
				}
				else if (!blackList.containsElement(id)) {
					var pozitie = new Pozitie(id, points, country);
					resultList.insertElement(pozitie, blackList);
				}
			}
			scanner.close();
		}
		return resultList;
	}

	public static void main(String[] args){
		String path = "data1";
		String outputClasamentFilename = "OutputClasament.txt";
		var numberProcesses = Integer.parseInt(args[0]);
		var numberProducers = Integer.parseInt(args[1]);
		String pathOutput = args[2];
		var maxSize = Integer.parseInt(args[3]);

		try (
		FileWriter outputFile = new FileWriter(pathOutput, true);
		FileWriter outputClasamentFile = new FileWriter(outputClasamentFilename, false);
		ExecutorService executor = Executors.newFixedThreadPool(numberProducers)) {
			File directory = new File(path);
			assert directory.isDirectory();
			Path basePath = Paths.get(path);
			String[] files = Arrays.stream(Objects.requireNonNull(directory.list())).map(file -> basePath.resolve(file).toString()).toArray(String[]::new);
			long startTime = System.nanoTime();
			var result_seq = seq(files);
			long stopTime = System.nanoTime();
			System.out.println("Secvential " + (stopTime - startTime));
			outputFile.write("Secvential " + (stopTime - startTime) + "\n");
			writeResult(result_seq, outputClasamentFile);

			Consumator[] consumers = new Consumator[numberProcesses - numberProducers];
			MyBlockingQueue queue = new MyBlockingQueue(maxSize);
			var d = new Node(new Pozitie(-1, -1, -1), null);
			var s = new Node(new Pozitie(-1, -1, -1), d);
			MyBlockingList resultList = new MyBlockingList(s, d);
			BlackList blackList = new BlackList();
			int start = 0, end = files.length / numberProducers, rest = files.length % numberProducers;
			startTime = System.nanoTime();
			for (int i = 0; i < numberProducers; i++) {
				if (rest > 0) {
					end++;
					rest--;
				}
				int finalStart = start;
				int finalEnd = end;
				executor.execute(() -> {
					var p = new Producator(files, queue, finalStart, finalEnd);
					p.run();
				});
				start = end;
				end += files.length / numberProducers;
			}
			for (int i = 0; i < numberProcesses - numberProducers; i++) {
				consumers[i] = new Consumator(queue, resultList, blackList);
				consumers[i].start();
			}
			for(Consumator c: consumers) {
				c.join();
			}
			stopTime = System.nanoTime();
			resultList.setStartNode(resultList.getStartNode().getNext());
			Node prev = null;
			var t = resultList.getStartNode();
			while (t != resultList.getEndNode()) {
				prev = t;
				t = t.getNext();
			}
			assert prev != null;
			prev.setNext(null);
			var seq_sorted = result_seq.sortDescending();
			var parallel_sorted = resultList.sortDescending();
			var a = seq_sorted.equals(parallel_sorted);
			System.out.println("Comparatie " + a);
			assert a;
			writeResult(resultList, outputClasamentFile);
			System.out.println("P: " + numberProducers + " C: " + (numberProcesses - numberProducers) + " " + (stopTime - startTime));
			outputFile.write("P: " + numberProducers + " C: " + (numberProcesses - numberProducers) + " " + (stopTime - startTime) + " " + true + "\n");

		} catch (IOException e) {
			System.err.println(e.getMessage());
		} catch (InterruptedException e) {
			throw new RuntimeException(e);
		}
	}

	private static void writeResult(MyBlockingList result, FileWriter outputClasamentFile) throws IOException {
		var node = result.getStartNode();
		while(node != null) {
			outputClasamentFile.write(String.valueOf(node.getPozitie().getId()) + ' ' + node.getPozitie().getPunctaj()
					+ ' ' + node.getPozitie().getTara() + '\n');
			node = node.getNext();
		}
		outputClasamentFile.write("\n\n\n");
	}
}