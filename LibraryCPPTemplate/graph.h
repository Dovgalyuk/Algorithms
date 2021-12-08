#pragma once
#include "list.h"

template <typename VershinaData, typename RebroData> class DirectedGraph {
public:

    struct Rebro;

    struct Vershina {
        VershinaData data;
        VershinaData status;
        List<Rebro*> neighbors;
        Vershina(VershinaData data) : data(data), neighbors(List<Rebro*>()) {}
    };

    struct Rebro {
        Vershina* to;
        RebroData data;
        Rebro(Vershina* to, RebroData data) : to(to), data(data) {}
    };

    typedef typename List<Vershina*>::Item VershinaItem;
    typedef typename List<Rebro*>::Item RebroItem;

    DirectedGraph(size_t vershinaAmount) : vershini(List<Vershina*>()), vershinaAmount(vershinaAmount) {
        vershini.insert(new Vershina(0));
        numberOfVershina++;
        for (int i = 1; i < vershinaAmount; i++) {
            vershini.insert_after(lastVershinaInList(), new Vershina(i));
            numberOfVershina++;
        }
    }

    ~DirectedGraph() {
        for (int j = 0; j < vershinaAmount; j++) {
            for (int i = 0; i < vershinaAmount; i++) {
                if (containsRebroBetweenVershina(getVershina(j), getVershina(i))) {
                    removeRebro(getVershina(j), getVershina(i));
                }
            }
        }
        while (vershini.empty()) {
            VershinaItem* item = vershini.first();
            delete item->data();
            vershini.erase(item);
        }
    }

    size_t getVershinaAmount() {
        return vershinaAmount;
    }

    Vershina* setVershina() {
        auto* vershina = new Vershina(numberOfVershina);
        numberOfVershina++;
        vershini.insert_after(lastVershinaInList(), vershina);
        vershinaAmount++;
        return vershina;
    }

    Vershina* getVershina(size_t index) {
        VershinaItem* item = vershini.first();
        int i = 0;
        while (item && i != index) {
            item = item->next();
            i++;
        }
        return item ? item->data() : NULL;
    }

    void removeVershina(size_t index) {
        VershinaItem* item = vershini.first();
        int i = 0;
        while (item && i != index) {
            item = item->next();
            i++;
        }
        if (item) {
            removeRebraToVershina(item);
            vershini.erase(item);
            vershinaAmount--;
        }
    }

    Rebro* setRebro(Vershina* fromVershina, Vershina* toVershina, RebroData data) {
        Rebro* reb;
        RebroItem* item = findRebroItem(fromVershina, toVershina);
        if (item) {
            return NULL;
        }
        else {
            reb = new Rebro(toVershina, data);
            fromVershina->neighbors.insert(reb);
        }
        return reb;
    }

    Rebro* getRebro(Vershina* fromVershina, Vershina* toVershina) {
        RebroItem* item = findRebroItem(fromVershina, toVershina);
        return item ? item->data() : NULL;
    }

    void removeRebro(Vershina* fromVershina, Vershina* toVershina) {
        RebroItem* item = findRebroItem(fromVershina, toVershina);
        if (item) {
            fromVershina->neighbors.erase(item);
        }
    }

    bool containsRebroBetweenVershina(Vershina* fromVershina, Vershina* toVershina) {
        return findRebroItem(fromVershina, toVershina);
    }

    class RebroVershiniIterator {
        RebroItem* firstNeighbor = NULL;
        RebroItem* neighbor = NULL;
    public:
        RebroVershiniIterator(Vershina* vershina) {
            firstNeighbor = vershina->neighbors.first();
            neighbor = firstNeighbor;
        }

        Rebro* operator *() {
            return neighbor ? neighbor->data() : NULL;
        }

        RebroVershiniIterator* operator ++(int i) {
            if (neighbor->next() != firstNeighbor) {
                neighbor = neighbor->next();
            }
            else {
                neighbor = NULL;
            }
            return this;
        }
    };

    class VershinaIterator {
        VershinaItem* currentVershina = NULL;
        int pos = 0;
    public:
        int amount = 0;

        VershinaIterator(DirectedGraph<VershinaData, RebroData>* graph) {
            amount = graph->vershinaAmount;
            currentVershina = graph->vershini.first();
        }

        Vershina* operator *() {
            return currentVershina ? currentVershina->data() : NULL;
        }

        VershinaIterator* operator ++(int i) {
            if (pos < amount) {
                currentVershina = currentVershina->next();
                pos++;
            }
            else {
                currentVershina = NULL;
            }
            return this;
        }
    };


    RebroVershiniIterator getRebroVershiniIterator(Vershina* vershina) {
        return RebroVershiniIterator(vershina);
    }

    VershinaIterator getVershinaIterator() {
        return VershinaIterator(this);
    }

protected:
    List<Vershina*> vershini;
    size_t vershinaAmount = 0;
    size_t numberOfVershina = 0;

    VershinaItem* lastVershinaInList() {
        VershinaItem* item = vershini.first();
        while (item && item->next()) {
            item = item->next();
        }
        return item;
    }

    RebroItem* findRebroItem(Vershina* fromVershina, Vershina* toVershina) {
        RebroItem* item = fromVershina->neighbors.first();
        while (item) {
            if (item->data() && item->data()->to == toVershina) {
                return item;
            }
            if (item->next()) {
                item = item->next();
            }
            else {
                return NULL;
            }
        }
        return NULL;
    }

    void removeRebraToVershina(VershinaItem* toVershina) {
        VershinaItem* vershina = vershini.first();
        RebroItem* rebro;
        int i = 0;
        while (vershina && i++ < vershinaAmount) {
            rebro = findRebroItem(vershina->data(), toVershina->data());
            if (rebro) {
                removeRebro(vershina->data(), toVershina->data());
            }
            vershina = vershina->next();
        }
    }
};