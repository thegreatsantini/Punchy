# Bacon Byte — Lesson 2: Functions (Punchy, Python)

**Big question:** "How do I stop copy-pasting the same code?"

## Before class
- Copy **only** `punchy_l2.py` to Punchy: `scp punchy_l2.py pi@punchy.local:~/`
- Make sure the C `punchy` program isn't running (it holds the same pins).
- Pins (canonical map): LEDs 17/18/27/22/23, buttons 5/6/13/19/26.
- Run: `python3 punchy_l2.py`. No sudo or compile step needed.
- Backup plan if `punchy.local` won't resolve on Bacon wifi: use a phone hotspot.

## Run sheet (predict → change → run)

| # | Exercise | Ask them to predict | What happens |
|---|---|---|---|
| 0 | **Read the file.** Count the copies. | "How many times does the same idea appear?" | Five button blocks, plus the blink written out longhand. |
| 1 | **Play the puzzle.** | "Can you win?" | **You can't.** Button 4 lights LED 5, and the print says "LED 4 on". |
| 2 | **Find the bug.** | "The print says LED 4. Why does LED 5 light?" | Block 4 says `led5.on()`, a copy-paste leftover. Lesson: *the print lied; the hardware told the truth.* |
| 3 | **`set_led(n, on)`** | "How many lines change if we rename a pin now?" | Teaches **parameters**. Hide the `n - 1` inside the function so the rest of the code counts 1–5 like humans do. |
| 4 | **`is_lit(n)` and `just_pressed(n)`** | "What does `just_pressed` give back?" | Teaches **return values**. The `was1…was5` mess collapses. |
| 5 | **`can_light(n)`** | "Where does the puzzle rule live now?" | In **one** place. Change the rule once and all 5 buttons obey. |
| 6 | **`handle_button(n)` and the loop** | "What does the main loop look like now?" | `for n in range(1, 6)`. Five blocks become three lines. The bug can't exist anymore. |
| 7 | **`blink_all(times)`** | "Change `blink_all(2)` to `blink_all(5)`." | A parameter is a dial on the function. |

**Bridge (last 5 min):** open `charlotte.cpp` and point at `drive()`. "You used functions last week and didn't know it."

## Go further
- **Change the rule:** LED 3 needs *both* 1 and 2 lit. Only edit `can_light`.
- **New function:** `reset()` turns everything off, bound to holding button 1.
- **Naming test:** could a teammate guess what the function does from its name alone?

## Mentor notes
- Tonight introduces lists as a "numbered shelf." Don't go deeper; that belongs to OOP later.
- Let *them* find the bug. Don't point at line numbers.
- The solution is in `punchy_l2_solution.py`. Keep it off the Pi.