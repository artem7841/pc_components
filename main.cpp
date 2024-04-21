#include <iostream>
#include <list>
#include <vector>


using namespace std;
#include "head.h"
#include "patterns.h"


//���������� ������ ��������
string PrintComponentType(const ComponentType type)
{
    switch(type)
    {
        case ComponentType::CPU: return "CPU";
        case ComponentType::GPU: return "GPU";
        case ComponentType::RAM: return "RAM";
        case ComponentType::Motherboard: return "Motherboard";
        case ComponentType::Disk: return "Disk";
        default: return "unknow";
    }
}

// �������� ����������� ������ �� ��������� ����
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

//����� ��������  � ��������� ������ n ������
void Task1(ComponentContainer *componentBox, int n)
{
    for(int i = 0; i < componentBox->GetCount(); i++)
    {
       const ComponentPtr currentComponent = componentBox->GetByIndex(i);
        if(currentComponent->GetGuarant() >= n)
        {
            cout << i << " (" << PrintComponentType(currentComponent->GetType()) << " guarantee: " << currentComponent->GetGuarant() << " months)" << endl;
        }
    }

}


// ����� ��� � �������������
void Task2(Iterator<ComponentPtr> * Iterator)
{
	for(Iterator->First(); !Iterator->IsDone(); Iterator->Next())
	{
		const ComponentPtr CurrentComponent = Iterator->GetCurrent();
		cout << PrintComponentType(CurrentComponent->GetType()) << endl;
		CurrentComponent->GetCharacteristics();
		cout << endl;
        //CurrentComponent->GetCharacteristics();
	}
}

// ����� ��� � ����
void Task3(Iterator<ComponentPtr> * Iterator)
{
	for(Iterator->First(); !Iterator->IsDone(); Iterator->Next())
	{
		const ComponentPtr CurrentComponent = Iterator->GetCurrent();
		cout << PrintComponentType(CurrentComponent->GetType()) << " ";
		cout << CurrentComponent->GetPrice() << " rub"<< endl;
        //CurrentComponent->GetCharacteristics();
	}
}

// ������� ���������� ��������� ���
ComponentType GetRandomComponentType()
{
    ComponentType a[5]{ComponentType::CPU, ComponentType::GPU,
        ComponentType::RAM, ComponentType::Motherboard, ComponentType::Disk};
    return *(a+getRandomNumber(0, 5));
}




int main()
{
    // ��������� �����
    int a = getRandomNumber(0, 1000);
    int b = getRandomNumber(0, 1000);
    int c = getRandomNumber(0, 1000);

    // ������������� � ���������� ��������� ������� ���������� ������
    ComponentContainer array_container(b);
    for(int i = 0; i < b; i++)
    {
        array_container.AddComponent(CreateComponent(GetRandomComponentType()));
    }

    // ������������� � ���������� ��������� ������� ���������� �������
    VectorComponentContainer vector_container;
    for(int i = 0; i < b; i++)
    {
        vector_container.AddComponent(CreateComponent(GetRandomComponentType()));
    }


    Iterator<ComponentPtr> *It_guarant = new ComponentGuarantDecorator(array_container.GetIterator(), 45);
    Iterator<ComponentPtr> *It_data = new ComponentDataRangeDecorator(array_container.GetIterator(), 2015, 2018);

    Task1(&array_container, 56);
    Task2(It_guarant);
    Task3(It_data);

    delete It_guarant;
    delete It_data;


    return 0;
}
