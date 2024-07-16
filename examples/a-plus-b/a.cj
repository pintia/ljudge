import std.core.*
import std.console.*
import std.collection.*
import std.convert.*

main(): Int64 {
    while (let Some(line) <- Console.stdIn.readln()) {
        let nums = map(Int.parse)(line.split(" "))
        let sum = reduce({a: Int64, b: Int64 => a + b})(nums)
        if (let Some(r) <- sum) {
            Console.stdOut.writeln(r)
        }
    }
    return 0
}
