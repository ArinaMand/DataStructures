#ifndef TEMPLATES_LIST_2022_02_03
#define TEMPLATES_LIST_2022_02_03

#include <cassert>

namespace lab618
{
    template<class T>
    class CSingleLinkedList
    {
    private:
        struct leaf
        {
            T data;
            leaf * pnext;
            leaf(T& _data, leaf * _pnext)
            {
                data = _data;
                pnext = _pnext;
            }
        };
    public:
        class CIterator
        {
        public:
            CIterator()
                : m_pCurrent(nullptr), m_pBegin(nullptr)
            {}

            CIterator(leaf *p)
            {
                m_pCurrent = p;
                m_pBegin = nullptr;
            }

            CIterator(const CIterator &src)
            {
                m_pBegin = src.m_pBegin;
                m_pCurrent = src.m_pCurrent;
            }

            ~CIterator()
            {
            }

            CIterator& operator = (const CIterator&  src)
            {
                m_pBegin = src.m_pBegin;
                m_pCurrent = src.m_pCurrent;
                return *this;
            }

            bool operator != (const CIterator&  it) const
            {
                return m_pBegin != it.m_pBegin || m_pCurrent != it.m_pCurrent;
            }

            void operator++()
            {
                if (m_pBegin == nullptr)
                {
                    if (m_pCurrent != nullptr) {
                        m_pCurrent = m_pCurrent->pnext;
                    }
                }
                else
                {
                    m_pCurrent = m_pBegin;
                    m_pBegin = nullptr;
                }
            }

            T& getData()
            {
                return m_pCurrent->data;
            }

            T& operator* ()
            {
                return m_pCurrent->data;
            }

            leaf* getLeaf()
            {
                return m_pCurrent;
            }

            void setLeaf(leaf* p)
            {
                m_pCurrent = p;
                m_pBegin = nullptr;
            }

            void setLeafPreBegin(leaf* p)
            {
                /*leaf* new_begin = p;
                new_begin->pnext = m_pBegin;
                m_pBegin = new_begin;*/
                m_pBegin = p;
                m_pCurrent = nullptr;
            }

            bool isValid() {
                return m_pCurrent != nullptr || m_pBegin != nullptr;
            }

        private:
            //храним голову списка, если мы находимся перед началом
            leaf* m_pBegin;
            // храним текущее положение
            leaf* m_pCurrent;
        };

    public:

        CSingleLinkedList()
        {
            m_pBegin = nullptr;
            m_pEnd = nullptr;
        }

        virtual ~CSingleLinkedList(){
        }

        void pushBack(T& data)
        {
            leaf* l = new leaf(data, nullptr);
            if (m_pBegin == nullptr) {
                m_pBegin = l;
                m_pEnd = l;
            }
            else {
                m_pEnd->pnext = l;
                m_pEnd = l;
            }
        }

        void pushFront(T& data)
        {
            leaf* l = new leaf(data, nullptr);
            if (m_pBegin != nullptr) {
                leaf* t = m_pBegin;
                l->pnext = t;
                m_pBegin = l;
            }
            else {
                m_pBegin = l;
                m_pEnd = l;
            }
        }

        T popFront()
        {
            T t = m_pBegin->data;
            if (m_pBegin == nullptr) {
                m_pEnd = nullptr;
            }
            leaf* l = m_pBegin;
            m_pBegin = m_pBegin->pnext;
            delete(l);
            return t;
        }

        // изменяет состояние итератора. выставляет предыдущую позицию.
        void erase(CIterator& it)
        {
            leaf* l = it.getLeaf();
            if (l == m_pBegin) {
                it.setLeafPreBegin(l->pnext);
                m_pBegin = m_pBegin->pnext;
            }
            else {
                leaf* t = m_pBegin;
                while (t->pnext != l) {
                    t = t->pnext;
                }
                t->pnext = l->pnext;
                it.setLeaf(t);
                if (l == m_pEnd) {
                    m_pEnd = t;
                }
            }
            delete(l);
            if (!m_pBegin) {
                m_pEnd = nullptr;
            }
        }

        int getSize()
        {
            if (m_pBegin == nullptr) {
                return 0;
            }
            leaf* l = m_pBegin;
            int count = 1;
            while (l != m_pEnd) {
                l = l->pnext;
                ++count;
            };
            return count;
        }

        void clear()
        {
            if (m_pBegin == nullptr) {
                return;
            }
            leaf* current_item = m_pBegin;
            while (current_item.pnext != nullptr) {
                leaf* next_item = current_item->pnext;
                delete(current_item);
                current_item = next_item;
            }
            delete(current_item);
            m_pBegin = nullptr;
            m_pEnd = nullptr;
        }

        CIterator begin()
        {
            return CIterator(m_pBegin);
        }

    private:
        leaf* m_pBegin, *m_pEnd;
    };

    template<class T>
    class CDualLinkedList
    {
    private:
        struct leaf
        {
            T data;
            leaf * pnext, *pprev;
            leaf(T& _data, leaf * _pprev, leaf * _pnext)
            {
                data = _data;
                pnext = _pnext;
                pprev = _pprev;
            }
        };
    public:
        class CIterator
        {
        public:
            CIterator()
            {
                m_pBegin = nullptr;
                m_pEnd = nullptr;
                m_pCurrent = nullptr;
            }

            CIterator(leaf *p)
            {
                m_pBegin = nullptr;
                m_pEnd = nullptr;
                m_pCurrent = p;
            }

            CIterator(const CIterator &src)
            {
                m_pBegin = src.m_pBegin;
                m_pEnd = src.m_pEnd;
                m_pCurrent = src.m_pCurrent;
            }

            ~CIterator()
            {
            }

            CIterator& operator = (const CIterator&  src)
            {
                m_pBegin = src.m_pBegin;
                m_pCurrent = src.m_pCurrent;
                m_pEnd = src.m_pEnd;
                return *this;
            }

            bool operator != (const CIterator&  it) const
            {
                if (m_pBegin != it.m_pBegin) {
                    return false;
                };
                if (m_pCurrent != it.m_pCurrent) {
                    return false;
                };
                if (m_pEnd != it.m_pEnd) {
                    return false;
                }
                return true;
            }

            void operator++()
            {
                if (!m_pBegin) {
                    if (m_pCurrent != nullptr) {
                        m_pCurrent = m_pCurrent->pnext;
                    }
                }
                else {
                    m_pCurrent = m_pBegin;
                    m_pBegin = nullptr;
                }
            }

            void operator--()
            {
                if (!m_pEnd) {
                    if (m_pCurrent != nullptr) {
                        m_pCurrent = m_pCurrent->pprev;
                    }
                }
                else {
                    m_pCurrent = m_pEnd;
                    m_pEnd = nullptr;
                }
            }

            T& getData()
            {
                return m_pCurrent->data;
            }

            T& operator* ()
            {
                return m_pCurrent->data;
            }

            leaf* getLeaf()
            {
                return m_pCurrent;
            }

            // применяется в erase и eraseAndNext
            void setLeaf(leaf* p)
            {
                m_pCurrent = p;
                m_pBegin = nullptr;
            }

            // применяется в erase и eraseAndNext
            void setLeafPreBegin(leaf* p)
            {
                m_pBegin = p;
                m_pCurrent = nullptr;
                m_pEnd = nullptr;
            }

            // применяется в erase и eraseAndNext
            void setLeafPostEnd(leaf* p)
            {
                m_pEnd = p;
                m_pCurrent = nullptr;
                m_pBegin = nullptr;
            }

            bool isValid() {
                return m_pCurrent != nullptr || m_pBegin != nullptr || m_pEnd != nullptr;
            }

        private:
            //храним голову списка, если мы находимся перед началом
            leaf* m_pBegin;
            // храним текущее положение
            leaf* m_pCurrent;
            //храним конец списка, если мы находимся после конца
            leaf* m_pEnd;
        };

    public:

        CDualLinkedList()
        {
            m_pBegin = nullptr;
            m_pEnd = nullptr;
        };

        virtual ~CDualLinkedList()
        {
        };

        void pushBack(T& data)
        {
            leaf* l = new leaf(data, m_pEnd, nullptr);
            if (m_pEnd != nullptr) {
                m_pEnd->pnext = l;
            }
            else {
                m_pBegin = l;
            }
            m_pEnd = l;
        }

        T popBack()
        {
            T data = m_pEnd->data;
            if (m_pEnd == m_pBegin) {
                m_pBegin = nullptr;
            }
            leaf* ptr = m_pEnd;
            m_pEnd = m_pEnd->pprev;
            delete(ptr);
            if (m_pEnd == nullptr) {
                m_pEnd->pnext = nullptr;
            }
            return data;
        }

        void pushFront(T& data)
        {
            leaf* l = new leaf(data, m_pBegin, nullptr);
            if (m_pBegin == nullptr) {
                m_pBegin = l;
                m_pEnd = l;
            }
            else {
                m_pBegin->pprev = l;
                m_pBegin = l;
            }
        }

        T popFront()
        {
            T data = m_pBegin->data;
            if (m_pEnd == m_pBegin) {
                m_pEnd = nullptr;
            }
            leaf* l = m_pBegin;
            m_pBegin = m_pBegin->pnext;
            if (m_pBegin != nullptr){
                m_pBegin->pprev = nullptr;
            }
            delete(l);
            return data;
        }

        // изменяет состояние итератора. выставляет предыдущую позицию.
        void erase(CIterator& it)
        {
            leaf* it_leaf = it.getLeaf();
            if (it_leaf == m_pBegin) {
                it.setLeafPreBegin(it_leaf->pnext);
                m_pBegin = m_pBegin->pnext;
            }
            else {
                leaf* ptr = it_leaf->pprev;
                it.setLeaf(ptr);
                if (it_leaf == m_pEnd) {
                    ptr->pnext = nullptr;
                    m_pEnd = m_pEnd->pprev;
                }
                else {
                    ptr->pnext = it_leaf->pnext;
                    (it_leaf->pnext)->pprev = ptr;
                }
            }
            delete it_leaf;
            if (!m_pBegin || !m_pEnd) {
                m_pBegin = nullptr;
                m_pEnd = nullptr;
            }
        }

        // изменяет состояние итератора. выставляет следующую позицию.
        void eraseAndNext(CIterator& it)
        {
            leaf* it_leaf = it.getLeaf();
            if (it_leaf == m_pEnd) {
                it.setLeafPostEnd(it_leaf->pprev);
                m_pEnd = m_pEnd->pprev;
            }
            else {
                leaf* ptr = it_leaf->pnext;
                it.setLeaf(ptr);
                if (it_leaf == m_pBegin) {
                    ptr->pprev = nullptr;
                    m_pBegin = m_pBegin->pnext;
                }
                else {
                    ptr->pprev = it_leaf->pprev;
                    (it_leaf->pprev)->pnext = ptr;
                }
            }
            delete it_leaf;
            if (!m_pBegin || !m_pEnd) {
                m_pBegin = nullptr;
                m_pEnd = nullptr;
            }
        }

        int getSize()
        {
            if (m_pBegin == nullptr) {
                return 0;
            }
            int count = 1;
            leaf* current = m_pBegin;
            while (current != m_pEnd) {
                current = current->pnext;
                ++count;
            }
            return count;
        }

        void clear()
        {
            if (!m_pBegin) {
                return;
            }
            leaf* l = m_pBegin;
            while (l != m_pEnd) {
                leaf* ptr = l->pnext;
                delete l;
                l = ptr;
            }
            delete l;
            m_pBegin = nullptr;
            m_pEnd = nullptr;
        }

        CIterator begin()
        {
            return CIterator(m_pBegin);
        }

        CIterator end()
        {
            return CIterator(m_pEnd);
        }

    private:
        leaf* m_pBegin, *m_pEnd;
    };
};
#endif //#ifndef TEMPLATES_LIST_2022_02_03
