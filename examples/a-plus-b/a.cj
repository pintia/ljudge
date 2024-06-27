from std import core.*
from std import console.*
from std import collection.*
from std import convert.*

main(): Int64 {
    while (let Some(line) <- Console.stdIn.readln()) {
        let nums = map(Int.parse)(line.split(" "))
        let sum = reduce(0, {a: Int64, b: Int64 => a + b})(nums)
        Console.stdOut.writeln(sum)
    }
    return 0
}
