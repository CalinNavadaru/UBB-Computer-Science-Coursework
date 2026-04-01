package cs.ubbcluj.ro;

import java.util.HashMap;
import java.util.Map;
import java.util.Objects;

public class MyBlockingList {

	private Node startNode;

	public Node getStartNode() {
		return startNode;
	}

	public MyBlockingList(Node startNode) {
		this.startNode = startNode;
	}

	public synchronized void removeElement(Integer id) {
		if (startNode == null) {
			return;
		}
		Node prev = null;
		var node = startNode;
		while (node != null && !Objects.equals(node.getElement().getKey(), id)) {
			prev = node;
			node = node.getNext();
		}
		if (node == startNode) {
			startNode = startNode.getNext();
		} else if (node != null) {
			assert prev != null;
			prev.setNext(node.getNext());
		}
	}

	private synchronized Pair<Node, Node> exists(Integer id) {
		Node prev = null;
		var node = startNode;
		while (node != null && !Objects.equals(node.getElement().getKey(), id)) {
			prev = node;
			node = node.getNext();
		}
		return new Pair<>(prev, node);
	}
	public synchronized void insertElement(Pair<Integer, Integer> value, BlackList blackList) {
		if (blackList.containsElement(value.getKey())) {
			return;
		}
		if (startNode == null) {
			startNode = new Node(value, null);
			return;
		}
		var existingPair = this.exists(value.getKey());
		Node existingNode;
		if (existingPair.getValue() != null) {
			var prevNode = existingPair.getKey();
			var currentNode = existingPair.getValue();
			currentNode.getElement().setValue(currentNode.getElement().getValue() + value.getValue());
			if (prevNode != null) {
				if (prevNode.getElement().getValue() <= currentNode.getElement().getValue()) {
					var nextNode = currentNode.getNext();
					prevNode.setNext(nextNode);
				} else {
					return;
				}
			} else {
				return;
			}
			existingNode = currentNode;
		} else {
			existingNode = new Node(value, null);
		}
		Node prev = null;
		var node = startNode;
		if (existingNode.getElement().getValue() > startNode.getElement().getValue()) {
			existingNode.setNext(startNode);
			startNode = existingNode;
			return;
		}
		while (node != null && node.getElement().getValue() >= existingNode.getElement().getValue()) {
			prev = node;
			node = node.getNext();
		}
		if (node == null) {
			assert prev != null;
			prev.setNext(existingNode);
		} else {
			existingNode.setNext(node);
			assert prev != null;
			prev.setNext(existingNode);
		}
	}

	@Override
	public boolean equals(Object o) {
		if (o == null || getClass() != o.getClass()) return false;
		MyBlockingList that = (MyBlockingList) o;
		Map<Integer, Integer> map = new HashMap<>();
		Map<Integer, Boolean> mapV = new HashMap<>();
		var n1 = this.startNode;
		while (n1 != null) {
			map.put(n1.getElement().getKey(), n1.getElement().getValue());
			mapV.put(n1.getElement().getKey(), false);
			n1 = n1.getNext();
		}
		var n2 = that.startNode;
		var l = 0;
		while (n2 != null) {
			if (map.get(n2.getElement().getKey()) == null || mapV.get(n2.getElement().getKey())) {
				System.out.println("Valoare pentru " + n2.getElement().getKey() + " in map " + map.get(n2.getElement().getKey()) + " si in mapV" + mapV.get(n2.getElement().getKey()));
				return false;
			}
			mapV.put(n2.getElement().getKey(), true);
			n2 = n2.getNext();
			l++;
		}
		return l == map.size();
	}

	@Override
	public int hashCode() {
		return Objects.hashCode(startNode);
	}
}
