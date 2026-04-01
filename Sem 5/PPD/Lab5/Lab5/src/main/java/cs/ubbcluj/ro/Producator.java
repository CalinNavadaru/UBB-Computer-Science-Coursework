package cs.ubbcluj.ro;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Producator{

	protected String[] filenames;
	protected MyBlockingQueue queue;
	protected int start;
	protected int end;

	Producator(String[] filenames, MyBlockingQueue queue, int start, int end) {
		this.filenames = filenames;
		this.queue = queue;
		this.start = start;
		this.end = end;
	}

	public void run() {
		try {
			queue.addProducer();
		} catch (InterruptedException e) {
			throw new RuntimeException(e);
		}
		for (int i = start; i < end; i++) {
			File file = new File(this.filenames[i]);
			assert file.isFile();
			Scanner scanner;
			try {
				scanner = new Scanner(file);
			} catch (FileNotFoundException e) {
				throw new RuntimeException(e);
			}
			while (scanner.hasNext()) {
				int id = scanner.nextInt();
				int points = scanner.nextInt();
				int country = scanner.nextInt();
				try {
					queue.addElement(new Pozitie(id, points, country));
				} catch (InterruptedException e) {
					throw new RuntimeException(e);
				}
			}
			scanner.close();
		}
		try {
			queue.removeProducer();
		} catch (InterruptedException e) {
			throw new RuntimeException(e);
		}
	}
}
