import std.core.*
import std.console.*
import std.collection.*
import std.convert.*

main(): Int64 {
    while (let Some(line) <- Console.stdIn.readln()) {
        let nums = map(Int.parse)(line.split(" "))
        let sum = reduce(0, {a: Int64, b: Int64 => a + b})(nums)
        if (let Some(r) <- sum) {
            Console.stdOut.writeln(sum)
        }
    }
    return 0
}
