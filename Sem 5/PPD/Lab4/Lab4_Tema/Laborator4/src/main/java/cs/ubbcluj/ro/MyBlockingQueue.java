package cs.ubbcluj.ro;

import java.util.LinkedList;
import java.util.Queue;

public class MyBlockingQueue {
	private final Queue<Pair<Integer, Integer>> queue;
	private int countProducers = 0;

	public MyBlockingQueue() {
		this.queue = new LinkedList<>();
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

	public synchronized void addElement(Pair<Integer, Integer> value) throws InterruptedException {
		queue.add(value);
		notify();
	}

	public synchronized Pair<Integer, Integer> get() throws InterruptedException {
		while (queue.isEmpty() && countProducers > 0) {
			wait();
		}
		if (queue.isEmpty() && countProducers == 0) {
			notifyAll();
			return null;
		}
		return queue.poll();
	}
}
