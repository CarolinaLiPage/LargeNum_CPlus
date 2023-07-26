Error: 2 adjacent parameters of 'mainAddition' of convertible types are easily swapped by mistake
I named them int index1 and int index2 originally, shows the error above, then I tried moved int index2 not right next to int index 1, error stills shows.
Then I changed int index1 to int left, and changed int index2 to int tight, error still shows.

error: function 'operator-' has cognitive complexity of 30 (threshold 25) [readability-function-cognitive-complexity,-warnings-as-errors]
I could potentially take out some of the code in operator- and make it a seperate function, that would reduce the complexity, but it causes other issue after doing that.

error: repeated branch in conditional chain [bugprone-branch-clone,-warnings-as-errors]
else if (isPositive && !rhs.isPositive): the conditions are not easily simplified without breaking rest of the code. 

error: redundant boolean literal in conditional assignment [readability-simplify-boolean-expr,-warnings-as-errors]
True and false are assigned multiple times, but under different conditions. It is too complicate to simplify those without breaking the rest of the code.