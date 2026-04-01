package cs.ubbcluj.ro;

import java.util.LinkedList;
import java.util.Queue;

public class MyBlockingQueue {
	private final Queue<Pozitie> queue;
	private int countProducers = 0;
	private final int maxSize;

	public MyBlockingQueue(int maxSize) {
		this.queue = new LinkedList<>();
		this.maxSize = maxSize;
	}

	public synchronized void addProducer() throws InterruptedException {
		countProducers++;
		notifyAll();
	}

	public synchronized void removeProducer() throws InterruptedException {
		countProducers--;

		if (countProducers == 0 && queue.isEmpty()) {
			notifyAll();
		}
	}

	public synchronized void addElement(Pozitie value) throws InterruptedException {
		while (queue.size() + 1 > maxSize) {
			wait();
		}
		queue.add(value);
		notify();
	}

	public synchronized Pozitie get() throws InterruptedException {
		while (queue.isEmpty() && countProducers > 0) {
			wait();
		}
		if (queue.isEmpty() && countProducers == 0) {
			notifyAll();
			return null;
		}
		var value = queue.poll();
		notifyAll();
		return value;
	}
}
