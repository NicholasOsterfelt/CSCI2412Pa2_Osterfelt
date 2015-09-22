#include <iostream>
#include "Point.h"
#include "Cluster.h"
#include <assert.h>

using namespace std;
using namespace Clustering;
        //function Prototypes
void pTestConstructor1();
void pTestConstructor2();
void pTestCopyConstructor();
void pTestAssignmentOperator();
void pTestGetDims();
void pTestSetValue();
void pTestGetValue();
void pTestDistanceTo();
void pTestMultiplyOperator1();
void pTestDivideOperator1();
void pTestMultiplyEqualOperator();
void pTestDivideEqualOperator();
void pTestAdditionOperator();
void pTestSubtractionOperator();
void pTestAdditionEqualOperator();
void pTestSubtractionEqualOperator();
void pTestCEqualOperator();
void pTestCNEqualOperator();
void pTestCLessOperator();
void pTestCGreaterOperator();
void pTestCLessEqualOperator();
void pTestCGreaterEqualOperator();
void pTestOstreamOperator();

int main() {
    pTestConstructor1();
    pTestConstructor2();
    pTestCopyConstructor();
    pTestAssignmentOperator();
    pTestGetDims();
    pTestSetValue();
    pTestGetValue();
    pTestDistanceTo();
    pTestMultiplyOperator1();
    pTestDivideOperator1();
    pTestMultiplyEqualOperator();
    pTestDivideEqualOperator();
    pTestAdditionOperator();
    pTestSubtractionOperator();
    pTestAdditionEqualOperator();
    pTestSubtractionEqualOperator();
    pTestCEqualOperator();
    pTestCNEqualOperator();
    pTestCLessOperator();
    pTestCGreaterOperator();
    pTestCLessEqualOperator();
    pTestCGreaterEqualOperator();
    pTestOstreamOperator();
}
void pTestConstructor1() {
    Point p(2);
    assert(p.getDims() == 2);
    assert(p.getValue(1) == 0 && p.getValue(2) == 0);
}
void pTestConstructor2() {
    double values[] = {1,2,3,4,5};
    double *pValues = values;
    Point p1(3,pValues);

    assert(p1.getDims() == 3);
    assert(p1.getValue(1) == 1 && p1.getValue(2) == 2 && p1.getValue(3) == 3);
}
void pTestCopyConstructor() {
    Point p(3);
    p.setValue(1, 1);
    p.setValue(2,2);
    p.setValue(3,3);
    Point p1(p);
    assert(p == p1);
}
void pTestAssignmentOperator(){
    Point p(3);
    p.setValue(1, 1);
    p.setValue(2,2);
    p.setValue(3,3);
    Point p1 = p;
    assert(p == p1);
}
void pTestGetDims() {
    Point p(3);
    assert(p.getDims() == 3);
}
void pTestSetValue() {
    Point p(3);
    p.setValue(1, 5);
    p.setValue(2, -5);
    assert(p.getValue(1) == 5 && p.getValue(2) == -5);
}
void pTestGetValue() {
    Point p(3);
    p.setValue(1,2);
    assert(p.getValue(1) == 2);
}
void pTestDistanceTo() {
    Point p(2);
    p.setValue(1, 27);
    p.setValue(2, 9);
    Point p1(2);
    p.setValue(1, 3);
    p.setValue(2, 2);
    assert(p.distanceTo(p1) != 25 );
}
void pTestMultiplyOperator1()
{
    Point p(2);
    p.setValue(1, 2);
    p.setValue(2, 3);
    Point p1(2);
    p1 = p*2;
    assert(p1.getValue(1) == 4 && p1.getValue(2) == 6);
}
void pTestDivideOperator1()
{
    Point p(2);
    p.setValue(1, 4);
    p.setValue(2, 6);
    Point p1(2);
    p1 = p/2;
    assert(p1.getValue(1) == 2 && p1.getValue(2) == 3);
}
void pTestMultiplyEqualOperator() {
    Point p(2);
    p.setValue(1, 2);
    p.setValue(2, 3);
    p*=2;
    assert(p.getValue(1) == 4 && p.getValue(2) == 6);
}
void pTestDivideEqualOperator() {
    Point p(2);
    p.setValue(1, 4);
    p.setValue(2, 6);
    p/=2;
    assert(p.getValue(1) == 2 && p.getValue(2) == 3);
}
void pTestAdditionOperator() {
    Point p(2);
    p.setValue(1, 2);
    p.setValue(2, 3);
    Point p1(2);
    p1.setValue(1, 2);
    p1.setValue(2, 3);
    Point p3(2);
    p3 = p+p1;
    assert(p3.getValue(1) == 4 && p3.getValue(2) == 6);
}
void pTestSubtractionOperator() {
    Point p(2);
    p.setValue(1, 6);
    p.setValue(2, 9);
    Point p1(2);
    p1.setValue(1, 2);
    p1.setValue(2, 3);
    Point p3(2);
    p3 = p-p1;
    assert(p3.getValue(1) == 4 && p3.getValue(2) == 6);
}
void pTestAdditionEqualOperator() {
    Point p(2);
    p.setValue(1, 2);
    p.setValue(2, 3);
    Point p1(2);
    p1.setValue(1, 2);
    p1.setValue(2, 3);

    p += p1;
    assert(p.getValue(1) == 4 && p.getValue(2) == 6);
}
void pTestSubtractionEqualOperator() {
    Point p(2);
    p.setValue(1, 6);
    p.setValue(2, 9);
    Point p1(2);
    p1.setValue(1, 2);
    p1.setValue(2, 3);
    p-=p1;
    assert(p.getValue(1) == 4 && p.getValue(2) == 6);
}
void pTestCEqualOperator()
{
    Point p(2);
    p.setValue(1, 6);
    p.setValue(2, 9);
    Point p1(2);
    p1.setValue(1, 6);
    p1.setValue(2, 9);
    assert(p == p1);
}
void pTestCNEqualOperator()
{
    Point p(2);
    p.setValue(1, 6);
    p.setValue(2, 10);
    Point p1(2);
    p1.setValue(1, 6);
    p1.setValue(2, 9);
    assert(p != p1);
}
void pTestCLessOperator(){
    Point p(2);
    p.setValue(1, 6);
    p.setValue(2, 5);
    Point p1(2);
    p1.setValue(1, 6);
    p1.setValue(2, 9);
    assert(p < p1);
}
void pTestCGreaterOperator(){
    Point p(2);
    p.setValue(1, 6);
    p.setValue(2, 10);
    Point p1(2);
    p1.setValue(1, 6);
    p1.setValue(2, 9);
    assert(p > p1);
}
void pTestCLessEqualOperator(){
    Point p(2);
    p.setValue(1, 6);
    p.setValue(2, 5);
    Point p1(2);
    p1.setValue(1, 6);
    p1.setValue(2, 9);
    Point p2(2);
    p2.setValue(1,6);
    p2.setValue(2,5);
    assert(p <= p1 && p <= p2);
}
void pTestCGreaterEqualOperator(){
    Point p(2);
    p.setValue(1, 6);
    p.setValue(2, 5);
    Point p1(2);
    p1.setValue(1, 6);
    p1.setValue(2, 4);
    Point p2(2);
    p2.setValue(1,6);
    p2.setValue(2,5);
    assert(p >= p1 && p >= p2);
}
void pTestOstreamOperator(){
    Point p(2);
    p.setValue(1, 6);
    p.setValue(2, 5);
    cout <<"Point p has values (6,5)" << endl;
    cout <<"This is p using Ostream Operator: " << p << endl;
}

