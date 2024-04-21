#include <iostream>
#include <list>
#include <vector>


using namespace std;
#include "head.h"
#include "patterns.h"

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

Component *CreateComponent(ComponentType Type)
{
    switch(Type)
    {
        case ComponentType::CPU: return new CPU();
    }
}
void Task1(ComponentContainer *componentBox)
{
    for(int i = 0; i < componentBox->GetCount(); i++)
    {
       const ComponentPtr currentComponent = componentBox->GetByIndex(i);
        if(currentComponent->GetGuarant() >= 36)
        {
            wcout << i << L" (" << PrintComponentType(currentComponent->GetType()) << L")" << endl;
        }
    }

}

void Task_Spikes(Iterator<ComponentPtr> * Iterator)
{
	for(Iterator->First(); !Iterator->IsDone(); Iterator->Next())
	{
		const ComponentPtr CurrentComponent = Iterator->GetCurrent();
		wcout << PrintComponentType(CurrentComponent->GetType());
		wcout << CurrentComponent->GetYear() << endl;
        //CurrentComponent->GetCharacteristics();
	}
}

ComponentType getcomponent()
{
    ComponentType a[2]{ComponentType::CPU, ComponentType::GPU};
    return a[0];
}




int main()
{

    ComponentContainer cont(100);
    VectorComponentContainer v_cont;
    for(int i = 0; i < getRandomNumber(1, 10000); i++)
    {
        v_cont.AddComponent(CreateComponent(getcomponent()));
    }

    Iterator<ComponentPtr> *It = new ComponentGuarantDecorator(v_cont.GetIterator(), 12*9);
    Task_Spikes(It);




    return 0;
}
