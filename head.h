#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED
#include "patterns.h"
#include <cmath>

enum class ComponentType : int
{
    CPU = 4,
    GPU = 5,
    RAM = 1,
    Motherboard = 3,
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
        Guarantee = getRandomNumber(1, 10) * 12;
       year = getRandomNumber(2000, 2024);
    };
public:
    int GetGuarant() const {return Guarantee;}
    int GetYear() const {return year;}
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


// Итераторы

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

class VectorComponentContainerIterator : public Iterator<ComponentPtr>
{
private:
    const vector<ComponentPtr> *ComponentBox;
    vector<ComponentPtr>::const_iterator it;

public:
    VectorComponentContainerIterator(const vector<ComponentPtr> *componentBox)
    {
        ComponentBox = componentBox;
        it = ComponentBox->begin();
    }

    void First() { it = ComponentBox->begin(); }
    void Next() { it++; }
    bool IsDone()  const { it ==ComponentBox->end(); }
    ComponentPtr GetCurrent() const { return *it; }
};



//Контейнеры

class ComponentContainer
{
private:
    ComponentPtr *ComponentBox;
    int ComponentCount;
    int MaxSize;

public:
    ComponentContainer(int maxSize)
    {
        ComponentBox = new ComponentPtr[maxSize];
        for(int i = 0; i < maxSize; i++)
        {
            ComponentBox[i] = NULL;
        }
        ComponentCount = 0;
        MaxSize = maxSize;
    };
    virtual ~ComponentContainer()
    {
        for(int i = 0; i < MaxSize; i++)
        {
            if(ComponentBox[i] != NULL)
            {
                delete ComponentBox[i];
                ComponentBox[i] = NULL;
            }
        }
    delete [] ComponentBox;
    };
    void AddComponent(ComponentPtr newComponent)
    {
        ComponentBox[ComponentCount] = newComponent;
        ComponentCount++;
    };
    int GetCount() const { return ComponentCount; }
    ComponentPtr GetByIndex(int index) const { return ComponentBox[index]; }

    Iterator<ComponentPtr> *GetIterator()
    {
        return new ComponentContainerIterator(ComponentBox, ComponentCount);
    }
};




class VectorComponentContainer
{
private:
    vector<ComponentPtr> ComponentBox;

public:
    void AddComponent(ComponentPtr newComponent) { ComponentBox.push_back(newComponent); }
    int GetCount() const { return ComponentBox.size(); }

    Iterator<ComponentPtr> *GetIterator()
    {
        return new VectorComponentContainerIterator(&ComponentBox);
    }
};

//1 декоратор по типу

class ComponentTypeDecorator : public IteratorDecorator<ComponentPtr>
{
private:
    ComponentType TargetType;
public:
    ComponentTypeDecorator(Iterator<ComponentPtr> *it, ComponentType tatgetType):IteratorDecorator(it)
    {
        TargetType = TargetType;
    }
    void First()
    {
        It->First();
        while(!It->IsDone()&& It->GetCurrent()->GetType() != TargetType)
        {
            It->Next();
        }
    }

    void Next()
    {
        do
        {
            It->Next();
        } while(!It->IsDone() && It->GetCurrent()->GetType() != TargetType);
    }
};

//2 Декоратор по временному отрезку

class ComponentDataRangeDecorator : public IteratorDecorator<ComponentPtr>
{
private:
    int DataStart;
    int DataEnd;
public:
    ComponentDataRangeDecorator(Iterator<ComponentPtr> *it, int dataStart, int dataEnd)
    :IteratorDecorator(it)
    {
        DataStart = dataStart;
        DataEnd = dataEnd;
    }
    void First()
    {
        It->First();
        while(!It->IsDone()&& (It->GetCurrent()->GetYear() <= DataStart-1) || (It->GetCurrent()->GetYear() >= DataEnd+1))
        {
            It->Next();
        }
    }

    void Next()
    {
        do
        {
            It->Next();
        } while(!It->IsDone()&& (It->GetCurrent()->GetYear() <= DataStart-1) || (It->GetCurrent()->GetYear() >= DataEnd+1));
    }
};

//3 Декоратор по гарантии

class ComponentGuarantDecorator : public IteratorDecorator<ComponentPtr>
{
private:
    int Guarant;
public:
    ComponentGuarantDecorator(Iterator<ComponentPtr> *it, int guarant)
    :IteratorDecorator(it)
    {
        Guarant = guarant;

    }
    void First()
    {
        It->First();
        while(!It->IsDone()&& (It->GetCurrent()->GetGuarant() <= Guarant) )
        {
            It->Next();
        }
    }

    void Next()
    {
        do
        {
            It->Next();
        } while(!It->IsDone()&& (It->GetCurrent()->GetGuarant()) <= Guarant);
    }
};





#endif // HEAD_H_INCLUDED
