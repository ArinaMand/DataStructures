#ifndef HASH_HEAD_H_2021_03_11
#define HASH_HEAD_H_2021_03_11

#include "MemoryManager/MemoryManager/mm.h" // необходимо использовать свой memorymanager

namespace lab618
{
    /**
    Шаблонный класс CHash.
    В качестве параметров шаблона применяется:
    тип - T;
    функция вычисления хеша - unsigned int HashFunc(const T* pElement);
    функция сравнения - int Compare(const T *pElement, const T* pElement2).

     Класс реализует алгоритм контейнера Хеш-таблица (ассоциативный массив). Данный алгоритм базируется на идее формирования линейной адресации
    произвольных элементов в зависимости от специально вычисляемого целого значения, уникального для каждого элемента (хеш).
     Формирование линейной адресации позволяет получать и сохранять элементы в контейнер за время не зависящее от числа элементов в контейнере — O(1).
     В идеальном случае каждому хешу соответствует ячейка в линейном массиве данных. На самом деле подобрать функцию вычисления хеша, таким образом,
    чтобы соблюдалась уникальность сложно, или получаются числа очень большой размерности. Для преодоления данной проблемы, в Хеш-таблице допускаются
    коллизии — одинаковые значения, уникальность элементов определяется их полями (функциями сравнения).
     Существует два способа разрешения коллизий — разреженная Хеш-таблица и Хеш-таблица со списками. Разреженные Хеш-таблицы при возникновении коллизии
    начинают искать первую свободную ячейку в самой таблице, поиск аналогично происходит от ячейки с номером равным значению хеша, пока не найдется нужный
    элемент. Хеш-таблица со списками, в каждой ячейке Хеш-таблицы хранит начало списка элементов с одинаковыми значениями хеша. Соответственно,
    вставка производится по алгоритму: вычисляем значение хеша для элемента, проверяем есть ли в списке с данным индексом (значение хеш функции)
    данный элемент с помощью функции сравнения, если нет до добавляем его в список. Поиск производится по алгоритму: вычисляем значение хеша для элемента,
    проверяем есть ли в списке с данным индексом искомый элемент с помощью функции сравнения.
     Размер Хеш-таблицы, как правило, меньше размерности функции вычисления хеша, поэтому вычисленное значение хеша ограничивают по размеру таблицы
    с помощью операции вычисления остатка от деления.
     Функция вычисления хеша и операция сравнения задаются как параметры шаблона, что позволяет построить разные Хеш-таблицы для одного набора элементов.
     Основные недостатки Хеш-таблиц:
      1. Сложность подбора хорошей хеш функции (функции дающей наименьшее число коллизий);
      2. Отсутствие упорядоченности элементов;
      3. Вычислительная сложность хеш функции может добавить большую константу в вычислительную сложность алгоритма.

    Данный класс реализует алгоритм Хеш-таблицы со списками
    Данный класс не хранит данные — хранит, только указатели на них.
    Хранение данных производится вне рамок данного класса!
    */
    template <class T, unsigned int(*HashFunc)(const T* pElement), int(*Compare)(const T *pElement, const T* pElement2) >
    class CHash
    {
    private:
        /**
        Лист списка элементов. Обратите внимание, что хранится указатель на данные.
        Данный класс не хранит данные — хранит, только указатели на них.
        Хранение данных производится вне рамок данного класса!
        */
        struct leaf
        {
            T* pData;
            leaf *pnext;
        };

    public:
        /**
        Исключение, которое применяется при нехватке памяти на работу алгоритма
        */
        class CMemoryException
        {
        public:
            CMemoryException()
            {
            }
        };

    public:
        /**
        Конструктор с параметрами: размер Хеш-таблицы, и размер блока памяти для менеджера памяти.
        Размер Хеш таблицы реализуем жестко — изменение размера таблицы в зависимости от числа элементов в контейнере не требуется.
        Все создаваемые листики списков разрешения коллизий храним в менеджере памяти.
        */
        CHash(int hashTableSize, int defaultBlockSize):m_Memory(defaultBlockSize, true)
        {
            m_tableSize = hashTableSize;
            m_pTable = new leaf*[hashTableSize];
            for (int i = 0; i < hashTableSize; ++i) {
                m_pTable[i] = nullptr;
            }
        }
        /**
        Деструктор. Должен освобождать всю выделенную память
        */
        virtual ~CHash()
        {
            clear();
            delete[] m_pTable;
        }

        /**
        Функция добавления элемента в Хеш-таблицу. Возвращает false, если элемент уже есть и true, если элемент добавлен.
        */
        bool add(T* pElement)
        {
            unsigned int i;
            leaf* try_find = findLeaf(pElement, i);
            if (try_find != nullptr) {
                return false;
            }

            leaf* new_leaf = m_Memory.newObject();
            if (!new_leaf) {
                throw CHash::CMemoryException();
            }
            new_leaf->pData = pElement;
            new_leaf->pnext = m_pTable[i];
            m_pTable[i] = new_leaf;
            return true;
        }
        /**
        Функция обновления элемента в Хеш-таблице. Обновляет, если элемент уже есть добавляет, если элемента еще нет.
        Возвращает false, если был добавлен новый элемент, true если элемент обновлен.
        */
        bool update(T* pElement)
        {
            unsigned int idx;
            leaf* l = findLeaf(pElement, idx);
            if (l != nullptr) {
                l->pData = pElement;
                return true;
            }
            leaf* new_leaf = m_Memory.newObject();
            new_leaf->pData = pElement;
            new_leaf->pnext = m_pTable[idx];
            m_pTable[idx] = new_leaf;
            return false;
        }

        /**
        Функция поиска элемента в Хеш-таблице. Возвращает указатель на данные. Если элемента не нашлось, то null.
        Обратите внимание, что для поиска используется частично заполненный объект, т.е. В нем должны быть заполнены поля на основе которых рассчитывается хеш.*/
        T* find(const T& element)
        {
            unsigned int idx;
            leaf* l = findLeaf(&element, idx);
            if (l == nullptr) {
                return nullptr;
            }
            return l->pData;
        }

        /**
        Функция удаления элемента из Хеш-таблицы. Возвращает false, если не нашлось элемента, true если элемент был удален.
        */
        bool remove(const T& element)
        {
            int i = HashFunc(&element) % m_tableSize;
            leaf* l = m_pTable[i];
            leaf* pred_l = nullptr;//findLeaf(element, idx);
            while (l != nullptr && Compare(l->pData, &element) != 0) {
                pred_l = l;
                l = l->pnext;
            }
            if (l == nullptr) {
                //не нашли
                return false;
            }
            if (pred_l != nullptr) {
                //перекинули цепочку связи
                pred_l->pnext = l->pnext;
            }
            else {
                //это первый
                m_pTable[i] = l->pnext;
            }
            m_Memory.deleteObject(l);
            return true;
        }

        /**
        Удаление всех элементов. Можно вызвать в деструкторе
        */
        void clear()
        {
            m_Memory.clear();
            for (int i = 0; i < m_tableSize; ++i) {
                m_pTable[i] = nullptr;
            }
        }
    private:
        /**

        Элементарная функция поиска узла в Хеш-таблицу. Возвращает найденный узел и в переменную idx выставляет актуальный индекс хеш-таблицы.
        Данную функцию следует использовать в функциях add, update, find.
        Алгоритм функции:
         1. вычисляем хеш функцию
         2. вычисляем индекс в Хеш-таблице (приводим вычисленное значение хеш функции к размеру массива)
         3. Перебираем список значений и если нашли, то возвращаем его.
         4. Если ничего не нашли, то возвращаем null
        */
        leaf *findLeaf(const T* pElement, unsigned int & idx)
        {
            idx = HashFunc(pElement) % m_tableSize;
            leaf* ptr = m_pTable[idx];
            while (ptr != nullptr) {
                if (Compare(ptr->pData, pElement) == 0) {
                    return ptr;
                }
                ptr = ptr->pnext;
            }
            return ptr;
        }

        /**
        Размер Хеш-таблицы
        */
        int m_tableSize;
        /**
        Хеш-таблица
        */
        leaf** m_pTable;
        /**
        Менеджер памяти, предназначен для хранение листов списков разрешения коллизий
        */
        CMemoryManager<leaf> m_Memory;
    };
}; // namespace templates

#endif // #define HASH_HEAD_H_2021_03_11
