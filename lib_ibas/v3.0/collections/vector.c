//
// Created by Павел on 16.03.2017.
//

#include "vector.h"
#include "../base/ibas.h"

#define $class Vector

$defineClass(Object)(
    $implements(List, 4)
);

$constructor (new)(size_t elemSize, size_t capacity, ToString_t stringifier)(
    if (!elemSize) throw(IllegalArgumentException, "Vector: elemSize must be greater than zero!");
    $construct;

    self->size = self->capacity = 0;
    self->storage = NULL;
    self->elemSize = elemSize;
    self->stringifier = stringifier;

    $this(ensureCapacity)(capacity);
)

void $public (destroy)()(
    if (!self) return;

    $this(clear)();
    free(self);
)

String_t $public (toString)()(
    if (self->stringifier) return List.toString(self, self->stringifier);
    else return String.format("[[Vector size=%zd elemSize=%zd storage=%p]]", self->size, self->elemSize, self->storage);
)

void $public (ensureCapacity)(size_t capacity)(
    if (capacity <= self->capacity) return;

    Pointer storage = realloc(self->storage, capacity * self->elemSize);
    if (!storage) throw(NotEnoughMemoryException, "Could not increase the vector's capacity");

    self->storage = storage;
    self->capacity = capacity;
)

Pointer $public (get)(int i)(
    if (i < 0 || i >= self->size) throw(IllegalArgumentException, "Vector: index out of bounds!");

    Pointer iter = $this(iter)(i);
    return $this(iterGet)(iter);
)

void $public (set)(int i, Pointer val)(
    if (i < 0 || i >= self->size) throw(IllegalArgumentException, "Vector: index out of bounds!");

    Pointer iter = $this(iter)(i);
    $this(iterSet)(iter, val);
)

void $private (insertSlice)(int i, Pointer slice, size_t size)(
    if (i < 0 || i > self->size) throw(IllegalArgumentException, "Vector: index out of bounds!");

    size_t cap = self->capacity;
    while (cap < self->size + size) {
      cap = max((size_t) (cap * VECTOR_GROWTH_FACTOR), cap + 1);
    }
    $this(ensureCapacity)(cap);

    Pointer ptr = self->storage + i * self->elemSize;
    memmove(ptr + size * self->elemSize, ptr, self->elemSize * (self->size - i));
    memcpy(ptr, slice, size * self->elemSize);
    self->size += size;
)

void $public (add)(Pointer val)(
    $this(insert)((int) self->size, val);
)

void $public (insert)(int i, Pointer val)(
    $ns(insertSlice)(self, i, val, 1);
)

void $public (addAll)(List_t list)(
    $this(insertAll)((int) self->size, list);
)

void $public (insertAll)(int i, List_t list)(
    Vector_t vec = Object.cast(list, "Vector");
    if (self->elemSize != vec->elemSize) throw(IllegalArgumentException, "Vector: element sizes don't match!");

    $ns(insertSlice)(self, i, vec->storage, vec->size);
)

void $public (remove)(int i)(
    Pointer ptr = $this(get)(i);
    memmove(ptr, ptr + self->elemSize, self->elemSize * (self->size - i - 1));
    self->size--;
)

void $public (clear)()(
    free(self->storage);

    self->size = self->capacity = 0;
    self->storage = NULL;
)

int $private (iterToIndex)(Pointer iter)(
    return (int) ((iter - self->storage) / self->elemSize);
)

int $public (indexOf)(Pointer val)(
    Pointer iter = $this(find)(val);

    if (iter == $this(end)()) return -1;
    else return $ns(iterToIndex)(self, iter);
)

Pointer $public (iter)(int i)(
    if (i < 0 || i >= self->size) return $this(end)();
    else return self->storage + i * self->elemSize;
)

Pointer $public (begin)()(
    return self->storage;
)

Pointer $public (end)()(
    return self->storage + self->size * self->elemSize;
)

Pointer $public (find)(Pointer val)(
    Pointer it = $this(begin)();
    for (; it != $this(end)(); it = $this(iterNext)(it)) {
      if (!memcmp($this(iterGet)(it), val, self->elemSize)) break;
    }

    return it;
)

Pointer $public (iterNext)(Pointer iter)(
    return $this(iterJump)(iter, 1);
)

Pointer $public (iterPrev)(Pointer iter)(
    return $this(iterJump)(iter, -1);
)

Pointer $public (iterJump)(Pointer iter, int length)(
    return $this(iter)($ns(iterToIndex)(self, iter) + length);
)

Pointer $public (iterGet)(Pointer iter)(
    return iter;
)

void $public (iterSet)(Pointer iter, Pointer val)(
    memcpy(iter, val, self->elemSize);
)

void $public (iterInsert)(Pointer iter, Pointer val)(
    $this(insert)($ns(iterToIndex)(self, iter), val);
)

void $public (iterInsertAll)(Pointer iter, List_t list)(
    $this(insertAll)($ns(iterToIndex)(self, iter), list);
)

void $public (iterRemove)(Pointer iter)(
    $this(remove)($ns(iterToIndex)(self, iter));
)

$defineStatic();

$defineMethods();
