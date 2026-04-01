package cs.ubbcluj.ro;

import java.util.HashSet;
import java.util.Set;

public class BlackList {

	private final Set<Integer> blacklist;

	public BlackList() {
		this.blacklist = new HashSet<>();
	}
	public synchronized void addElement(Integer value) {
		blacklist.add(value);
	}

	public synchronized boolean containsElement(Integer value) {
		return blacklist.contains(value);
	}
}
