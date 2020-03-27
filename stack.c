#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stack.h"

// pop function for stack
Element* pop(Stack* s){
  Element* e = NULL;
  if (currentSize(s)==0) { return e; }
  if (s->dynamic){
    if (currentSize(s) <= (int)(s->shrinkFactor*s->capacity)) {
      // half the size
      int newC = (int)(s->capacity/2);
      // free the latter half space
      for(int i=newC; i < s->capacity; i++){
        free(s->elements[i]);
      }
      s->capacity = newC;
    }
  }
  e = s->elements[s->top--];
  return e;
}

// pop multiple elements from stack
Element** multiPop(Stack* s, int k){
  Element** array = NULL;
  // empty stack return NULL
  if (currentSize(s) == 0) { return array; }
  if (k > currentSize(s)) { k = currentSize(s); }
  array = malloc(sizeof(Element*) * k);
  for (int i=0; i < k; i++){
    array[i] = pop(s);
  }
  return array;
}

// Utility function: add element for push
void addE(Stack* s, int k, char* v) {
  Element* newE = malloc(sizeof(Element));
  newE->key = k;
  newE->value = v;
  s->elements[++s->top] = newE;
}

// Utility function: expandCapacity for push
void expandCapacity(Stack* s) {
  int newCapacity = s->capacity * 2;
  Element** newArray = malloc(sizeof(Element*) * newCapacity);
  int currS = currentSize(s);
  // copy the data to new location
  for(int i = 0; i < currS; i++) {
    newArray[i] = s->elements[i];
  }
  free(s->elements);
  s->elements = newArray;
  s->capacity = newCapacity;
}

// push function for stack
bool push(Stack* s, int k, char* v){
  if (!s->dynamic){
    if (s->top >= s->capacity-1) { return false; }
    else {
      addE(s, k, v);
      return true;
    }
  }
  else {
    if (currentSize(s) >= (int)(s->growthFactor * s->capacity)){
      expandCapacity(s);
    }
  }
  addE(s, k, v);
  return true;
}

// push unique function for stack
bool pushUnique(Stack* s, int k, char* v){
  Element* e = peek(s);
  // when stack is not empty
  if (e != NULL) {
    if ((e->key == k) && (e->value == v)) { return false; }
 }
  return push(s, k, v);
}

// reverse the elements in stack
void reverse(Stack* s){
  Element** newArray = malloc(sizeof(Element*) * s->capacity);
  int currS = currentSize(s);
  int topidx = s->top;
  for(int i = 0; i < currS; i++) {
    newArray[i] = s->elements[topidx-i];
  }
  free(s->elements);
  s->elements = newArray;
}

// peek function for stack
Element* peek(Stack* s){
  Element* e = NULL;
  if (currentSize(s)==0) { return e; }
  e = s->elements[s->top];
  return e;
}

// search for element from top of stack
int search(Stack* s, int k, char* v){
  if (currentSize(s) == 0) { return -1; }
  for (int i = s->top; i >= 0; i--){
    if ((s->elements[i]->key == k) && (s->elements[i]->value == v)){
      return s->top+1-i;
    }
  }
  return -1;
}

// get current capacity of stack
int getCapacity(Stack* s){
  return s->capacity;
}

//check if stack is full
bool isFull(Stack* s){
  if (s->dynamic) { return false; }
  else {
    if (s->top == s->capacity-1) { return true; }
    else { return false; }
  }
}

// clear the stack
void clear(Stack *s) {
  s->top = -1;
}

// clean the stack
void cleanStack(Stack *s) {
  for(int i = 0; i < s->capacity; i++) {
    free(s->elements[i]);
  }
	free(s->elements);
	free(s);
}

// current size of stack
int currentSize(Stack* s){
  return s->top + 1;
}

// check if stack empty
bool isEmpty(Stack* s){
  int size = currentSize(s);
  if (size>0) { return false; }
  else { return true; }
}

// Stack with fixed capacity
Stack* makeStack(int cap){
  Stack* s = malloc(sizeof(Stack));
  s->capacity = cap;
  s->top = -1;
  s->dynamic = false;
  s->growthFactor = -1.0;
  s->shrinkFactor = -1.0;
  s->elements = malloc(sizeof(Element*) * cap);
  return s;
}

// Stack that can grow
Stack* makeStackG(int cap, float growF){
  Stack* s = malloc(sizeof(Stack));
  s->capacity = cap;
  s->top = -1;
  s->dynamic = true;
  s->growthFactor = growF;
  s->shrinkFactor = -1.0;
  s->elements = malloc(sizeof(Element*) * cap);
  return s;
}

// Stack that can grow and shrink
Stack* makeStackGnS(int cap, float growF, float shrinkF){
  Stack* s = malloc(sizeof(Stack));
  s->capacity = cap;
  s->top = -1;
  s->dynamic = true;
  s->growthFactor = growF;
  s->shrinkFactor = shrinkF;
  s->elements = malloc(sizeof(Element*) * cap);
  return s;
}
