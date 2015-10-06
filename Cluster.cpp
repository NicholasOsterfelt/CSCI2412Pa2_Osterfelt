//
// Created by Nick on 9/20/2015.
//

#include "Cluster.h"
#include "Point.h"
#include <cmath>
#include "assert.h"
using namespace std;

namespace Clustering {
    Cluster:: Cluster(const Cluster & c)
    {
        size = c.getSize();
        points = nullptr;
        for(LNodePtr curr = c.getPoints(); curr != nullptr; curr = curr->next)
        {
            Point *newP = new Point(curr->p->getDims());
            for(int n = 0; n < curr->p->getDims(); n++)
            {
                newP->setValue(n+1, 0);
            }
            for(int n = 0; n < newP->getDims(); n++)
            {
                newP->setValue(n+1, curr->p->getValue(n+1));
            }
            add(newP);
        }
       size = c.getSize();
    }
    Cluster &Cluster::operator=(const Cluster &rhs)
    {
        if(*this == rhs)
            return *this;
        size = rhs.getSize();
        deleteAll();
        for(LNodePtr curr = rhs.getPoints(); curr != nullptr; curr = curr->next)
        {
            add(curr->p);
        }
    }

    void Cluster:: add(const PointPtr  &ptr)
    {

        if(points == nullptr)
        {
            size++;
            LNode *newP = new LNode;
            newP->p = ptr;
            newP->next = nullptr;
            points = newP;
        }
        else {
            LNodePtr prev = points;

            for (LNodePtr curr = points; curr != nullptr; curr = curr->next) {
                LNodePtr next = curr->next;
                if (next == nullptr) {
                    if(*ptr <= (*curr->p))
                    {
                        LNode *newP = new LNode;
                        newP->p = ptr;
                        newP->next = curr;
                        curr->next = nullptr;
                        points = newP;
                        size++;
                        break;
                    }
                    else
                    {
                        LNode *newP = new LNode;
                        newP->p = ptr;
                        newP->next = nullptr;
                        curr->next = newP;
                        size++;
                        break;
                    }
                }
                if (*ptr <= (*curr->p)) {

                    LNode *newP = new LNode;
                    newP->p = ptr;
                    newP->next = curr;
                    if(prev != points)
                    {
                        prev->next = newP;
                    }
                    else
                    {
                        points = newP;
                    }
                    size++;
                    break;
                }
                prev = prev->next;
            }
        }
    }
    const PointPtr &Cluster:: remove(const PointPtr & p) {
        LNodePtr nex = points->next;
        LNodePtr prev = points;
        if (points == nullptr) {
            return p;
        }
        if (points->next == nullptr && points->p == p) {
            deleteAll();
            size--;
            return p;
        }

        LNodePtr curr = points;
        while (curr != nullptr) {
            if (*(curr->p) == *p) {
                points = points->next;
//                delete curr->p;
                delete curr;
                size--;
                return p;
            }
            if (nex == nullptr && *(curr->p) == *p) {
//                delete curr->p;
                delete curr;
                size--;
                return p;
            }
            if (nex == nullptr && *(curr->p) != *p) {

                return p;
            }
            if (*(nex->p) == *p) {
                curr->next = curr->next->next;
//                delete nex->p;
                delete nex;
                size--;
                return p;
            }
            nex = nex->next;
            curr = curr->next;
            return p;
        }
    }

    Cluster &Cluster::operator+=(const Point &rhs)
    {
        Point *p = new Point(rhs.getDims());
        *p = rhs;
        add(p);
        return *this;
    }
    Cluster &Cluster::operator-=(const Point &rhs)
    {
        Point *p = new Point(rhs.getDims());
        *p = rhs;
        remove(p);
        return *this;
    }
    void Cluster:: deleteAll()
    {
        if(points != nullptr)
        {
            LNodePtr curr = points;
            if(curr->next == nullptr) {
                delete curr->p;
                delete curr;
            }
            while(curr != nullptr)
            {
                if(curr->next != nullptr )
                {
                    LNodePtr delPtr = curr;
                    curr = curr->next;
                    delete delPtr->p;
                    delete delPtr;
                }
                curr = curr->next;
            }
        }
        points = nullptr;
        size = 0;
    }
        //use do while to avoid first

    Cluster:: ~Cluster()
    {
        deleteAll();
    }

    Cluster &Cluster::operator +=(const Cluster &rhs)
    {       //Adds the pointers of points not in 1 cluster to another]
        for(LNodePtr curr = rhs.getPoints(); curr != nullptr; curr = curr->next)
        {
            bool found = false;
            for(LNodePtr currThis = points; currThis != nullptr; currThis = currThis->next)
            {
                if(curr->p == currThis->p)
                {
                    found = true;
                    break;
                }

            }
            if(found != true)
            {
                Point *p = new Point(curr->p->getDims());
                *p = *(curr->p);
                add(p);
            }
        }

        return *this;
    }

    Cluster &Cluster:: operator-=(const Cluster &rhs)
    {
        LNodePtr checkP = points;

        for(LNodePtr curr = points; curr != nullptr; curr = curr->next)
        {
            bool found = false;
            for(LNodePtr currRhs = rhs.getPoints(); currRhs != nullptr; currRhs = currRhs->next)
            {
                if(curr->p == currRhs->p)
                {
                    found = true;
                    curr = curr->next;
                    break;
                }

            }
            if(found == true)
            {
                LNodePtr delPtr = curr;
                remove(delPtr->p);
            }
        }

        return *this;
    }

    const Cluster operator+(const Cluster &lhs, const Cluster &rhs)
    {
        Cluster newCluster = Cluster();
        newCluster += lhs;
        newCluster += rhs;
        return newCluster;
    }
    const Cluster operator-(const Cluster &lhs, const Cluster &rhs)
    {
        Cluster newCluster = Cluster();
        newCluster = lhs;
        newCluster -=rhs;
        return newCluster;
    }
    std::ostream &operator<<(std::ostream &os, const Cluster &c)
    {
        for(LNodePtr curr = c.getPoints(); curr != nullptr; curr = curr->next)
        {
                cout << *(curr->p);
        }
        return os;
    }
    bool operator==(const Cluster &lhs, const Cluster &rhs)
    {
        if(lhs.getSize() != rhs.getSize())
            return false;
        LNodePtr currRhs =  rhs.getPoints();
        for(LNodePtr currLhs = lhs.getPoints(); currLhs != nullptr; currLhs = currLhs->next)
        {
            if(*(currLhs->p) != *(currRhs->p))
            {
                return false;
            }
            currRhs = currRhs->next;
        }
        return true;
    }
    const Cluster operator+(const Cluster &lhs, const PointPtr &rhs)
    {
        Cluster newCluster = lhs;
        newCluster.add(rhs);
        return newCluster;
    }
    const Cluster operator-(const Cluster &lhs, const PointPtr &rhs)
    {
        Cluster newCluster = lhs;
        newCluster.remove(rhs);
        return newCluster;
    }
}


