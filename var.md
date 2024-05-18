1. Start
2. Check if `input` is NULL or empty
   - If yes, go to step 3
   - If no, go to step 4
3. Add `input` to variable list `v` and end
4. Find the position of the equal sign in `input`
   - If found, go to step 5
   - If not found, go to step 11
5. Create `prefix` from `input` up to the equal sign
6. Remove outer quotes from the string after the equal sign and assign to `unquoted`
7. Check if the string after the equal sign is double quoted and contains a dollar sign
   - If yes, go to step 8
   - If no, go to step 10
8. Expand the variable in `unquoted` and assign to `expanded`
9. Join `prefix` and `expanded` and assign to `new_input`
   - If `new_input` is not NULL, assign `new_input` to `input`
10. Free `input` and assign `unquoted` to `input`
11. Check if `new_input` is not NULL
   - If yes, go to step 12
   - If no, go to step 13
12. Add `new_input` to variable list `v` and end
13. Add `input` to variable list `v` and end