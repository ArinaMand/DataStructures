#include <string>
#ifndef MEMORY_MANAGER_HEAD_H_2022_02_17
#define MEMORY_MANAGER_HEAD_H_2022_02_17
#include <iostream>

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
                while (b->pnext!=nullptr && b->usedCount == m_blkSize) {
                    b = b->pnext;
                }
                if (b->usedCount == m_blkSize) {
                    block* new_block = newBlock();
                    b->pnext = new_block;
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
                    int* pp = (reinterpret_cast<int*>(p));
                    *pp = current_block->firstFreeIndex;
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
            if (!m_pBlocks) {
                return;
            }
            block* cur_block = m_pBlocks;

            if (m_isDeleteElementsOnDestruct) {
                while (cur_block != nullptr) {
                    block* next = cur_block->pnext;
                    delete(cur_block);
                    cur_block = next;
                };
            }
            else {
                while (cur_block != nullptr)
                {
                    if (cur_block->usedCount > 0)
                    {
                        throw CException("object not empty, must clear by yourself");
                    }
                    block* blk = cur_block->pnext;
                    deleteBlock(cur_block);
                    cur_block = blk;
                }
            }
            m_pBlocks = nullptr;
            m_pCurrentBlk = nullptr;
        }
    private:

        // Создать новый блок данных. применяется в newObject
        block* newBlock()
        {
            block* new_block = new block();
            char* ppp = new char[m_blkSize * sizeof(T)];
            new_block->pdata = reinterpret_cast<T*>(ppp);
            new_block->firstFreeIndex = 0;
            new_block->usedCount = 0;
            T* xxx = new_block->pdata;
            for (int i = 0; i < m_blkSize - 1; ++i) {
                int* aaa = reinterpret_cast<int*>(xxx + i);
                *aaa = i + 1;
            }
            int* aaa = reinterpret_cast<int*>(xxx + m_blkSize - 1);
            *aaa = -1;
            return new_block;
        }

        // Освободить память блока данных. Применяется в clear
        void deleteBlock(block *p)
        {
            /*не стыкуется с newBlock*/
            char* pd = reinterpret_cast<char*>(p->pdata);
            delete[] pd;
            //delete[] p->pdata;
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
