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
		Pozitie item;
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
			var id = item.getId();
			var points = item.getPunctaj();
			if (points == -1 && !blackList.containsElement(id)) {
				blackList.addElement(id);
				resultList.removeElementv2(id);
			} else if (!blackList.containsElement(id)) {
				resultList.insertElementv2(item, blackList);
			}
		}
	}
}
