#include <iostream>
using namespace std;


//базовый абстрактный класс
class Room
{
protected:
    int Number; //номер комнаты 
    int Count; //количество мест в комнате 
    double Price; //цена
    int CountOccupied; //количество занятых мест

public:
    //конструктор по умолчанию
    Room()
    {
        Number = 0;
        Count = 1;
        Price = 0;
        CountOccupied = 0;
    }


//конструктор с параметрами 
    Room(int m_Number, int m_Count, double m_Price, int m_CountOccupied)
    {
        Number = m_Number;
        if (m_Count > 0)
            Count = m_Count;
        else
            Count = 1;

        if (m_Price >= 0)
            Price = m_Price;
        else
            Price = 0;

        if (m_CountOccupied >= 0 && m_CountOccupied <= Count)
            CountOccupied = m_CountOccupied;
        else
            CountOccupied = 0;
    }


    //виртуальный деструктор
    virtual ~Room()
    {
        cout << "Комната " << Number << " удалена" << endl;
    }


    //вирутальный метод вывода информации 
    virtual void printInfo()
    {
        cout << "Номер комнаты: " << Number << endl;
        cout << "Количество мест: " << Count << endl;
        cout << "Занято мест: " << CountOccupied << endl;
        cout << "Свободно мест: " << Count - CountOccupied << endl;
        cout << "Цена за ночь: " << Price << endl;
    }


    //виртуальные методы подсчета стоимости и описания
    virtual void calcNightCost(int guests, int nights) = 0;
    virtual void getRoomDescription() = 0;
};


//класс общего номера 
class DormRoom : public Room
{
private:
    int twoLevelBeds; //количество двухъярусных кроватей
    bool Lockers; //количество шкафчиков

//конструктор с параметрами
public:
    DormRoom(int m_Number, int m_Count, double m_Price, int m_CountOccupied,
        int m_twoLevelBeds, bool m_Lockers)
        : Room(m_Number, m_Count, m_Price, m_CountOccupied)
    {
        twoLevelBeds = m_twoLevelBeds;
        Lockers = m_Lockers;
    }
    
    //метод расчета стоимости общей комнаты
    void calcNightCost(int guests, int nights)
    {
        if (guests <= 0 || nights <= 0)
        {
            cout << "Некорректные данные" << endl;
            cout << "----------------" << endl;
            return;
        }

        if (guests > Count - CountOccupied)
        {
            cout << "Недостаточно свободных мест" << endl;
            cout << "----------------" << endl;
            return;
        }

        cout << "Количество гостей: " << guests << endl;
        cout << "Количество ночей: " << nights << endl;

        double result = Price * guests * nights;

        if (guests > 3)
        {
            double discount = 0.8;
            result = result * discount;
            cout << "Скидка для группы: 20%" << endl;
        }

        cout << "Стоимость: " << result << endl;
        cout << "----------------" << endl;
    }

    //метод описания общей комнаты
    void getRoomDescription()
    {
        cout << "Общий номер с двухъярусными кроватями" << endl;
    }

    //вывод информации
    void printInfo()
    {
        Room::printInfo();
        cout << "Двухъярусных кроватей: " << twoLevelBeds << endl;
        cout << "Шкафчики: " << Lockers << endl;
    }
};

//класс приватной комнаты 
class PrivateRoom : public Room
{
private:
    bool Bathroom;
    bool TV;

public:
    //конструктор с параметрами
    PrivateRoom(int m_Number, int m_Count, double m_Price, int m_CountOccupied,
        bool m_Bathroom, bool m_TV): Room(m_Number, m_Count, m_Price, m_CountOccupied)
    {
        Bathroom = m_Bathroom;
        TV = m_TV;
    }


    //метод расчета стоимости для приватной комнаты
    void calcNightCost(int guests, int nights)
    {
        if (guests <= 0 || nights <= 0)
        {
            cout << "Некорректные данные" << endl;
            cout << "----------------" << endl;
            return;
        }

        cout << "Количество гостей: " << guests << endl;
        cout << "Количество ночей: " << nights << endl;

        double result = Price * guests * nights;

        if (Bathroom)
            result = result + 300;

        if (TV)
            result = result + 600;

        cout << "Стоимость: " << result << endl;
        cout << "----------------" << endl;
    }


    //метод описания приватной комнаты
    void getRoomDescription()
    {
        cout << "Приватная комната" << endl;
    }

    void printInfo()
    {
        Room::printInfo();
        cout << "Санузел: " << Bathroom << endl;
        cout << "Телевизор: " << TV << endl;
    }
};

int main()
{
    setlocale(LC_ALL, "RU");

    Room*rooms[4]; //массив указаителей на базовый класс

//создание объектов 
    rooms[0] = new DormRoom(540, 6, 1000, 2, 3, true);
    rooms[1] = new DormRoom(685, 8, 900, 2, 4, false);
    rooms[2] = new PrivateRoom(578, 2, 3500, 0, true, false);
    rooms[3] = new PrivateRoom(497, 4, 3000, 1, true, true);


    //полиморфизм
    for (int i = 0; i < 4; i++)
    {
        rooms[i]->getRoomDescription();
        rooms[i]->printInfo();
        rooms[i]->calcNightCost(4, 3);
    }

    return 0;
}