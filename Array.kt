class Array<T>(val size: Int) {
    private val data = ArrayList<T>(size)

    operator fun get(index: Int): T {
        if (index !in (0 until size)){
            throw IndexOutOfBoundsException()
        } else {
            return data[index]
        }
    }

    operator fun set(index: Int, value: T){
        when {
            index !in (0 until size) -> {
                throw IndexOutOfBoundsException()
            }
            data.size <= index -> {               //Если в динамическом массиве поле с таким индексом ещё не существует, то заполняем его "мусором"
                while (data.size <= index){
                    data.add(value)
                }
            }
            else -> {
                data[index] = value
            }
        }
    }

    fun print(){
        println("$size : $data")
    }
}