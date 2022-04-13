#ifndef AVL_HEAD_H_2022_03_24
#define AVL_HEAD_H_2022_03_24

#include "mm.h"

namespace templates
{

    template <class T, int(*Compare)(const T *pElement, const T* pElement2) >
    class CAVLTree
    {
    private:
        struct leaf
        {
            T* pData;
            leaf *pLeft;
            leaf *pRight;
            int balanceFactor;
        };

    public:
        class CException
        {
        public:
            CException()
            {
            }
        };

    public:
        CAVLTree()
        {
            m_pRoot = nullptr;
        }

        virtual ~CAVLTree()
        {
        }

        bool add(T* pElement)
        {
            leaf new_elem = leaf(pElement, nullptr, nullptr, 0);
            leaf* current_leaf = m_pRoot;
            leaf* prev_leaf = nullptr;
            bool is_left = false;
            while (current_leaf != nullptr) {
                prev_leaf = current_leaf;
                if (Compare(pElement, &current_leaf.pData)) {
                    current_leaf = current_leaf.pRight;
                    is_left = false;
                }
                else {
                    current_leaf = current_leaf.pLeft;
                    is_left = true;
                }
            }
            if (is_left) {
                prev_leaf.pLeft = *new_elem;
            }
            else {
                prev_leaf.pRight = *new_elem;
            }
        }

        bool update(T* pElement)
        {
        }
      
        T* find(const T& pElement)
        {
            leaf* current_leaf = m_pRoot;
            while (current_leaf.pData != pElement) {
                if (Compare(pElement, &current_leaf.pData)) {
                    current_leaf = current_leaf.pRight;
                }
                else {
                    current_leaf = current_leaf.pLeft;
                }
            }
        }

        bool remove(const T& element)
        {
        }

        void clear()
        {
        }

    private:
        leaf* m_pRoot;
        CMemoryManager<leaf> m_Memory;
    };

}; // namespace templates

#endif // #define AVL_HEAD_H_2015_03_31
