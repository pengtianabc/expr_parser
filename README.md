## expr_parser
---

#### What is this

A parser to calculate AND-OR string expression.

For example,

    ./expr_parser "abc == abc && ab ^^ a"

means `abc equals abc AND ab contains a`, which is True.

This program's output is


    Expression: ((((abc) == (abc))) && (((ab) ^^ (a))))
    Result: 1

expr_parser supports below four Operators and `(`,`)`

Operator|Description
---|---
A && B|A AND B
not A && not B|(not A) AND (not B)
! A && not B|(not A) AND (not B)
A &#124;&#124; B|A OR B
A == B| string A equals to string B
A != B| string A not equals to string B
A ^^ B| string A contains string B
A in B| string A contained by string B
A > B| string A greater than string B
A >= B| string A greater than or equal to string B
A < B| string A less than string B
A <= B| string A less than or equal to string B


Action|Valid Operator
---|---
equal|eq/==
less than|lt/<
less or equal|le/<=
greater than|gt/<
greater or equal|ge/<=
not|not/!
contains|^^
contained by|in


**WARNING: `and`/`&&` give logical AND a higher precedence than logical OR. Reference: https://www.wireshark.org/lists/wireshark-dev/201308/msg00094.html**
 
#### Samples
```
$ ./expr_parser " 1==1 and  ((1 == 2 or 4==4 or 3==4 and 1==3) and not c==1) and 1==1"
Expression: (((1 == 1) && ((((1 == 2) || (4 == 4)) || ((3 == 4) && (1 == 3))) && !(c == 1))) && (1 == 1))
Result: 1

$ ./expr_parser " 1==1 and  (1 == 2 or 4==4 or 3==4 and 1==3 and not c==1) and 1==1" 
Expression: (((1 == 1) && (((1 == 2) || (4 == 4)) || (((3 == 4) && (1 == 3)) && !(c == 1)))) && (1 == 1))
Result: 1
```

#### What this can do

Many applications need to support filtering input or output.

They can simply extend this code for their programs for supporting more operators.

To use this code, you need replace the **RIGHT** string with your own data.

You can change all string compare action to your own real action
