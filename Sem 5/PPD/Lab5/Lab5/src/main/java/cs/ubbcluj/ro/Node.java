package cs.ubbcluj.ro;

import java.util.Objects;
import java.util.concurrent.locks.ReentrantLock;

public class Node {

	private final Pozitie pozitie;
	private Node next;
	private final ReentrantLock lock;

	public ReentrantLock getLock() {
		return lock;
	}


	public Node(Pozitie pozitie, Node next) {
		this.pozitie = pozitie;
		this.next = next;
		this.lock = new ReentrantLock();
	}

	public Pozitie getPozitie() {
		return pozitie;
	}

	public Node getNext() {
		return next;
	}

	public void setNext(Node next) {
		this.next = next;
	}

	@Override
	public boolean equals(Object o) {
		if (o == null || getClass() != o.getClass()) return false;
		Node node = (Node) o;
		return Objects.equals(getPozitie(), node.getPozitie());
	}

	@Override
	public int hashCode() {
		return Objects.hashCode(getPozitie());
	}
}
