#include <iostream>
#include <list>
#include <vector>


using namespace std;
#include "head.h"
#include "patterns.h"


//возвращает строку названия
wstring PrintComponentType(const ComponentType type)
{
    switch(type)
    {
        case ComponentType::CPU: return L"CPU";
        case ComponentType::GPU: return L"GPU";
        case ComponentType::RAM: return L"RAM";
        case ComponentType::Motherboard: return L"Motherboard";
        case ComponentType::Disk: return L"Disk";
        default: return L"unknow";
    }
}

// создание экзкемпляра класса по заданному типу
Component *CreateComponent(ComponentType Type)
{
    switch(Type)
    {
        case ComponentType::CPU: return new CPU();
        case ComponentType::GPU: return new GPU();
        case ComponentType::RAM: return new RAM();
        case ComponentType::Motherboard: return new Motherboard();
        case ComponentType::Disk: return new Disk();
    }
}

//вывод объектов  с гарантией больше n меяцев
void Task1(ComponentContainer *componentBox, int n)
{
    for(int i = 0; i < componentBox->GetCount(); i++)
    {
       const ComponentPtr currentComponent = componentBox->GetByIndex(i);
        if(currentComponent->GetGuarant() >= n)
        {
            wcout << i << L" (" << PrintComponentType(currentComponent->GetType()) << " guarantee: " << currentComponent->GetGuarant() << L" months)" << endl;
        }
    }

}


// Вывод тип и характкристки
void Task2(Iterator<ComponentPtr> * Iterator)
{
	for(Iterator->First(); !Iterator->IsDone(); Iterator->Next())
	{
		const ComponentPtr CurrentComponent = Iterator->GetCurrent();
		wcout << PrintComponentType(CurrentComponent->GetType()) << endl;
		CurrentComponent->GetCharacteristics();
		wcout << endl;
        //CurrentComponent->GetCharacteristics();
	}
}

// Вывод тип и цена
void Task3(Iterator<ComponentPtr> * Iterator)
{
	for(Iterator->First(); !Iterator->IsDone(); Iterator->Next())
	{
		const ComponentPtr CurrentComponent = Iterator->GetCurrent();
		wcout << PrintComponentType(CurrentComponent->GetType()) << " ";
		wcout << CurrentComponent->GetPrice() << endl;
        //CurrentComponent->GetCharacteristics();
	}
}

// функция возвращает случайный тип
ComponentType GetRandomComponentType()
{
    ComponentType a[5]{ComponentType::CPU, ComponentType::GPU,
        ComponentType::RAM, ComponentType::Motherboard, ComponentType::Disk};
    return *(a+getRandomNumber(0, 5));
}





int main()
{
    int a = getRandomNumber(0, 1000);
    int b = getRandomNumber(0, 1000);
    int c = getRandomNumber(0, 1000);


    ComponentContainer array_container(b);
    VectorComponentContainer vector_container;
    for(int i = 0; i < b; i++)
    {
        array_container.AddComponent(CreateComponent(GetRandomComponentType()));
    }
    for(int i = 0; i < c; i++)
    {
        vector_container.AddComponent(CreateComponent(GetRandomComponentType()));
    }

    Iterator<ComponentPtr> *clean_iterator = array_container.GetIterator();
    Iterator<ComponentPtr> *It = new ComponentDataRangeDecorator(array_container.GetIterator(), 2007, 2022);

    //Task1(&array_container, 56);
    Task2(clean_iterator);
    Task3(clean_iterator);
    delete clean_iterator;
    delete It;


    cout << "fgfg" << endl;

    return 0;
}
