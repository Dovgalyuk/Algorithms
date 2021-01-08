import platform.posix.rand
import platform.posix.system

fun main() {

    val array = Array<Int>(readLine()?.toInt() ?: 5)
    for (i in 0 until array.size) {
        array[i] = rand() % 100 - 50
    }
    var count = 0
    var summ = 0
    for (i in 0 until array.size) {
        if (array[i] >= 0){
            summ += array[i]
            ++count
        }
    }
    if (count > 0){
        println(summ / count)
        array.print()
    } else {
        println("There is no positive numbers is array")
        array.print()
    }
    system("Pause")
}

fun testArray(){
    val arr = Array<Int>(10)
    assert(arr.size == 10)
    for (i in 0 until 10){
        arr[i] = i * 2
    }

    for (i in 0 until 10){
        assert(arr[i] == i * 2)
    }
}