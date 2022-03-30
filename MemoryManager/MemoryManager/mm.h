#include <string>
#ifndef MEMORY_MANAGER_HEAD_H_2022_02_17
#define MEMORY_MANAGER_HEAD_H_2022_02_17

template<class TYPE>
inline void _stdcall ConstructElements(TYPE* pElements)
{
    memset(reinterpret_cast<void*>(pElements), 0, sizeof(TYPE));
    ::new(reinterpret_cast<void*>(pElements)) TYPE;
}

template<class TYPE>
inline void _stdcall DestructElements(TYPE* pElements)
{
    pElements->~TYPE();
    memset(reinterpret_cast<void*>(pElements), 0, sizeof(TYPE));
}

namespace lab618
{
    template <class T>
    class CMemoryManager
    {
    private:
        struct block
        {
            // Массив данных блока
            T* pdata;
            // Адрес следующего блока
            block *pnext;
            // Первая свободная ячейка
            int firstFreeIndex;
            // Число заполненных ячеек
            int usedCount;
        };
    public:
        class CException
        {
        public:
            CException(std::string s)
            {
                return std::runtime_error(s);
            }
        };

    public:
        CMemoryManager(int _default_block_size, bool isDeleteElementsOnDestruct = false)
        {
            m_blkSize = _default_block_size;
            m_isDeleteElementsOnDestruct = isDeleteElementsOnDestruct;
        }

        virtual ~CMemoryManager()
        {
            block* cur_block = m_pBlocks;
            do {
                block* prev = cur_block;
                cur_block = cur_block.pnext;
                free(prev);
            } while (cur_block.pnext != nullptr);
        }

        // Получить адрес нового элемента из менеджера
        T* newObject()
        {
            block* b = newBlock();
            return b;
        }

        // Освободить элемент в менеджере
        bool deleteObject(T* p)
        {
            block* current_block = m_pBlocks;
            while (&current_block.pdata != &p) {
                if (current_block.pnext == nullptr) {
                    throw CException();
                    break;
                }
                current_block = current_block.pnext;
            };
            free(current_block.pdata);
        }

        // Очистка данных, зависит от m_isDeleteElementsOnDestruct
        void clear()
        {
            if (m_isDeleteElementsOnDestruct) {
                block* cur_block = m_pBlocks;
                do {
                    free(cur_block.data);
                    cur_block = cur_block.pnext;
                } while (cur_block.pnext != nullptr);
            }
        }
    private:

        // Создать новый блок данных. применяется в newObject
        block* newBlock()
        {
            return *ConstructElements(block);
        }

        // Освободить память блока данных. Применяется в clear
        void deleteBlock(block *p)
        {
            DestructElements(p);
        }

        // Размер блока
        int m_blkSize;
        // Начало списка блоков
        block* m_pBlocks;
        // Текущий блок
        block *m_pCurrentBlk;
        // Удалять ли элементы при освобождении
        bool m_isDeleteElementsOnDestruct;
    };
}; // namespace lab618

#endif // #define MEMORY_MANAGER_HEAD_H_2022_02_17
