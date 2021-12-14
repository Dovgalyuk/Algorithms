#include "list.h"

template <typename RebrData> class Graph {
public:


    template <typename stat, typename Da> struct info
    {
        stat status;
        Da length;
        info()
        {
            length = 0;
            status = 0;
        }
    };

    struct Rebro;

    struct Vershina 
    {
        List<Rebro*> neighbors;
        info<int, int> data;
        //Vershina(VersData data) : data(data),status(0), neighbors(List<Rebro*>()) {}
        Vershina()
        {
            neighbors = List<Rebro*>();
        }
    };

    struct Rebro 
    {
        Vershina* to;
        RebrData data;

        Rebro(Vershina* To, RebrData Data)
        {
            to = To;
            data = Data;
        }
    };

    typedef typename List<Vershina*>::Item VItem;

    typedef typename List<Rebro*>::Item RItem;

    Graph(size_t vershinaSum) : vershini(List<Vershina*>()), vershinaSum(vershinaSum) 
    {
        vershini.insert(new Vershina);
        num_Vershina++;
        for (int i = 1; i < vershinaSum; i++) 
        {
            vershini.insert_after(lastVershinaInList(), new Vershina);
            num_Vershina++;
        }
    }

    size_t getVershinaSum() 
    {
        return vershinaSum;
    }

    Vershina* setVershina() 
    {
        auto* vershina = new Vershina(num_Vershina);
        num_Vershina++;
        vershini.insert_after(lastVershinaInList(), vershina);
        vershinaSum++;
        return vershina;
    }

    Vershina* getVershina(size_t index) 
    {
        VItem* item = vershini.first();
        int i = 0;
        while (item && i != index) 
        {
            item = item->next();
            i++;
        }
        return item ? item->data() : nullptr;
    }

    void removeVershina(size_t index) 
    {
        VItem* item = vershini.first();
        int i = 0;
        while (item && i != index) 
        {
            item = item->next();
            i++;
        }
        if (item) 
        {
            removeRebraToVershina(item);
            RItem* reb_Item = (item->data())->neighbors.first();
            while (reb_Item) 
            {
                if (reb_Item->next())
                {
                    RItem* delet_reb_Item = reb_Item;
                    reb_Item = reb_Item->next();
                    delete delet_reb_Item->data();
                    (item->data())->neighbors.erase(delet_reb_Item);
                }
                else 
                {
                    delete reb_Item->data();
                    (item->data())->neighbors.erase(reb_Item);
                    reb_Item = nullptr;
                }
            }
            delete item->data();
            vershini.erase(item);
            vershinaSum--;
        }
    }

    Rebro* setRebro(Vershina* fromVershina, Vershina* toVershina, RebrData data) 
    {
        Rebro* rebro;
        RItem* item = findRebroItem(fromVershina, toVershina);
        if (item) {
            return nullptr;
        }
        else {
            rebro = new Rebro(toVershina, data);
            fromVershina->neighbors.insert(rebro);
        }
        return rebro;
    }

    Rebro* getRebro(Vershina* fromVershina, Vershina* toVershina) 
    {
        RItem* item = findRebroItem(fromVershina, toVershina);
        if (item->data())
        {
            return item->data();
        }
        else
        {
            return nullptr;
        }
    }

    void removeRebro(Vershina* fromVershina, Vershina* toVershina) 
    {
        RItem* item = findRebroItem(fromVershina, toVershina);
        if (item) {
            fromVershina->neighbors.erase(item);
        }
    }

    bool containsRebroBetweenVershina(Vershina* fromVershina, Vershina* toVershina) 
    {
        return findRebroItem(fromVershina, toVershina);
    }

    class RebroVershiniIterator 
    {
        RItem* firstNeighbor = NULL;
        RItem* neighbor = NULL;
    public:
        RebroVershiniIterator(Vershina* vershina) 
        {
            firstNeighbor = vershina->neighbors.first();
            neighbor = firstNeighbor;
        }

        Rebro* operator *()
        {
            return neighbor ? neighbor->data() : nullptr;
        }

        RebroVershiniIterator* operator ++(int i) 
        {
            if (neighbor->next() != firstNeighbor) 
            {
                neighbor = neighbor->next();
            }
            else
            {
                neighbor = nullptr;
            }
            return this;
        }
    };

    class VershinaIterator
    {
        VItem* currentVershina = NULL;
        int pos = 0;
    public:
        int sum = 0;

        VershinaIterator(Graph<RebrData>* graph)
        {
            sum = graph->vershinaSum;
            currentVershina = graph->vershini.first();
        }

        Vershina* operator *()
        {
            return currentVershina ? currentVershina->data() : nullptr;
        }

        VershinaIterator* operator ++(int i) 
        {
            if (pos < sum) 
            {
                currentVershina = currentVershina->next();
                pos++;
            }
            else 
            {
                currentVershina = nullptr;
            }
            return this;
        }
    };


    RebroVershiniIterator getRebroVershiniIterator(Vershina* vershina) 
    {
        return RebroVershiniIterator(vershina);
    }

    VershinaIterator getVershinaIterator() 
    {
        return VershinaIterator(this);
    }

    ~Graph()
    {
        VItem* versh_Item = vershini.first();
        while (versh_Item) {
            RItem* rebro_Item = (versh_Item->data())->neighbors.first();
            while (rebro_Item) {
                if (rebro_Item->next()) {
                    RItem* delet_Rebr_Item = rebro_Item;
                    rebro_Item = rebro_Item->next();
                    delete delet_Rebr_Item->data();
                    (versh_Item->data())->neighbors.erase(delet_Rebr_Item);
                }
                else {
                    delete rebro_Item->data();
                    (versh_Item->data())->neighbors.erase(rebro_Item);
                    rebro_Item = nullptr;
                }
            }
            if (versh_Item->next()) {
                VItem* deletingVershinaItem = versh_Item;
                versh_Item = versh_Item->next();
                delete deletingVershinaItem->data();
                vershini.erase(deletingVershinaItem);
            }
            else {
                delete versh_Item->data();
                vershini.erase(versh_Item);
                versh_Item = nullptr;
            }
        }
    }

    protected:
        List<Vershina*> vershini;
        size_t vershinaSum = 0;
        size_t num_Vershina = 0;

        VItem* lastVershinaInList() {
            VItem* item = vershini.first();
            while (item && item->next()) {
                item = item->next();
            }
            return item;
        }

        RItem* findRebroItem(Vershina * fromVershina, Vershina * toVershina)
        {
            RItem* item = fromVershina->neighbors.first();
            while (item) {
                if (item->data() && item->data()->to == toVershina)
                {
                    return item;
                }
                if (item->next())
                {
                    item = item->next();
                }
                else
                {
                    return nullptr;
                }
            }
            return nullptr;
        }

        void removeRebraToVershina(VItem * toVershina)
        {
            VItem* vershina = vershini.first();
            RItem* rebro;
            int i = 0;
            while (vershina && i++ < vershinaSum)
            {
                rebro = findRebroItem(vershina->data(), toVershina->data());
                if (rebro)
                {
                    removeRebro(vershina->data(), toVershina->data());
                }
                vershina = vershina->next();
            }
        }
    };