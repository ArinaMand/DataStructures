#ifndef TEMPLATES_LIST_2022_02_03
#define TEMPLATES_LIST_2022_02_03

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
                if (m_pBegin == nullptr) {
                    m_pBegin = p;
                }
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
                return m_pBegin != it.m_pBegin or m_pCurrent != it.m_pCurrent;
            }

            void operator++()
            {
                if (m_pCurrent != nullptr)
                {
                    m_pCurrent = m_pCurrent->pnext;
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
            }

            void setLeafPreBegin(leaf* p)
            {
                leaf* new_begin = &p;
                new_begin.pnext = *m_pBegin;
                m_pBegin = *new_begin;
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

        virtual ~CSingleLinkedList()
        {
        }

        void pushBack(T& data)
        {
            leaf l = leaf(data, nullptr);
            if (m_pEnd == nullptr) {
                m_pBegin = &l;
                m_pEnd = m_pBegin;
            }
            else {
                m_pEnd->pnext = &l;
                m_pEnd = m_pEnd->pnext;
            }
            m_pEnd = &l;
        }

        void pushFront(T& data)
        {
            leaf l = leaf(data, nullptr);
            if (m_pBegin != nullptr) {
                l.pnext = m_pBegin;
                m_pBegin = &l;
            }
            else {
                m_pBegin = &l;
                m_pEnd = m_pBegin;
            }
        }

        T popFront()
        {
            T tmp = m_pBegin->data;
            leaf* l = m_pBegin;
            m_pBegin = m_pBegin->pnext;
            delete(l);
            if (m_pBegin == nullptr) {
                m_pEnd = nullptr;
            }
            return tmp;
        }

        // изменяет состояние итератора. выставляет предыдущую позицию.
        void erase(CIterator& it)
        {
            leaf* l = m_pBegin;
            while (l.pnext != it) {
                l = l.pnext;
            };
            it.SetLeaf(l);
            ~(*it.pnext);
        }

        int getSize()
        {
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
            leaf* current_item = &m_pBegin;
            while (current_item.pnext != nullptr) {
                leaf* next_item = &current_item.pnext;
                delete(current_item);
                current_item = next_item;
            }
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
                this.data = data;
                this.pnext = _pnext;
                this.pprev = _pprev;
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
                m_pBegin = p;
                m_pEnd = p;
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
                if (m_pCurrent != m_pEnd) {
                    m_pCurrent = m_pCurrent->_pnext;
                }
                else {
                    _ASSERT("end of list");
                }
            }

            void operator--()
            {
                if (m_pCurrent != m_pBegin) {
                    m_pCurrent = m_pCurrent->_pprev;;
                }
                else {
                    _ASSERT("start of list");
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
            }

            // применяется в erase и eraseAndNext
            void setLeafPreBegin(leaf* p)
            {
                p->pnext = m_pBegin;
                m_pBegin = p;
            }

            // применяется в erase и eraseAndNext
            void setLeafPostEnd(leaf* p)
            {
                m_pEnd->pnext = p;
                p->pprev = m_pEnd;
                m_pEnd = p;
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
            T tmp = m_pEnd->data;
            if (m_pEnd == m_pBegin) {
                m_pBegin = nullptr;
            }
            leaf* ptr = m_pEnd;
            m_pEnd = m_pEnd->_pprev;
            delete(ptr);
            
            return tmp;
        }

        void pushFront(T& data)
        {
            leaf* l = new leaf(data, m_pBegin, nullptr);
            if (m_pBegin == nullptr) {
                m_pBegin = l;
                m_pEnd = l;
            }
            else {
                m_pBegin->_pprev = l;
            }
        }

        T popFront()
        {
            T tmp = m_pBegin->data;
            if (m_pEnd == m_pBegin) {
                m_pEnd = nullptr;
            }
            leaf* l = m_pBegin;
            m_pBegin = m_pBegin->pnext;
            if (m_pBegin != nullptr){
                m_pBegin->pprev = nullptr;
            }
            delete(l);
            return tmp;
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
                leaf* tmp = it_leaf->pprev;
                it.setLeaf(tmp);
                if (it_leaf == m_pEnd) {
                    tmp->pnext = nullptr;
                    m_pEnd = m_pEnd->pprev;
                }
                else {
                    tmp->pnext = it_leaf->pnext;
                    (it_leaf->pnext)->pprev = tmp;
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
                leaf* tmp = it_leaf->pnext;
                it.setLeaf(tmp);
                if (it_leaf == m_pBegin) {
                    tmp->pprev = nullptr;
                    m_pBegin = m_pBegin->pnext;
                }
                else {
                    tmp->pprev = it_leaf->pprev;
                    (it_leaf->pprev)->pnext = tmp;
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
            int count = 0;
            leaf* current = m_pBegin;
            while (current != nullptr) {
                current = &current.pnext;
                ++count;
            }
            return count;
        }

        void clear()
        {
            leaf* l = m_pBegin;
            while (l.pnext != nullptr) {
                l = l.pnext;
                delete(l.pprev);
            }
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
