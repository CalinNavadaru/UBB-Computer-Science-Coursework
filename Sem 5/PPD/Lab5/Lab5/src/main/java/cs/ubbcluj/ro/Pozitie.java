package cs.ubbcluj.ro;

import java.util.Objects;

public class Pozitie {

	int id;
	int punctaj;
	int tara;

	public Pozitie(int id, int punctaj, int tara) {
		this.id = id;
		this.punctaj = punctaj;
		this.tara = tara;
	}

	public int getId() {
		return id;
	}

	public int getPunctaj() {
		return punctaj;
	}

	public int getTara() {
		return tara;
	}

	public void setPunctaj(int punctaj) {
		this.punctaj = punctaj;
	}

	@Override
	public boolean equals(Object o) {
		if (o == null || getClass() != o.getClass()) return false;
		Pozitie pozitie = (Pozitie) o;
		return getId() == pozitie.getId() && getTara() == pozitie.getTara();
	}

	@Override
	public String toString() {
		return "Pozitie{" +
				"id=" + id +
				", punctaj=" + punctaj +
				", tara=" + tara +
				'}';
	}

	@Override
	public int hashCode() {
		return Objects.hash(getId(), getTara());
	}
}
