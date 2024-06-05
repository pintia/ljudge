open System

while true do
  let line = Console.In.ReadLine()
  match line with
  | null -> exit 0
  | _ -> let a = line.Split [|' '|] |> Seq.sumBy int
         printfn "%d" a