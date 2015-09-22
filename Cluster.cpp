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
        points = c.getPoints();
    }
    void Cluster:: add(const PointPtr &p)
    {
        LNode *point = new LNode;
        (*point).p = p;

        if(size == 0)
        {
            size++;
            points = point;
        }
        else {
            size++;
            for (int n = 0; n < size; n++) {

                if (*p < *(points[n].p)) {
                    (*point).next = &points[n];
                    if (n + 1 > size) {
                        points[n].next = nullptr;
                    }
                    else {
                        points[n].next = &points[n + 1];
                    }
                }
            }
        }
    }
    Cluster:: ~Cluster()
    {
        for(int n =0; n < size; n++)
        {
            delete points[n].p;
        }
        for(int n = 0; n < size; n++)
        {
            delete points[n].next;
        }
        delete [] points;
    }
}
