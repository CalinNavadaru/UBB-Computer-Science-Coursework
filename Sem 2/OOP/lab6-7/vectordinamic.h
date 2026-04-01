//
// Created by calin on 19.04.2023.
//

#pragma once

template<typename Element>
class IteratorVector;

template<typename Element>
class VectorDinamic {

private:
    Element* data;
    int lungime = 0;
    int capacitate = 0;

    [[noreturn]] void resize() noexcept;

public:

    VectorDinamic();

    ~VectorDinamic();

    VectorDinamic(const VectorDinamic& ot);

    VectorDinamic& operator=(const VectorDinamic& ot);

    VectorDinamic(VectorDinamic&& ot) noexcept ;

    VectorDinamic& operator=(VectorDinamic&& ot) noexcept;

    void add(const Element& e);

    Element& deleteLastElement();

    int size() const noexcept;

    const Element& get(int poz) const;

    void set(int poz, const Element& ot);

    friend class IteratorVector<Element>;

    IteratorVector<Element> begin() const;
    IteratorVector<Element> end() const;
};

template<typename Element>
Element& VectorDinamic<Element>::deleteLastElement() {
    Element e = this->data[lungime - 1];
    this->lungime--;
    return e;
}


template<typename Element>
class IteratorVector {
private:
    int poz = 0;
    const VectorDinamic<Element>& vector;
public:
    explicit IteratorVector(const VectorDinamic<Element>& v) noexcept;

    IteratorVector(const VectorDinamic<Element>& v, int poz) noexcept;


    bool valid() const noexcept;

    Element& element() const noexcept;

    void next() noexcept;

    Element& operator*();

    IteratorVector& operator++();

    bool operator==(const IteratorVector& ot) noexcept;

    bool operator!=(const IteratorVector& ot) noexcept;
};

template<typename Element>
VectorDinamic<Element>::VectorDinamic(): lungime{0}, capacitate{1}, data{new Element[1]}{

}

template<typename Element>
VectorDinamic<Element>::~VectorDinamic() {
    delete[] data;
}

template<typename Element>
VectorDinamic<Element>::VectorDinamic(const VectorDinamic &ot) {

    data = new Element[ot.capacitate];

    for (int i = 0; i < ot.lungime; i++) {
        data[i] = ot.data[i];
    }
    lungime = ot.lungime;
    capacitate = ot.capacitate;
}

template<typename Element>
void VectorDinamic<Element>::add(const Element &e){

    if (lungime == capacitate)
        this->resize();

    data[lungime++] = e;
}

template<typename Element>
[[noreturn]] void VectorDinamic<Element>::resize() noexcept {

    int newCapacity = 2 * capacitate;
    if (lungime == capacitate / 2) {
        newCapacity = capacitate / 2;
    }
    auto newData = new Element[2 * newCapacity];
    for (int i = 0; i < lungime; i++)
        newData[i] = data[i];

    delete[] data;
    data = newData;
    capacitate = static_cast<int>(2 * newCapacity);
}

template<typename Element>
int VectorDinamic<Element>::size() const noexcept {
    return lungime;
}

template<typename Element>
const Element &VectorDinamic<Element>::get(int poz) const {
    return data[poz];
}

template<typename Element>
void VectorDinamic<Element>::set(int poz, const Element &ot) {
    data[poz] = ot;
}

template<typename Element>
VectorDinamic<Element>& VectorDinamic<Element>::operator=(const VectorDinamic<Element> &ot) {
    if (this == &ot) {
        return *this;
    }

    delete[] data;
    data = new Element[ot.capacitate];
    for (int i = 0; i < ot.lungime; i++) {
        data[i] = ot.data[i];
    }
    lungime = ot.lungime;
    capacitate = ot.capacitate;
    return *this;
}

template<typename Element>
VectorDinamic<Element>::VectorDinamic(VectorDinamic &&ot)  noexcept {
    data = ot.data;
    lungime = ot.lungime;
    capacitate = ot.capacitate;

    ot.data = nullptr;
    ot.lungime = 0;
    ot.capacitate = 0;
}

template<typename Element>
VectorDinamic<Element>& VectorDinamic<Element>::operator=(VectorDinamic<Element> &&ot) noexcept {
    if (this == &ot)
        return *this;

    delete []data;
    data = ot.data;
    lungime = ot.lungime;
    capacitate = ot.capacitate;

    ot.data = nullptr;
    ot.lungime = 0;
    ot.capacitate = 0;
    return *this;
}

template<typename Element>
IteratorVector<Element>::IteratorVector(const VectorDinamic<Element> &v) noexcept : vector{v}{
}

template<typename Element>
IteratorVector<Element>::IteratorVector(const VectorDinamic<Element> &v, int poz) noexcept: vector{v}, poz{poz} {

}

template<typename Element>
bool IteratorVector<Element>::valid() const noexcept {
    return poz < vector.lungime;
}

template<typename Element>
void IteratorVector<Element>::next() noexcept {
    poz++;
}

template<typename Element>
Element& IteratorVector<Element>::element() const noexcept {
    return vector.data[poz];
}

template<typename Element>
Element& IteratorVector<Element>::operator*() {
    return element();
}

template<typename Element>
IteratorVector<Element>& IteratorVector<Element>::operator++() {
    next();
    return *this;
}

template<typename Element>
bool IteratorVector<Element>::operator==(const IteratorVector<Element>& ot) noexcept {
    return poz == ot.poz;
}

template<typename Element>
bool IteratorVector<Element>::operator!=(const IteratorVector<Element>& ot) noexcept {
    return !(*this == ot);
}

template<typename Element>
IteratorVector<Element> VectorDinamic<Element>::begin() const{
    return IteratorVector<Element>(*this);
}

template<typename Element>
IteratorVector<Element> VectorDinamic<Element>::end() const {
    return IteratorVector<Element>(*this, lungime);
}