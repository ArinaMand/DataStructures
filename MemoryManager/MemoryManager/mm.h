#include <string>
#ifndef MEMORY_MANAGER_HEAD_H_2022_02_17
#define MEMORY_MANAGER_HEAD_H_2022_02_17

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
            block* pnext;
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
            }
        };

    public:
        CMemoryManager(int _default_block_size, bool isDeleteElementsOnDestruct = false)
        {
            m_blkSize = _default_block_size;
            m_isDeleteElementsOnDestruct = isDeleteElementsOnDestruct;
            m_pBlocks = nullptr;
            m_pCurrentBlk = nullptr;
        }

        virtual ~CMemoryManager()
        {
            /*block* cur_block = m_pBlocks;
            do {
                block* prev = cur_block;
                cur_block = cur_block.pnext;
                free(prev);
            } while (cur_block.pnext != nullptr);*/
            clear();
        }

        // �������� ����� ������ �������� �� ���������
        T* newObject()
        {
            if (m_pBlocks == nullptr) {
                m_pBlocks = newBlock();
                m_pCurrentBlk = m_pBlocks;
            }
            block* b = m_pCurrentBlk;
            if (b->usedCount == m_blkSize) {
                b = m_pBlocks;
                while (b != nullptr && b->usedCount == m_blkSize) {
                    b = b->pnext;
                }
                if (b == nullptr) {
                    block* new_block = newBlock();
                    //b->pnext = new_block;
                    b = new_block;
                }
                m_pCurrentBlk = b;
            }
            T* p = m_pCurrentBlk->pdata + m_pCurrentBlk->firstFreeIndex;
            int* pi = reinterpret_cast<int*>(p);
            m_pCurrentBlk->firstFreeIndex = *pi;
            memset(reinterpret_cast<void*>(p), 0, sizeof(T));
            ::new(reinterpret_cast<void*>(p)) T;
            m_pCurrentBlk->usedCount += 1;


            /*T* p = m_pCurrentBlk->pdata + m_pCurrentBlk->firstFreeIndex;
            memset(reinterpret_cast<void*>(p), 0, sizeof(T));
            ::new(reinterpret_cast<void*>(p)) T;
            m_pCurrentBlk->firstFreeIndex = reinterpret_cast<int*>(p);
            m_pCurrentBlk->usedCount += 1;*/
            return p;
        }

        // Освободить элемент в менеджере
        bool deleteObject(T* p)
        {
            block* current_block = m_pBlocks;
            while (current_block != nullptr) {
                int data_distance = p - current_block->pdata;
                if (data_distance >= 0 && data_distance < m_blkSize) {
                    p->~T();
                    memset(reinterpret_cast<void*>(p), 0, sizeof(T));
                    int* ptr = reinterpret_cast<int*>(p);
                    *ptr = current_block->firstFreeIndex;
                    current_block->firstFreeIndex = data_distance;
                    current_block->usedCount -= 1;
                    return true;
                }
                current_block = current_block->pnext;
            }
            return false;
        }

        // Очистка данных, зависит от m_isDeleteElementsOnDestruct
        void clear()
        {
            if (m_isDeleteElementsOnDestruct) {
                block* cur_block = m_pBlocks;
                while (cur_block != nullptr) {
                    block* next = cur_block->pnext;
                    deleteBlock(cur_block);
                    cur_block = next;
                };
            }
            m_pBlocks = nullptr;
            m_pCurrentBlk = nullptr;
        }
    private:

        // Создать новый блок данных. применяется в newObject
        block* newBlock()
        {
            block* new_block = new block();
            new_block->pdata = new T[m_blkSize];
            //newBlock->pnext = nullptr;
            new_block->firstFreeIndex = 0;
            new_block->usedCount = 0;
            for (int i = 0; i < m_blkSize - 1; ++i) {
                *reinterpret_cast<int*>(&new_block->pdata[i]) = i + 1;
            }
            *reinterpret_cast<int *>(&new_block->pdata[m_blkSize - 1]) = -1;
            return new_block;
        }

        // Освободить память блока данных. Применяется в clear
        void deleteBlock(block *p)
        {
            delete[] p->pdata;
            delete p;
        }

        // ������ �����
        int m_blkSize;
        // ������ ������ ������
        block* m_pBlocks;
        // ������� ����
        block *m_pCurrentBlk;
        // ������� �� �������� ��� ������������
        bool m_isDeleteElementsOnDestruct;
    };
}; // namespace lab618

#endif // #define MEMORY_MANAGER_HEAD_H_2022_02_17
