#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED
#include "patterns.h"
#include <cmath>

enum class ComponentType : int
{
    CPU = 3,
    GPU = 5,
    RAM = 1,
    Motherboard = 2,
    Disk = 2,
    Unknown = 0
};


int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return min + static_cast<int>((max - min + 1) * (rand() * fraction));
}

class Component
{
protected:
    int Guarantee;
    int year;
    ComponentType Type;
    Component()
    {
       year = getRandomNumber(2000, 2024);
    };
public:
    int GetGuarant() const {return Guarantee;}
    virtual ComponentType GetType() const = 0;
    virtual int GetPrice() = 0;
    virtual void GetCharacteristics() = 0;
};

typedef Component * ComponentPtr;

class CPU : public Component
{
protected:
    int Cores;
    int Threads;
    int Frequency;
public:
    CPU() : Component()
    {
        Type = ComponentType::CPU;
        Cores = getRandomNumber(2, 16);
        Threads = Cores * (getRandomNumber(1, 2));
    }
    ComponentType GetType() const {return Type;}
    int GetPrice () { return Cores * Threads  * 100 * (year - 2000);}
    void GetCharacteristics()
    {
        cout << "Cores: " << Cores << endl;
        cout << "Threads: " << Threads << endl;
        cout << "Frequency: " << Frequency << endl;
    }
};

class GPU : public Component
{
protected:
    int Gpu_memory;
    int Frequency;
public:
    GPU() : Component()
    {
        Type = ComponentType::GPU;
        Gpu_memory = getRandomNumber(2, 8);
        Frequency = getRandomNumber(1000, 2000);
    }
    ComponentType GetType() const {return Type;}
    int GetPrice () { return Gpu_memory * Frequency / 1000 * 100 * (year - 2000);}
    void GetCharacteristics()
    {
        cout << "GPU memory: " << Gpu_memory << endl;
        cout << "Frequency: " << Frequency << endl;
    }
};




class RAM : public Component
{
protected:
    int Memory;
    int Frequency;
public:
    RAM() : Component()
    {
        Type = ComponentType::RAM;
        Memory = getRandomNumber(2, 32);
        Frequency = getRandomNumber(1000, 4000);
    }
    ComponentType GetType() const {return Type;}
    int GetPrice () { return Memory * Frequency / 1000 * 100 * (year - 2000);}
    void GetCharacteristics()
    {
        cout << "GPU memory: " << Memory << endl;
        cout << "Frequency: " << Frequency << endl;
    }
};

class Motherboard : public Component
{
protected:
    int Slots_RAM;

public:
    Motherboard() : Component()
    {
        Type = ComponentType::Motherboard;
        Slots_RAM = getRandomNumber(1, 4) * 2;
    }
    ComponentType GetType() const {return Type;}
    int GetPrice () { return Slots_RAM / 1000 * 100 * (year - 2000);}
    void GetCharacteristics()
    {
        cout << "Slots RAM: " << Slots_RAM << endl;

    }
};

class Disk : public Component
{
protected:
    int Memory;
    int Speed;
public:
    Disk() : Component()
    {
        Type = ComponentType::Disk;
        Memory =  pow(2, getRandomNumber(0, 6)) * 128 ;
        Speed = getRandomNumber(1000, 4000);
    }
    ComponentType GetType() const {return Type;}
    int GetPrice () { return Memory * Speed / 1000 * 100 * (year - 2000);}
    void GetCharacteristics()
    {
        cout << "Memory: " << Memory << endl;
        cout << "Speed: " << Speed << endl;
    }
};


// Iterator

class ComponentContainerIterator : public Iterator<ComponentPtr>
{
private:
    const ComponentPtr *ComponentBox;
    int Pos;
    int Count;

public:
    ComponentContainerIterator(const ComponentPtr *componentBox, int c_count)
    {
        ComponentBox = componentBox;
        Count = c_count;
        Pos = 0;
    }

    void First() { Pos = 0; }
    void Next() { Pos++; }
    bool IsDone() const { return Pos >= Count; }
    ComponentPtr GetCurrent() const { return ComponentBox[Pos]; }
};

//Container

class ComponentContainer
{
private:
    ComponentPtr *ComponentBox; // указатель на указатель на фрукт
    int ComponentCount;
    int MaxSize;

public:
    ComponentContainer(int maxSize);
    virtual ~ComponentContainer();
    void AddComponent(ComponentPtr newComponent);
    int GetCount() const { return ComponentCount; }
    ComponentPtr GetByIndex(int index) const { return ComponentBox[index]; }

    Iterator<ComponentPtr> *GetIterator()
    {
        return new ComponentContainerIterator(ComponentBox, ComponentCount);
    }
};

/* class MegaComponentContainerIterator : public Iterator<ComponentPtr>
{
private:
    const list<ComponentPtr> *ComponentBox;
    list<ComponentPtr>::const_iterator it;

public:
    MegaComponentContainerIterator(const std::list<ComponentPtr> *componentBox)
    {        ComponentBox = componentBox;
        it = ComponentBox->begin();
    }

    void First() { it = ComponentBox->begin(); }
    void Next() { it++; }
    bool IsDone()  const { it !=ComponentBox->end(); }
    ComponentPtr GetCurrent() const { return *it; }
};

class MegaComponentContainer
{
private:
    vector<ComponentPtr> ComponentBox;
    list<ComponentPtr> ComponentBox;

public:
    void AddComponent(ComponentPtr newComponent) { ComponentBox.push_back(newComponent); }
    int GetCount() const { return ComponentBox.size(); }
    // FruitPtr GetByIndex(int index) const { return FruitBox[index]; }

    Iterator<ComponentPtr> *GetIterator()
    {
        return new MegaComponentContainerIterator(&componentBox);
    }
};


*/


#endif // HEAD_H_INCLUDED
