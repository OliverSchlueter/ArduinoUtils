#define UINT_MAX 0xffffffff

template <typename T>
class List{
public:
    List(T* startingValues, unsigned int startingLength):length(startingLength), actualLength(startingLength){
        values = startingValues;
    }

    List(){
        clear();
    }

    int getLength(){
        return length;
    }

    /*
        Returns the length of
        the internal array.
    */
    int getActualLength(){
        return actualLength;
    }

    T get(unsigned int index){
        outOfRangeCheck(index);

        return values[index];
    }

    T* getElementPtr(unsigned int index){
        outOfRangeCheck(index);

        return &values[index];
    }

    bool contains(T element){
        for(unsigned int i; i < length; i++){
            if(values[i] == element){
                return true;
            }
        }

        return false;
    }

    /*
        Returns UINT_MAX if not found.
    */
    unsigned int getIndexOf(T element){
        for(unsigned int i; i < length; i++){
            if(values[i] == element){
                return i;
            }
        }

        return UINT_MAX;
    }

    void add(T element){
        if(length + 1 >= actualLength){
            growArray();
        }

        values[length] = element;
        length++;
    }

    /*
        Adds the element to the
        front of the list.
    */
    void addFront(T element){
        if(length + 1 >= actualLength){
            growArray();
        }

        for(unsigned int i = length; i > 0; i--){
            values[i] = values[i-1];
        }

        values[0] = element;

        length++;
    }

    /*
        Removes all elements in the list,
        that match with the given input.
    */
    void removeElement(T element){
        for(unsigned int i = 0; i < length; i++){
            if(values[i] == element){
                remove(i);
            }
        }
    }

    /*
        Removes the element at
        a certain index.
    */
    bool remove(unsigned int index){
        outOfRangeCheck(index);

        for(unsigned int i = index+1; i < length; i++){
            values[i-1] = values[i];
        }

        length--;

        unsigned int possibleNewLength = actualLength / 1.5;
        if(possibleNewLength > 10 && possibleNewLength >= length){
            shrinkArray();
        }

        return true;
    }

    void set(unsigned int index, T element){
        outOfRangeCheck(index);

        values[index] = element;
    }

    void reverse(){
        for(unsigned int i = 0; i < length/2; i++){
            int rightIndex = length - 1 - i;
            T right = values[rightIndex];
            values[rightIndex] = values[i];
            values[i] = right;
        }
    }

    void clear(){
        values = new T[10];
        actualLength = 10;
        length = 0;
    }

private:
    unsigned int length;
    unsigned int actualLength;
    T* values;

    void outOfRangeCheck(unsigned int index){
        if(index >= length || index < 0){
            throw "Out of range";
        }
    }

    void growArray(){
        int oldActualLength = actualLength;

        // copy the values
        T oldValues[actualLength];
        for (unsigned int i = 0; i < actualLength; i++) {
            oldValues[i] = values[i];
        }

        // resize the length
        actualLength *= 1.5;

        // create new empty array
        values = new T[actualLength];

        // refill with the old values
        for (unsigned int i = 0; i < oldActualLength; i++) {
            values[i] = oldValues[i];
        }
    }

    void shrinkArray(){
        unsigned int newActualLength = actualLength / 1.5;

        T newValues[newActualLength];
        for (unsigned int i = 0; i < newActualLength; i++) {
            newValues[i] = values[i];
        }

        actualLength = newActualLength;

        values = new T[newActualLength];
        for (unsigned int i = 0; i < newActualLength; i++) {
            values[i] = newValues[i];
        }
    }
};
