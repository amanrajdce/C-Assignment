#include "cutest/CuTest.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Add your tests here
 * A few sample tests
 * are provided
 */

// Tests for Fixed Stack //
void TestisEmpty(CuTest *tc) {
  Stack* s = makeStack(10);
  CuAssertTrue(tc, isEmpty(s));
  push(s, 1, "black");
  push(s, 2, "jack");
  CuAssertFalse(tc, isEmpty(s));
  cleanStack(s);
}

void TestClear(CuTest *tc) {
  Stack* s = makeStack(10);
  push(s, 1, "black");
  push(s, 2, "jack");
  clear(s);
  CuAssertTrue(tc, isEmpty(s));
  cleanStack(s);
}

void TestPop(CuTest *tc) {
  Stack* s = makeStack(10);
  push(s, 1, "black");
  push(s, 2, "jack");
  Element* e = pop(s);
  CuAssertIntEquals(tc, 2, e->key);
  CuAssertStrEquals(tc, "jack", e->value);
  cleanStack(s);
}

void TestPopWhenEmpty(CuTest *tc) {
  Stack* s = makeStack(10);
  Element* e = pop(s);
  CuAssertPtrEquals(tc, NULL, e);
  cleanStack(s);
}

void TestPushWhenFull(CuTest *tc) {
  Stack* s = makeStack(3);
  push(s, 1, "black");
  push(s, 2, "jack");
  push(s, 3, "jill");
  CuAssertFalse(tc, push(s, 4, "john"));
  cleanStack(s);
}

void TestPeek(CuTest *tc) {
  Stack* s = makeStack(5);
  push(s, 1, "black");
  push(s, 2, "jack");
  push(s, 3, "jill");
  Element* e1 = peek(s);
  CuAssertIntEquals(tc, 3, e1->key);
  CuAssertStrEquals(tc, "jill", e1->value);
  Element* e2 = pop(s);
  CuAssertIntEquals(tc, 3, e2->key);
  CuAssertStrEquals(tc, "jill", e2->value);
  cleanStack(s);
}

void TestPeekWhenEmpty(CuTest *tc) {
  Stack* s = makeStack(5);
  Element* e = peek(s);
  CuAssertPtrEquals(tc, NULL, e);
  cleanStack(s);
}

void TestCurrentSize(CuTest *tc) {
  Stack* s = makeStack(10);
  push(s, 0, "black");
  push(s, 1, "jack");
  push(s, 2, "jill");
  int size = currentSize(s);
  CuAssertIntEquals(tc, 3, size);
  cleanStack(s);
}

void TestCurrentSizeWhenEmpty(CuTest *tc) {
  Stack* s = makeStack(10);
  int size = currentSize(s);
  CuAssertIntEquals(tc, 0, size);
  cleanStack(s);
}

void TestisFull(CuTest *tc) {
  Stack* s = makeStack(3);
  CuAssertFalse(tc, isFull(s));
  push(s, 0, "black");
  push(s, 1, "jack");
  push(s, 2, "jill");
  CuAssertTrue(tc, isFull(s));
  cleanStack(s);
}

void TestMultiPop(CuTest *tc) {
  Stack* s = makeStack(10);
  push(s, 0, "black");
  push(s, 1, "jack");
  push(s, 2, "jill");
  push(s, 3, "bill");
  int k = 3;
  Element** arr = multiPop(s, k);
  CuAssertIntEquals(tc, 3, arr[0]->key);
  CuAssertStrEquals(tc, "bill", arr[0]->value);
  CuAssertIntEquals(tc, 1, arr[2]->key);
  CuAssertStrEquals(tc, "jack", arr[2]->value);
  cleanStack(s);
  free(arr);
}

void TestMultiPopSizeLessthanK(CuTest *tc) {
  Stack* s = makeStack(10);
  push(s, 0, "black");
  push(s, 1, "jack");
  push(s, 3, "bill");
  int k = 5;
  Element** arr = multiPop(s, k);
  CuAssertIntEquals(tc, 3, arr[0]->key);
  CuAssertStrEquals(tc, "bill", arr[0]->value);
  CuAssertIntEquals(tc, 0, arr[2]->key);
  CuAssertStrEquals(tc, "black", arr[2]->value);
  cleanStack(s);
  free(arr);
}

void TestMultiPopEmpty(CuTest *tc) {
  Stack* s = makeStack(10);
  Element** arr = multiPop(s, 3);
  CuAssertPtrEquals(tc, NULL, arr);
  cleanStack(s);
  free(arr);
}

void TestReverse(CuTest *tc) {
  Stack* s = makeStack(10);
  push(s, 0, "black");
  push(s, 1, "jack");
  push(s, 2, "jill");
  push(s, 3, "bill");
  reverse(s);
  Element* e = pop(s);
  CuAssertIntEquals(tc, 0, e->key);
  CuAssertStrEquals(tc, "black", e->value);
  cleanStack(s);
}

void TestPushUniqueWithSameElement(CuTest *tc) {
  Stack* s = makeStack(10);
  push(s, 0, "black");
  push(s, 1, "jack");
  push(s, 2, "jill");
  CuAssertFalse(tc, pushUnique(s, 2, "jill"));
  Element* e = pop(s);
  CuAssertIntEquals(tc, 2, e->key);
  CuAssertStrEquals(tc, "jill", e->value);
  cleanStack(s);
}

void TestPushUniqueWithDiffElement(CuTest *tc) {
  Stack* s = makeStack(10);
  push(s, 0, "black");
  push(s, 1, "jack");
  push(s, 2, "jill");
  CuAssertTrue(tc, pushUnique(s, 5, "laila"));
  Element* e = pop(s);
  CuAssertIntEquals(tc, 5, e->key);
  CuAssertStrEquals(tc, "laila", e->value);
  cleanStack(s);
}

void TestPushUniqueOverflow(CuTest *tc) {
  Stack* s = makeStack(3);
  push(s, 0, "black");
  push(s, 1, "jack");
  push(s, 2, "jill");
  CuAssertFalse(tc, pushUnique(s, 3, "jill"));
  cleanStack(s);
}

void TestSearch(CuTest *tc) {
  Stack* s = makeStack(10);
  push(s, 0, "black");
  push(s, 1, "jack");
  push(s, 2, "bella");
  push(s, 5, "valerian");
  int idx = search(s, 1, "jack" );
  CuAssertIntEquals(tc, 3, idx);
  cleanStack(s);
}

void TestSearchDuplicate(CuTest *tc) {
  Stack* s = makeStack(10);
  push(s, 0, "black");
  push(s, 2, "bella");
  push(s, 1, "jack");
  push(s, 2, "bella");
  push(s, 5, "valerian");
  push(s, 1, "jack");
  int idx1 = search(s, 1, "jack" );
  int idx2 = search(s, 2, "bella" );
  CuAssertIntEquals(tc, 1, idx1);
  CuAssertIntEquals(tc, 3, idx2);
  cleanStack(s);
}

void TestSearchStackEmpty(CuTest *tc) {
  Stack* s = makeStack(10);
  int idx = search(s, 1, "jack" );
  CuAssertIntEquals(tc, -1, idx);
  cleanStack(s);
}

void TestSearchWhenElementNotFound(CuTest *tc) {
  Stack* s = makeStack(10);
  push(s, 1, "jack");
  push(s, 2, "bella");
  push(s, 5, "valerian");
  int idx = search(s, 4, "jack" );
  CuAssertIntEquals(tc, -1, idx);
  cleanStack(s);
}

void TestgetCapacity(CuTest *tc) {
  Stack* s = makeStack(10);
  CuAssertIntEquals(tc, 10, getCapacity(s));
  cleanStack(s);
}

// Tests for Growable Stack //
void TestgetCapacityG(CuTest *tc) {
  Stack* s = makeStackG(10, 0.6);
  CuAssertIntEquals(tc, 10, getCapacity(s));
  push(s, 0, "black");
  push(s, 2, "bella");
  push(s, 1, "jack");
  push(s, 2, "bella");
  push(s, 5, "valerian");
  push(s, 1, "jack");
  push(s, 12, "daniels");
  CuAssertIntEquals(tc, 20, getCapacity(s));
  cleanStack(s);
}

void TestPopAndCheckSizeG(CuTest *tc) {
  Stack* s = makeStackG(10, 0.5);
  CuAssertIntEquals(tc, 10, getCapacity(s));
  push(s, 0, "black");
  push(s, 2, "bella");
  push(s, 1, "jack");
  push(s, 2, "bella");
  push(s, 5, "valerian");
  push(s, 12, "daniels");
  Element* e = pop(s);
  CuAssertIntEquals(tc, 12, e->key);
  CuAssertStrEquals(tc, "daniels", e->value);
  CuAssertIntEquals(tc, 20, getCapacity(s));
  cleanStack(s);
}

void TestClearG(CuTest *tc) {
  Stack* s = makeStackG(10, 0.5);
  CuAssertIntEquals(tc, 10, getCapacity(s));
  push(s, 0, "black");
  push(s, 2, "bella");
  push(s, 1, "jack");
  push(s, 2, "bella");
  push(s, 5, "valerian");
  push(s, 12, "daniels");
  clear(s);
  CuAssertTrue(tc, isEmpty(s));
  CuAssertIntEquals(tc, 20, getCapacity(s));
  cleanStack(s);
}

void TestisFullG(CuTest *tc) {
  Stack* s = makeStackG(5, 0.6);
  push(s, 0, "black");
  push(s, 2, "bella");
  push(s, 1, "jack");
  push(s, 2, "bella");
  push(s, 4, "bellarium");
  CuAssertFalse(tc, isFull(s));
  cleanStack(s);
}

void TestCurrentSizeG(CuTest *tc) {
  Stack* s = makeStackG(5, 0.6);
  push(s, 0, "black");
  push(s, 2, "bella");
  push(s, 1, "jack");
  push(s, 2, "bella");
  push(s, 4, "bellarium");
  push(s, 6, "regal");
  CuAssertIntEquals(tc, 6, currentSize(s));
  cleanStack(s);
}

// Test cases for Stack which can Grow and Shrink
void TestReziableGnS(CuTest *tc) {
  Stack* s = makeStackGnS(5, 0.6, 0.4);
  push(s, 0, "black");
  push(s, 2, "bella");
  push(s, 1, "jack");
  push(s, 2, "bella");
  push(s, 5, "valkyrie");
  CuAssertIntEquals(tc, 10, getCapacity(s));
  pop(s);
  pop(s);
  CuAssertIntEquals(tc, 5, getCapacity(s));
  CuAssertIntEquals(tc, 3, currentSize(s));
  cleanStack(s);
}

CuSuite* StrUtilGetSuite() {
  CuSuite* suite = CuSuiteNew();

  /** ADD YOUR TESTS HERE **/
  SUITE_ADD_TEST(suite, TestisEmpty);
  SUITE_ADD_TEST(suite, TestClear);
  SUITE_ADD_TEST(suite, TestPop);
  SUITE_ADD_TEST(suite, TestPopWhenEmpty);
  SUITE_ADD_TEST(suite, TestPushWhenFull);
  SUITE_ADD_TEST(suite, TestPeek);
  SUITE_ADD_TEST(suite, TestPeekWhenEmpty);
  SUITE_ADD_TEST(suite, TestCurrentSize);
  SUITE_ADD_TEST(suite, TestCurrentSizeWhenEmpty);
  SUITE_ADD_TEST(suite, TestisFull);
  SUITE_ADD_TEST(suite, TestMultiPop);
  SUITE_ADD_TEST(suite, TestMultiPopSizeLessthanK);
  SUITE_ADD_TEST(suite, TestMultiPopEmpty);
  SUITE_ADD_TEST(suite, TestReverse);
  SUITE_ADD_TEST(suite, TestPushUniqueWithSameElement);
  SUITE_ADD_TEST(suite, TestPushUniqueWithDiffElement);
  SUITE_ADD_TEST(suite, TestPushUniqueOverflow);
  SUITE_ADD_TEST(suite, TestSearch);
  SUITE_ADD_TEST(suite, TestSearchDuplicate);
  SUITE_ADD_TEST(suite, TestSearchStackEmpty);
  SUITE_ADD_TEST(suite, TestSearchWhenElementNotFound);
  SUITE_ADD_TEST(suite, TestgetCapacity);
  SUITE_ADD_TEST(suite, TestgetCapacityG);
  SUITE_ADD_TEST(suite, TestPopAndCheckSizeG);
  SUITE_ADD_TEST(suite, TestClearG);
  SUITE_ADD_TEST(suite, TestisFullG);
  SUITE_ADD_TEST(suite, TestCurrentSizeG);
  SUITE_ADD_TEST(suite, TestReziableGnS);
  return suite;
}

// Don't edit below this line

void RunAllTests(void) {
  CuString *output = CuStringNew();
  CuSuite* suite = CuSuiteNew();
  CuSuite* ourSuite = StrUtilGetSuite();

  CuSuiteAddSuite(suite, ourSuite);

  CuSuiteRun(suite);
  CuSuiteSummary(suite, output);
  CuSuiteDetails(suite, output);
  printf("%s\n", output->buffer);

  CuStringDelete(output);
  CuSuiteDelete(suite);
  free(ourSuite);
}

int main(void) {
  RunAllTests();
  return 0;
}
