package cs.ubbcluj.ro;

import java.util.Objects;

public class Node {

	private final Pair<Integer, Integer> element;
	private Node next;

	public Node(Pair<Integer, Integer> element, Node next) {
		this.element = element;
		this.next = next;
	}

	public Pair<Integer, Integer> getElement() {
		return element;
	}

	public Node getNext() {
		return next;
	}

	public void setNext(Node next) {
		this.next = next;
	}

	public Node copy() {
		return new Node(this.element, this.next);
	}

	@Override
	public boolean equals(Object o) {
		if (o == null || getClass() != o.getClass()) return false;
		Node node = (Node) o;
		return Objects.equals(getElement(), node.getElement());
	}

	@Override
	public int hashCode() {
		return Objects.hashCode(getElement());
	}
}
