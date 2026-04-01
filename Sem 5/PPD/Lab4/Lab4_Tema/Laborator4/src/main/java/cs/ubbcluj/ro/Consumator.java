package cs.ubbcluj.ro;

public class Consumator extends Thread {

	protected MyBlockingList resultList;
	protected MyBlockingQueue queue;
	protected BlackList blackList;

	Consumator(MyBlockingQueue queue, MyBlockingList resultList, BlackList blackList) {
		this.resultList = resultList;
		this.queue = queue;
		this.blackList = blackList;
	}

	public void run() {
		Pair<Integer, Integer> item;
		while (true) {
			try {
				item = queue.get();
			} catch (InterruptedException e) {
				Thread.currentThread().interrupt();
				throw new RuntimeException(e);
			}
			if (item == null) {
				return;
			}
			var id = item.getKey();
			var points = item.getValue();
			if (points == -1 && !blackList.containsElement(id)) {
				blackList.addElement(id);
				resultList.removeElement(id);
			}
			else if (!blackList.containsElement(id)) {
				Pair<Integer, Integer> pair = new Pair<>(id, points);
				resultList.insertElement(pair, blackList);
			}
		}
	}
}
