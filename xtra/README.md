## xtra
### C made a little easier
- A little C library that has a load of QOL definitions
### Features
- Alt names for various operators
- GetType method for type of value
- Better pythpn-style casting
- Dynamic Vectors and fixed-size matrices

## Methods
### Struct: XtraVector

Represents a dynamic 1D vector.

**Members:**
- `length`: Current length of the vector.
- `max`: Maximum capacity of the vector.

### Function: NewXtraVector

Creates a new `XtraVector` instance.

**Parameters:**
- `maxsize`: Maximum capacity of the vector (optional, defaults to 16 if not provided).

**Returns:** Pointer to the created `XtraVector` instance.

### Function: XtraVectorPush

Adds an element to the end of the `XtraVector`.

**Parameters:**
- `vec`: Pointer to the `XtraVector` instance.
- `data`: Pointer to the data element to be added.

**Returns:** XtraVectorReturn enum indicating success or failure.

### Function: XtraVectorPop

Removes and returns the last element from the `XtraVector`.

**Parameters:**
- `vec`: Pointer to the `XtraVector` instance.

**Returns:** Pointer to the removed element, or NULL if the vector is empty.

### Function: XtraVectorIndex

Returns the element at the specified index in the `XtraVector`.

**Parameters:**
- `vec`: Pointer to the `XtraVector` instance.
- `index`: Index of the element to retrieve.

**Returns:** Pointer to the element at the specified index, or NULL if the index is out of bounds.

### Function: XtraVectorDelete

Deletes the `XtraVector` and frees the associated memory.

**Parameters:**
- `vec`: Pointer to the `XtraVector` instance.

### Function: XtraVectorDelEl

Creates a new `XtraVector` without the specified element.

**Parameters:**
- `vec`: Pointer to the `XtraVector` instance.
- `el`: Index of the element to be removed.

**Returns:** Pointer to the new `XtraVector` instance.

### Function: XtraVectorChangeEl

Creates a new `XtraVector` with the specified element replaced.

**Parameters:**
- `vec`: Pointer to the `XtraVector` instance.
- `el`: Index of the element to be replaced.
- `data`: Pointer to the new data element.

**Returns:** Pointer to the new `XtraVector` instance.

### Struct: XtraVector2D

Represents a dynamic 2D vector.

**Members:**
- `CurrWidth`: Current width of the vector.
- `CurrLength`: Current length of the vector.

### Function: NewXtraVector2D

Creates a new `XtraVector2D` instance.

**Parameters:**
- `max_width`: Maximum width of the vector (optional, defaults to 16 if not provided).
- `max_length`: Maximum length of the vector (optional, defaults to 16 if not provided).

**Returns:** Pointer to the created `XtraVector2D` instance.

### Function: XtraVector2DPush

Adds an element to the specified row in the `XtraVector2D`.

**Parameters:**
- `vec`: Pointer to the `XtraVector2D` instance.
- `data`: Pointer to the data element to be added.
- `row`: Row index where the element will be added.

**Returns:** XtraVectorReturn enum indicating success or failure.

### Function: XtraVector2DNewRow

Adds a new empty row to the `XtraVector2D`.

**Parameters:**
- `vec`: Pointer to the `XtraVector2D` instance.

**Returns:** XtraVectorReturn enum indicating success or failure.

### Function: XtraVector2DGrab

Retrieves the element at the specified coordinates in the `XtraVector2D`.

**Parameters:**
- `vec`: Pointer to the `XtraVector2D` instance.
- `row`: Row index of the element.
- `col`: Column index of the element.

**Returns:** Pointer to the element at the specified coordinates, or NULL if the coordinates are out of bounds.

### Function: XtraVector2DDelete

Deletes the `XtraVector2D` and frees the associated memory.

**Parameters:**
- `vec`: Pointer to the `XtraVector2D` instance.
