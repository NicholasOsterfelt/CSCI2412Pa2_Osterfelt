//
// Created by Nick on 9/20/2015.
//
#include "Cluster.h"
#include "Point.h"
#include <cmath>
#include "assert.h"
#include <sstream>


using namespace std;
namespace Clustering {

    Cluster:: Cluster(const Cluster &c)
    {
        size = c.getSize();
        points = nullptr;
        pdims = c.getDims();
        *centroid = c.getCentroid();
        centroidValid = c.getCValid();
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
        LNode *newP = new LNode;
        newP->p = ptr;
        if(points == nullptr)
        {
            size++;                     //add to empty array
            newP->next = nullptr;
            points = newP;
            return;
        }
        if(points->next == nullptr)
        {
            if(*points->p <= *ptr)      //add to array with 1 element
            {
              points->next = newP;
                newP->next = nullptr;
                return;
            }
            else
            {
                newP->next = points;
                points = newP;
                return;
            }
        }
        if(*ptr <= *points->p)
        {
            newP->next = points;
            points = newP;
            return;
        }
        else
        {
            for(LNodePtr curr = points; curr != nullptr; curr = curr->next)
            {
                LNodePtr next = curr->next;
                if(next == nullptr)
                {
                    curr->next = newP;
                    newP->next = nullptr;
                    return;
                }
                if(*ptr >= *(curr->p) && *ptr <= *(next->p)) {
                    curr->next = newP;
                    newP->next = next;
                    return;
                }
            }
        }
    }
    const PointPtr &Cluster:: remove(const PointPtr & p) {
        LNodePtr nex = points->next;
        Point *Point = p;
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
        delete centroid;
        points = nullptr;
        size = 0;
    }
        //use do while to avoid first

    Cluster:: ~Cluster()
    {
        deleteAll();
//        if(points != nullptr)
//        {
//            LNodePtr curr = points;
//            if(curr->next == nullptr) {
//                delete curr->p;
//                delete curr;
//            }
//            while(curr != nullptr)
//            {
//                if(curr->next != nullptr )
//                {
//                    LNodePtr delPtr = curr;
//                    curr = curr->next;
//                    delete delPtr->p;
//                    delete delPtr;
//                }
//                curr = curr->next;
//            }
//        }
//        points = nullptr;
//        size = 0;
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
                if(*(curr->p) == *(currRhs->p))
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
                cout << "(" << *(curr->p) << ")";
        }
        return os;
    }
    std::istream &operator>>(std::istream &is, Cluster &c)
    {
        istream &i = is;
        string line;
     while(getline(is, line))
     {
         Point *p = new Clustering::Point(c.getDims());
         string temp;
         std:: istringstream lineStream(line);
         while(!lineStream.eof()) {
             if(!(lineStream >> *p)) {break;}
         }
         c.add(p);

     }
        return i;
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


