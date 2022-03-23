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
                self.data = data;
                self.pnext = _pnext;
            }
        };
    public:
        class CIterator
        {
        public:
            CIterator()
                : m_pCurrent(0), m_pBegin(0)
            {}

            CIterator(leaf *p)
            {
                m_pBegin = p;
                m_pCurrent = p;
            }

            CIterator(const CIterator &src)
            {
                m_pBegin = scr.m_pBegin;
                m_pCurrent = scr.m_pCurrent;
            }

            ~CIterator()
            {
            }

            CIterator& operator = (const CIterator&  src)
            {
                m_pBegin = scr.m_pBegin;
                m_pCurrent = scr.m_pCurrent;
            }

            bool operator != (const CIterator&  it) const
            {
                return m_pBegin != it.m_pBegin or m_pCurrent != it.m_pCurrent;
            }

            void operator++()
            {
                m_pCurrent = m_pCurrent.pnext;
            }

            T& getData()
            {
                return T();
            }

            T& operator* ()
            {
                T tmp;
                return tmp;
            }

            leaf* getLeaf()
            {
                return *m_pCurrent;
            }

            void setLeaf(leaf* p)
            {
                self.m_pCurrent.pnext = p;
                self.m_pCurrent = &p;
            }

            void setLeafPreBegin(leaf* p)
            {
                new_begin = &p;
                new_begin.pnext = *self.m_pBegin;
                self.m_pBegin = *new_begin;
            }

            bool isValid() {
                return false;
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
        }

        virtual ~CSingleLinkedList()
        {
        }

        void pushBack(T& data)
        {
            l = leaf(data, self.m_pBegin);
            self.m_pBegin = *l;
        }

        void pushFront(T& data)
        {
            l = leaf(data);
            &self.m_pEnd.pname = *l;
            self.m_pEnd = *l;
        }

        T popFront()
        {
            T tmp;
            return tmp;
        }

        // изменяет состояние итератора. выставляет предыдущую позицию.
        void erase(CIterator& it)
        {
            l = m_pBegin;
            while (l.pnext != it) {
                l = l.pnext;
            };
            it.SetLeaf(l);
            ~(*it.pnext);
        }

        int getSize()
        {
            l = m_pBegin;
            count = 1;
            while (l != m_pEnd) {
                l = l.pnext;
                ++count;
            };
            return count;
        }

        void clear()
        {
            current_item = &self.m_pBegin;
            while (current_item.pnext != None) {
                next_item = &current_item.pnext;
                delete(current_item);
                current_item = next_item;
            }
        }

        CIterator begin()
        {

            return CIterator();
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
                self.data = data;
                self.pnext = _pnext;
                self.pprev = _pprev;
            }
        };
    public:
        class CIterator
        {
        public:
            CIterator()
            {
            }

            CIterator(leaf *p)
            {
            }

            CIterator(const CIterator &src)
            {
                self.m_pCurrent = scr;
            }

            ~CIterator()
            {
            }

            CIterator& operator = (const CIterator&  src)
            {
                m_pBegin = scr.m_pBegin;
                m_pCurrent = scr.m_pCurrent;
                m_pEnd = scr.m_pEnd;
            }

            bool operator != (const CIterator&  it) const
            {
                if (self.m_pBegin != it.m_pBegin) {
                    return false;
                };
                if (self.m_pCurrent != it.m_pCurrent) {
                    return false;
                };
                if (self.m_pEnd != it.m_pEnd) {
                    return false;
                }
                return true;
            }

            void operator++()
            {
                if (self.m_pCurrent != self.m_pEnd) {
                    self.m_pCurrent = item.pnext;
                }
                else {
                    assert("end of list");
                }
            }

            void operator--()
            {
                if (self.m_pCurrent != self.m_pBegin) {
                    self.m_pCurrent = item.pprev;
                }
                else {
                    assert("start of list");
                }
            }

            T& getData()
            {
                T tmp;
                return tmp;
            }

            T& operator* ()
            {
                T tmp;
                return tmp;
            }

            leaf* getLeaf()
            {
                return 0;
            }

            // применяется в erase и eraseAndNext
            void setLeaf(leaf* p)
            {
                /*p.pprev = m_pCurrent;
                secont_leaf = *m_pCurrent.pnext;
                p.pnext = second_leaf;
                m_pCurrent.pnext = p;
                *second_leaf.pprev = p;
                m_pCurrent = p;*/
                m_pCurrent = p;
            }

            // применяется в erase и eraseAndNext
            void setLeafPreBegin(leaf* p)
            {
                &p.pnext = self.m_pBegin;
                self.m_pBegin = p;
            }

            // применяется в erase и eraseAndNext
            void setLeafPostEnd(leaf* p)
            {
                (&self.m_pEnd).pnext = p;
                &p.pprev = self.m_pEnd;
                self.m_pEnd = p;
            }

            bool isValid() {
                return false;
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
        };

        virtual ~CDualLinkedList()
        {
        };

        void pushBack(T& data)
        {
            l = leaf(data, nullptr, m_pBegin);
            *m_pBegin.pprev = *l;
            m_pBegin = *l;
        }

        T popBack()
        {
            T tmp;
            return tmp;
        }

        void pushFront(T& data)
        {
            l = leaf(data, m_pEnd, nullptr);
            *m_pEnd.pnext = *l;
            m_pEnd = *l;
        }

        T popFront()
        {
            T tmp;
            return tmp;
        }

        // изменяет состояние итератора. выставляет предыдущую позицию.
        void erase(CIterator& it)
        {

        }

        // изменяет состояние итератора. выставляет следующую позицию.
        void eraseAndNext(CIterator& it)
        {
        }

        int getSize()
        {
            return 0;
        }

        void clear()
        {
            l = m_pBegin;
            while (l.pnext != nullptr) {
                l = l.pnext;
                free(l.pprev);
            }
        }

        CIterator begin()
        {
            return CIterator();
        }

        CIterator end()
        {
            return CIterator();
        }

    private:
        leaf* m_pBegin, *m_pEnd;
    };
};
#endif //#ifndef TEMPLATES_LIST_2022_02_03
