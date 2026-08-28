
STUDENT MISSION BRIEF

CAMPUS QUEST: TEAM CHALLENGE LEADERBOARD
Your group has 180 minutes to build a safe dynamic leaderboard in C++. Complete
the core mission first. Earn badges by proving, not merely claiming, that your
program is correct.
The Scenario
Campus teams complete short missions and earn points. The organizer needs a
program that keeps each team’s ID, name, score, and completed-mission count
together; expands safely when more teams register; searches and removes teams;
produces a ranked leaderboard; saves to a text file; and restores valid records during
the next run.
Team Roles

Role Main responsibility Must explain during checkpoint

Memory Guardian

Owner pointer,
size/capacity, `realloc`,
cleanup

Why failure leaves old state usable

Record Architect

`Team` design,
validation,
complete-record
movement

Why ID/name/score/missions never
separate

Test Captain

Expected results,
boundary cases, test
evidence

Which test exposes each likely
defect

Integration Captain /
Presenter

Menu, function
connections, file flow,
demo

How the complete program moves
from input to saved state

Rotate the keyboard driver at each checkpoint. Every member may be asked any
question.
Required Data Model and File Format

Use the supplied structure:
typedef struct {
int id;
char name[40];
int score;
int missions;
} Team;
File format: one team per line, with four fields separated by `|`:
EXAMPLE
101|Byte Bandits|120|2
102|Pointer Pirates|90|1
Validation rules: ID must be positive and unique; name must not be empty and must fit
the array; score and missions must be nonnegative; mission points entered through the
menu must be from 1 through 100.
Core Mission: Required Features
A. Dynamic collection
Start with `teams = NULL`, `size = 0`, `capacity = 0`. Grow by doubling. Use a
temporary result for `realloc`. Update capacity only after success.
B. Register a team
Validate the complete candidate, reject duplicate ID, expand if necessary, copy the
complete record, then increment size.
C. Record mission points
Find the team by ID. Validate points first. On success, add points and increment
missions. Invalid input leaves the record unchanged.
D. Find a team
Return the matching logical index or −1. Do not search unused capacity.
E. Remove a team
Find by ID, shift complete `Team` objects left, and reduce size exactly once. Missing ID
leaves state unchanged.
F. Show leaderboard
Sort descending by score; use missions as the tie-breaker if possible. Swap complete
`Team` objects. Display only logical records.
G. Load safely

Read one line with `fgets`; parse into temporary fields; validate; reject malformed or
duplicate lines; commit only accepted complete records.
H. Save and clean up
Write all logical records in the documented format; check write and close results; `free`
the allocation exactly once and set the owner to `NULL`.
Required Functions
Function Observable responsibility
findTeamIndex Return the logical index for an ID, otherwise −1
ensureCapacity Guarantee room for `required` records or return

failure without changing owner/capacity

addTeam

Validate, enforce unique ID, ensure room, and
commit one record

recordMission Validate, locate, then update one complete team

state

deleteTeam

Locate, shift complete records, reduce logical
size

sortLeaderboard Order logical records and keep all fields attached
displayTeams Read-only display of indexes below size
loadTeams

Open/read/parse/validate/commit; reject bad
lines safely

saveTeams Write logical records and report file failure
The Four Collection Invariants
● `0 <= size <= capacity`.
● Indexes `0` through `size - 1` are meaningful Team records.
● The owner is either `NULL` for no block or identifies the live allocation.
● Each Team’s ID, name, score, and missions move together as one object.

Checkpoints
Blueprint Gate — by minute 35
● Draw owner, size, capacity, logical range, and unused capacity.
● Write the file format and validation rules.
● State what remains unchanged after failed expansion.
● Divide initial functions among the group, but agree on contracts first.
Memory Gate — by minute 75
● Add teams into capacity 2; add a third team and show capacity grows.
● Reject a duplicate without changing size.
● Delete first and last records safely.
● Explain the temporary-pointer pattern.
Persistence Gate — by minute 140
● Load valid lines.
● Reject one malformed, one duplicate, and one invalid-score line.
● Save, exit, restart, and show the accepted data remains.

Required Test Gauntlet
Test Setup/action Expected evidence
T1 Empty Show leaderboard with

size 0

No read; clear “no teams” output
T2 First add Add ID 101 size becomes 1; complete record

visible
T3 Growth boundary With capacity 2, add

third team

capacity grows safely; first two
records preserved

T4 Duplicate Add ID 101 again Rejected; size and old record

unchanged

T5 Invalid points Add 0 or 101 points Rejected; score and missions

unchanged

T6 Search absent Search unused ID Return/report not found; no mutation
T7 Delete boundaries Delete first, then last Complete records shift; size
decreases; no out-of-range access

T8 Sort identity Use equal/different

scores

Correct rank; every name remains
attached to its ID and fields
T9 Malformed file Add bad field count Line rejected; accepted collection

unchanged

T10 Save/reload Save, exit, rerun

Same accepted logical records
restored

T11 Cleanup Exit normally Allocation freed once; owner no

longer used

For at least six tests, record: input/state, predicted result, actual result, pass/fail, and
defect the test could expose.
Hackathon Rules
● Core safety beats bonus quantity. Bonuses are ignored if the core test gauntlet
fails.
● You may use course slides and your own notes. Cite any code not written by the
group.
● Do not use `std::vector`, a database, or a new collection library; the purpose is to
demonstrate the taught dynamic-array logic.
● Do not change required function responsibilities merely to hide a failure.
● Ask for Hint Level 1, 2, or 3. The instructor records the highest level used.
● Every student must make a visible contribution and answer an oral question.

Submission Checklist
☐ Completed `.cpp` source with group member names in a comment.
☐ Sample `teams.txt` used for the final demonstration.
☐ Test evidence sheet containing at least six required tests.
☐ One screenshot or short note showing successful save/reload.
☐ Individual exit ticket: invariant, bug found, and next improvement.
