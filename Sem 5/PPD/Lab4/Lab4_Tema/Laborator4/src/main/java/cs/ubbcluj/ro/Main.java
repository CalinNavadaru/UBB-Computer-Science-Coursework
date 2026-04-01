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

public class Main {

	private static MyBlockingList seq(String[] files) throws FileNotFoundException {
		MyBlockingList resultList = new MyBlockingList(null);
		BlackList blackList = new BlackList();

		for (String filename: files) {
			File file = new File(filename);
			assert file.isFile();
			Scanner scanner = new Scanner(file);
			while (scanner.hasNext()) {
				Integer id = scanner.nextInt();
				int points = scanner.nextInt();

				if (points == -1 && !blackList.containsElement(id)) {
					blackList.addElement(id);
					resultList.removeElement(id);
				}
				else if (!blackList.containsElement(id)) {
					Pair<Integer, Integer> pair = new Pair<>(id, points);
					resultList.insertElement(pair, blackList);
				}
			}
			scanner.close();
		}
		return resultList;
	}

	public static void main(String[] args) throws InterruptedException, IOException {
		String path = "data";
		String outputClasamentFilename = "OutputClasament.txt";
		String pathOutput = args[2];
		FileWriter outputFile = new FileWriter(pathOutput, true);
		FileWriter outputClasamentFile = new FileWriter(outputClasamentFilename, false);
		File directory = new File(path);
		assert directory.isDirectory();
		Path basePath = Paths.get(path);
		
		String[] files = Arrays.stream(Objects.requireNonNull(directory.list()))  
				.map(file -> basePath.resolve(file).toString())  
				.toArray(String[]::new);
		long startTime = System.nanoTime();
		var result_seq = seq(files);
		long stopTime = System.nanoTime();
		System.out.println("Secvential " + (stopTime - startTime));
		outputFile.write("Secvential " + (stopTime - startTime) + "\n");

		MyBlockingList resultList = new MyBlockingList(null);
		BlackList blackList = new BlackList();
		MyBlockingQueue queue = new MyBlockingQueue();
		var numberProcesses = Integer.parseInt(args[0]);
		var numberProducers = Integer.parseInt(args[1]);
		Producator[] producers = new Producator[numberProducers];
		Consumator[] consumers = new Consumator[numberProcesses - numberProducers];
		int start = 0, end = files.length / numberProducers, rest = files.length % numberProducers;
		startTime = System.nanoTime();
		for (int i = 0; i < producers.length; i++) {
			if (rest > 0) {
				end++;
				rest--;
			}
			producers[i] = new Producator(files, queue, start, end);
			producers[i].start();
			start = end;
			end += files.length / numberProducers;
		}
		for (int i = 0; i < numberProcesses - numberProducers; i++) {
			consumers[i] = new Consumator(queue, resultList, blackList);
			consumers[i].start();
		}
		for (Producator p: producers) {
			p.join();
		}
		for(Consumator c: consumers) {
			c.join();
		}
		stopTime = System.nanoTime();

		var a = result_seq.equals(resultList);
		System.out.println(a);
		assert a;
		writeResult(result_seq, outputClasamentFile);
		writeResult(resultList, outputClasamentFile);
		System.out.println("P: " + numberProducers + " C: " + (numberProcesses - numberProducers) + " " + (stopTime - startTime));
		outputFile.write("P: " + numberProducers + " C: " + (numberProcesses - numberProducers) + " " + (stopTime - startTime) + "\n");
		outputFile.close();
		outputClasamentFile.close();

	}

	private static void writeResult(MyBlockingList result, FileWriter outputClasamentFile) throws IOException {
		var node = result.getStartNode();
		while(node != null) {
			outputClasamentFile.write(node.getElement().getKey().toString() + ' ' + node.getElement().getValue().toString() + '\n');
			node = node.getNext();
		}
		outputClasamentFile.write("\n\n\n");
	}
}