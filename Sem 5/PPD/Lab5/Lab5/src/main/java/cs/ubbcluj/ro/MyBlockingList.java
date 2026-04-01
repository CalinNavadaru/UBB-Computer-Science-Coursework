package cs.ubbcluj.ro;

import java.util.*;

public class MyBlockingList {

	private Node startNode;
	private final Node endNode;

	public Node getStartNode() {
		return startNode;
	}

	public void setStartNode(Node startNode) {
		this.startNode = startNode;
	}

	public Node getEndNode() {
		return endNode;
	}

	public MyBlockingList(Node startNode, Node endNode) {
		this.startNode = startNode;
		this.endNode = endNode;
	}

	public synchronized void removeElement(Integer id) {
		if (startNode == null) {
			return;
		}
		Node prev = null;
		var node = startNode;
		while (node != null && !Objects.equals(node.getPozitie().getId(), id)) {
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
		while (node != null && !Objects.equals(node.getPozitie().getId(), id)) {
			prev = node;
			node = node.getNext();
		}
		return new Pair<>(prev, node);
	}

	public synchronized void insertElement(Pozitie value, BlackList blackList) {
		if (blackList.containsElement(value.getId())) {
			return;
		}
		if (startNode == null) {
			startNode = new Node(value, null);
			return;
		}
		var existingPair = this.exists(value.getId());
		Node existingNode;
		if (existingPair.getValue() != null) {
			var prevNode = existingPair.getKey();
			var currentNode = existingPair.getValue();
			currentNode.getPozitie().setPunctaj(currentNode.getPozitie().getPunctaj() + value.getPunctaj());
			if (prevNode != null) {
				if (prevNode.getPozitie().getPunctaj() <= currentNode.getPozitie().getPunctaj()) {
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
		while (node != null && node.getPozitie().getPunctaj() > existingNode.getPozitie().getPunctaj()) {
			prev = node;
			node = node.getNext();
		}
		if (node == null) {
			assert prev != null;
			prev.setNext(existingNode);
		} else if (startNode.getPozitie().getPunctaj() <= existingNode.getPozitie().getPunctaj()) {
			existingNode.setNext(startNode);
			startNode = existingNode;
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
			map.put(n1.getPozitie().getId(), n1.getPozitie().getPunctaj());
			mapV.put(n1.getPozitie().getId(), false);
			n1 = n1.getNext();
		}
		var n2 = that.startNode;
		var l = 0;
		while (n2 != null) {
			if (map.get(n2.getPozitie().getId()) == null || mapV.get(n2.getPozitie().getId())) {
				System.out.println("Valoare pentru " + n2.getPozitie().getId() + " in map " + map.get(n2.getPozitie().getId()) + " si in mapV" + mapV.get(n2.getPozitie().getId()));
				return false;
			}
			mapV.put(n2.getPozitie().getId(), true);
			n2 = n2.getNext();
			l++;
		}
		return l == map.size();
	}

	@Override
	public int hashCode() {
		return Objects.hashCode(startNode);
	}

	public void removeElementv2(Integer id) {
		startNode.getLock().lock();
		startNode.getNext().getLock().lock();
		var prev = startNode;
		var node = startNode.getNext();
		while (node != endNode && node.getPozitie().getId() != id) {
			prev.getLock().unlock();
			prev = node;
			node.getNext().getLock().lock();
			node = node.getNext();
		}
		if (node == endNode) {
			prev.getLock().unlock();
			node.getLock().unlock();
			return;
		}
		node.getNext().getLock().lock();
		prev.setNext(node.getNext());
		prev.getLock().unlock();
		node.getLock().unlock();
		node.getNext().getLock().unlock();
	}

	public void insertElementv2(Pozitie pozitie, BlackList blackList) {
		startNode.getLock().lock();
		startNode.getNext().getLock().lock();
		var prev = startNode;
		var node = startNode.getNext();
		if (node == endNode) {
			if (blackList.containsElement(pozitie.getId())) {
				return;
			}
			prev.setNext(new Node(pozitie, endNode));
			prev.getLock().unlock();
			node.getLock().unlock();
			return;
		}
		while (node != endNode) {
			if (node.getPozitie().getId() == pozitie.getId()) {
				if (blackList.containsElement(pozitie.getId())) {
					prev.getLock().unlock();
					node.getLock().unlock();
					return;
				}
				node.getPozitie().setPunctaj(node.getPozitie().getPunctaj() + pozitie.getPunctaj());
				prev.getLock().unlock();
				node.getLock().unlock();
				return;
			}
			prev.getLock().unlock();
			prev = node;
			node.getNext().getLock().lock();
			node = node.getNext();
		}
		if (blackList.containsElement(pozitie.getId())) {
			prev.getLock().unlock();
			node.getLock().unlock();
			return;
		}
		prev.setNext(new Node(pozitie, endNode));
		prev.getLock().unlock();
		node.getLock().unlock();
	}

	public MyBlockingList sortDescending() {
		List<Pozitie> pozitieList = new ArrayList<>();
		Node currentNode = startNode;
		while (currentNode != null) {
			Pozitie currentPozitie = currentNode.getPozitie();
			Pozitie copiedPozitie = new Pozitie(currentPozitie.getId(), currentPozitie.getPunctaj(), currentPozitie.getTara());
			pozitieList.add(copiedPozitie);
			currentNode = currentNode.getNext();
		}
		pozitieList.sort((p1, p2) -> Integer.compare(p2.getPunctaj(), p1.getPunctaj()));
		MyBlockingList sortedList = new MyBlockingList(null, null);
		Node prevNode = null;
		for (Pozitie pozitie : pozitieList) {
			Node newNode = new Node(pozitie, null);
			if (sortedList.getStartNode() == null) {
				sortedList.setStartNode(newNode);
			} else {
				assert prevNode != null;
				prevNode.setNext(newNode);
			}
			prevNode = newNode;
		}
		return sortedList;
	}
}
